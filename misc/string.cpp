#include "misc.hpp"
#include <bits/stdc++.h>

/**
 * @brief Split string function.
 *
 * @param txt
 * @param strs
 * @param ch
 * @return size_t
 */
size_t split(const std::string& txt, std::vector<std::string>& strs, char ch)
{
    // TODO re-write split function.
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}

std::vector<std::string> parser(std::string line)
{
    std::vector<std::string> instruction;

    std::string chrTab("\t");
    std::string chrSpace(" ");

    std::size_t posTab = line.find(chrTab);
    while (posTab != std::string::npos) {
        line.replace(posTab, chrTab.length() - 1, " ");
        posTab = line.find(chrTab, posTab + 1);
    }

    split(line, instruction, ' ');

    // TODO string trim

    return instruction;
}

std::string getUpper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return str;
}

// uint8_t literalExtract(std::string addr)
// {
// }

uint32_t addrExtract(std::string addr)
{
    return (uint32_t) addr[0];
}