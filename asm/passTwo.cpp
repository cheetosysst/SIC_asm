#include "asm.hpp"
#include "misc.hpp"
#include <sstream>
#include <stdint.h>
#include <vector>

extern struct intermediate imData;
extern struct unordered_map<string, instruction> optab;

void passTwo(ofstream& compiled)
{
    printf("Pass 2 Start\n");

    // Header Record
    std::string temp = "COPY";
    compiled << "H^" << std::setw(6) << std::left << temp << "^";
    compiled << setfill('0') << setw(6) << imData.start << "^";
    compiled << setfill('0') << setw(6) << std::right << std::hex << imData.size << endl;

    // Texr Record
    uint32_t recordData = 0;
    uint32_t recordCounter = 0;
    uint32_t addressCounter = imData.start;
    uint32_t baseAddress = 0;

    std::stringstream record;
    for (std::vector<imCode>::iterator it = imData.codes.begin(); it != imData.codes.end(); it++) {
        struct imCode current = *it;
        std::string charData;
        int32_t targetData = 0;

        cout << "data: " << current.data;

        // Parse data
        switch (addrExtract(current.data)) {
        case 1: // immediate
            std::cout << ",\ttype: \x1b[31m immed\x1b[39m";
            break;
        case 2:
            // indirect
            std::cout << ",\ttype: \x1b[32m indir\x1b[39m";
            break;
        case 3:
            // indexed
            std::cout << ",\ttype: \x1b[33m dual\x1b[39m";
            break;
        case 4:
            // immediate
            std::cout << ",\ttype: \x1b[34m index\x1b[39m";
            break;
        case 5:
            // hex
            std::cout << ",\ttype: \x1b[35m hex\x1b[39m";
            charData = parsedHex(current.data);
            break;
        case 6:
            // char
            std::cout << ",\ttype: \x1b[36m char\x1b[39m";
            charData = parsedChar(current.data);
            break;
        case 7:
            std::cout << ",\ttype: \x1b[37m label\x1b[39m";
            targetData = imData.symtab[current.data];
            break;
        case 8:
            std::cout << ",\ttype: \x1b[37m int\x1b[39m";
            targetData = stoi(current.data);
            break;

        default:
            std::cout << ",\ttype: \x1b[30m blank\x1b[39m";
            break;
        }

        cout << ", \tins: " << current.ins;
        if (current.ins == "BYTE") {
            if (!targetData)
                record << "^" << charData;
            else
                record << "^" << targetData;
            recordData += 1;
            recordCounter += 1;
        } else if (current.ins == "WORD") {
            record << "^" << charData;
            recordData += 3;
            recordCounter += 3;
        } else if (current.ins == "RESB") {
            recordCounter += targetData;
        } else if (current.ins == "RESW") {
            recordCounter += targetData * 3;
        } else if (current.ins == "BASE") {
            baseAddress = targetData;
        } else {

            uint32_t entry = current.opcode;
            switch (optab[current.ins].len) {
            case 1:
                // 1 byte
                recordData += 1;
                recordCounter += 1;
                // addressCounter += 1;
                break;
            case 2:
                entry *= 0x100;
                std::cout << " \t" << std::hex << std::setfill('0') << std::setw(4) << entry;
                record << "^" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << entry;
                recordData += 2;
                recordCounter += 2;
                // addressCounter += 2;
                break;
            case 3:
                entry *= (current.extFormat) ? 0x1000000 : 0x10000;
                std::cout << " \t" << std::hex << std::setfill('0') << std::setw((current.extFormat) ? 8 : 6) << entry;
                record << "^" << std::hex << std::uppercase << std::setfill('0') << std::setw((current.extFormat) ? 8 : 6) << entry;
                recordData += (current.extFormat) ? 4 : 3;
                recordCounter += (current.extFormat) ? 4 : 3;
                // addressCounter += (current.extFormat) ? 4 : 3;
                break;
            }
        }

        if (it + 1 == imData.codes.end() || recordCounter + optab[(*(it + 1)).ins].len > 30) {
            compiled << "T^" << std::hex << std::uppercase << std::setfill('0') << std::setw(6) << addressCounter << "^" << std::setw(2) << (int)recordData << record.str() << endl;
            record.str("");
            recordData = 0;
            addressCounter += recordCounter;
            recordCounter = 0;
        }
        cout << std::hex << std::uppercase << ",\tbase: 0x" << baseAddress;
        cout << endl;
    }

    if (record.str().size()) {
        compiled << "T^" << std::hex << std::uppercase << std::setfill('0') << std::setw(6) << addressCounter << "^" << std::setw(2) << (int)recordCounter << record.str() << endl;
    }

    // Modification and End header
    for (auto relocAddr : imData.reloctab) {
        compiled << "M^" << setfill('0') << setw(6) << std::hex << relocAddr.first << "^" << setw(2) << (int)relocAddr.second << endl;
    }
    compiled << "E^" << setfill('0') << setw(6) << imData.start << endl;

    printf("Pass 2 Complete\n");
}

bool is_int(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

uint8_t addrExtract(std::string data)
{
    if (data[0] == '#') {
        return 1;
    }
    if (data[0] == '@') {
        return 2;
    }
    if (data.find(",X") != std::string::npos || data.find(",x") != string::npos) {
        return 4;
    }
    if (data.find(',') != std::string::npos) {
        return 3;
    }
    if ((data[0] == 'x' || data[0] == 'X') && data[1] == '\'') {
        return 5;
    }
    if ((data[0] == 'c' || data[0] == 'C') && data[1] == '\'') {
        return 6;
    }
    if (imData.symtab.count(data)) {
        return 7;
    }
    if (is_int(data)) {
        return 8;
    }
    return 0;
}

std::string parsedChar(std::string data)
{
    std::stringstream ss;
    for (int i = 2; i < (int)data.size() - 1; i++) {
        ss << std::setw(2) << std::hex << std::uppercase << std::setfill('0') << (int)data[i];
    }
    return ss.str();
}

std::string parsedHex(std::string data)
{
    data.replace(0, 2, "");
    data.replace(data.size() - 1, 1, "");
    return data;
}
