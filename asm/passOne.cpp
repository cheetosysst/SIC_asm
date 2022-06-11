
#include "asm.hpp"
#include "misc.hpp"

using namespace std;

extern unordered_map<string, instruction> optab;
extern unordered_map<string, uint32_t> symtab;
extern std::vector<pair<uint32_t, uint8_t>> reloctab;
extern unordered_map<string, directives> directive;
struct intermediate imData;
uint32_t address = 0;

void passOne(ifstream& source)
{

    string line;
    vector<string> splitLine;
    int idx = 1;
    bool firstLine = true;

    string objectName;
    uint32_t startAddress;
    // uint32_t baseAddress;

    while (getline(source, line)) {

        if (firstLine) {
            firstLine = false;
            idx += 1;

            vector<string> start = parser(line);
            if (getUpper(start[1]) != "START") {
                printf("FATAL: \"START\" not specified.");
                exit(-1);
            }

            objectName = start[0];
            startAddress = stoi(start[2]);

            cout << "Program name: " << objectName << endl;
            cout << "Initial address: " << startAddress << endl;

            imData.name = objectName;
            imData.start = startAddress;

            continue;
        }

        vector<string> instruction = parser(line);

        // comment line
        if (instruction[0][0] == '.') {
            idx++;
            continue;
        }
        // empty line
        if ((int)instruction[0][0] == 0) {
            idx++;
            continue;
        }

        int extFormat = false;

        // Delete trailing comment
        for (vector<string>::iterator it = instruction.begin(); it != instruction.end(); it++) {
            if ((*it)[0] != '.')
                continue;
            instruction.erase(it, instruction.end());
            break;
        }

        // Look up directives
        string directive_word = "";
        if (directive.count((instruction.size() == 3) ? instruction[1] : instruction[0])) {
            directive_word = getUpper(instruction.size() == 3 ? instruction[1] : instruction[0]);
            printf("Line %d, directive: ", idx);
            cout << (instruction.size() == 3 ? instruction[1] : instruction[0]) << ", locptr: 0x" << hex << uppercase << address << endl;
            struct imCode tempCode = {
                (string) "",
                0,
                0xFF,
                (string) "",
                false
            };
            if (directive_word == (string) "RESB") {
                if (instruction.size() == 3)
                    symtab[instruction[0]] = address;

                tempCode.ins = "RESB";
                tempCode.data = (instruction.size() == 3 ? instruction[2] : instruction[1]);

                imData.codes.push_back(tempCode);
                address += stoi(instruction.size() == 3 ? instruction[2] : instruction[1]);
                // imData.size = address;
                idx++;
                continue;
            }
            if (directive_word == (string) "RESW") {
                if (instruction.size() == 3)
                    symtab[instruction[0]] = address;

                tempCode.ins = "RESW";
                tempCode.data = (instruction.size() == 3 ? instruction[2] : instruction[1]);
                tempCode.opcode = 0xFF;

                imData.codes.push_back(tempCode);
                address += stoi(instruction.size() == 3 ? instruction[2] : instruction[1]) * 3;
                // imData.size = address;
                idx++;
                continue;
            }
            if (directive_word == (string) "BYTE") {
                if (instruction.size() == 3)
                    symtab[instruction[0]] = address;
                tempCode.ins = "BYTE";
                tempCode.len = 1;
                tempCode.data = (instruction.size() == 3 ? instruction[2] : instruction[1]);
                imData.codes.push_back(tempCode);

                address += 1;
                // imData.size = address;
                idx++;
                continue;
            }
            if (directive_word == (string) "WORD") {
                if (instruction.size() == 3)
                    symtab[instruction[0]] = address;
                tempCode.ins = "WORD";
                tempCode.len = 3;
                tempCode.data = (instruction.size() == 3 ? instruction[2] : instruction[1]);
                imData.codes.push_back(tempCode);
                address += 3;
                // imData.size = address;
                idx++;
                continue;
            }
            if (directive_word == (string) "BASE") {
                // baseAddress = addrExtract(instruction.size() == 3 ? instruction[2] : instruction[1]);
                tempCode.ins = "BASE";
                tempCode.len = 0;
                tempCode.data = (instruction.size() == 3 ? instruction[2] : instruction[1]);
                imData.codes.push_back(tempCode);
                idx++;
                continue;
            }
        }

        // Look up opcode

        if (instruction.size() == 2) {
            if (instruction[0][0] == '+') {
                extFormat = true;
                instruction[0].replace(0, 1, "");
            }
        }
        if (instruction.size() == 3) {
            symtab[instruction[0]] = address;
            if (instruction[1][0] == '+') {
                extFormat = true;
                instruction[1].replace(0, 1, "");
            }
        }

        string ins = (instruction.size() == 3) ? instruction[1] : instruction[0];
        if (!optab.count(ins)) {

            if (ins == "END") {
                cout << "Line " << idx << ", END, Full: " << address << endl;
                break;
            }

            cout << "Unknown instruction: " << ins << " on line " << idx << endl;
            exit(-1);
        }

        uint8_t instructionLength = optab[instruction[instruction.size() == 3 ? 1 : 0]].len;

        if (ins == "JSUB") {
            reloctab.push_back(make_pair(address + 1, (extFormat) ? 5 : 3));
            // if (extFormat)
            //     instructionLength++;
            // address--;
        }
        // if (ins == "RSUB") {
        //     reloctab.push_back(make_pair(address + 1, (extFormat) ? 5 : 3));
        //     // address--;
        // }
        if (extFormat)
            instructionLength++;

        // debug messages
        printf("Line %d, insLen: %ld, Ext %d, ", idx, instruction.size(), extFormat);
        cout << "instruction: " << ins;
        printf(", length: %X", instructionLength);
        printf(", opcode: 0x%X", (instruction.size() == 3) ? optab[instruction[1]].opcode : optab[instruction[0]].opcode);
        if (instruction.size() > 1)
            cout << ", data: " << instruction[instruction.size() - 1] << ",\t";
        printf("locptr: 0x%X\n", address);
        // printf(", base: 0x%X\n", baseAddress);

        struct imCode tempCode = {
            ins,
            0,
            (instruction.size() == 3) ? optab[instruction[1]].opcode : optab[instruction[0]].opcode,
            instruction[instruction.size() - 1],
            (bool)extFormat
        };
        imData.codes.push_back(tempCode);

        // if (instruction.size() == 1)
        //     address += 1;
        // address += (optab[instruction[instruction.size() == 3 ? 1 : 0]].len == 2) ? 2 : ((extFormat) ? 4 : 3);
        address += instructionLength;

        idx += 1;
    }
    imData.size = address;
    imData.reloctab = reloctab;
    imData.symtab = symtab;
    printf("Pass 1 Complete\n");
}