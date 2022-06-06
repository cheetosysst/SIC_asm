#include "misc.hpp"
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, uint32_t> symtab;

std::vector<uint32_t> reloctab;

std::unordered_map<std::string, int> directive = {
    { "BASE", 1 },
    { "BYTE", 1 },
    { "WORD", 1 },
    { "RESB", 1 },
    { "RESW", 1 },
};

const struct instruction _ADD = { 0x18, 3 };
const struct instruction _ADDF = { 0x58, 3 };
const struct instruction _ADDR = { 0x90, 2 };
const struct instruction _AND = { 0x40, 3 };
const struct instruction _CLEAR = { 0x4, 2 };
const struct instruction _COMP = { 0x28, 3 };
const struct instruction _COMPF = { 0x88, 3 };
const struct instruction _COMPR = { 0xA0, 2 };
const struct instruction _DIV = { 0x24, 3 };
const struct instruction _DIVF = { 0x64, 3 };
const struct instruction _DIVR = { 0x9C, 2 };
const struct instruction _FIX = { 0xC4, 1 };
const struct instruction _FLOAT = { 0xC0, 1 };
const struct instruction _HIO = { 0xF4, 1 };
const struct instruction _J = { 0x3C, 3 };
const struct instruction _JEQ = { 0x30, 3 };
const struct instruction _JGT = { 0x34, 3 };
const struct instruction _JLT = { 0x38, 3 };
const struct instruction _JSUB = { 0x48, 3 };
const struct instruction _LDA = { 0x00, 3 };
const struct instruction _LDB = { 0x68, 3 };
const struct instruction _LDCH = { 0x50, 3 };
const struct instruction _LDF = { 0x70, 3 };
const struct instruction _LDL = { 0x08, 3 };
const struct instruction _LDS = { 0x6C, 3 };
const struct instruction _LDT = { 0x74, 3 };
const struct instruction _LDX = { 0x04, 3 };
const struct instruction _LPS = { 0xD0, 3 };
const struct instruction _MUL = { 0x20, 3 };
const struct instruction _MULF = { 0x60, 3 };
const struct instruction _MULR = { 0x98, 2 };
const struct instruction _NORM = { 0xC8, 1 };
const struct instruction _OR = { 0x44, 3 };
const struct instruction _RD = { 0xD8, 3 };
const struct instruction _RMO = { 0xAC, 2 };
const struct instruction _RSUB = { 0x4C, 3 };
const struct instruction _SHIFTL = { 0xA4, 2 };
const struct instruction _SHIFTR = { 0xA8, 2 };
const struct instruction _SIO = { 0xD0, 1 };
const struct instruction _SSK = { 0xEC, 3 };
const struct instruction _STA = { 0x0C, 3 };
const struct instruction _STB = { 0x78, 3 };
const struct instruction _STCH = { 0x54, 3 };
const struct instruction _STF = { 0x80, 3 };
const struct instruction _STI = { 0xD4, 3 };
const struct instruction _STL = { 0x14, 3 };
const struct instruction _STS = { 0x7C, 3 };
const struct instruction _STSW = { 0xE8, 3 };
const struct instruction _STT = { 0x84, 3 };
const struct instruction _STX = { 0x10, 3 };
const struct instruction _SUB = { 0x1C, 3 };
const struct instruction _SUBF = { 0x5C, 3 };
const struct instruction _SUBR = { 0x94, 2 };
const struct instruction _SVC = { 0xB0, 2 };
const struct instruction _TD = { 0xE0, 3 };
const struct instruction _TIO = { 0xF8, 1 };
const struct instruction _TIX = { 0x2C, 3 };
const struct instruction _TIXR = { 0xB8, 2 };
const struct instruction _WD = { 0xDC, 3 };

/**
 * @brief mnemonics code for dev
 *
 */
std::unordered_map<std::string, instruction> optab = {
    { "ADD", _ADD },
    { "ADDF", _ADDF },
    { "ADDR", _ADDR },
    { "AND", _AND },
    { "CLEAR", _CLEAR },
    { "COMP", _COMP },
    { "COMPF", _COMPF },
    { "COMPR", _COMPR },
    { "DIV", _DIV },
    { "DIVF", _DIVF },
    { "DIVR", _DIVR },
    { "FIX", _FIX },
    { "FLOAT", _FLOAT },
    { "HIO", _HIO },
    { "J", _J },
    { "JEQ", _JEQ },
    { "JGT", _JGT },
    { "JLT", _JLT },
    { "JSUB", _JSUB },
    { "LDA", _LDA },
    { "LDB", _LDB },
    { "LDCH", _LDCH },
    { "LDF", _LDF },
    { "LDL", _LDL },
    { "LDS", _LDS },
    { "LDT", _LDT },
    { "LDX", _LDX },
    { "LPS", _LPS },
    { "MUL", _MUL },
    { "MULF", _MULF },
    { "MULR", _MULR },
    { "NORM", _NORM },
    { "OR", _OR },
    { "RD", _RD },
    { "RMO", _RMO },
    { "RSUB", _RSUB },
    { "SHIFTL", _SHIFTL },
    { "SHIFTR", _SHIFTR },
    { "SIO", _SIO },
    { "SSK", _SSK },
    { "STA", _STA },
    { "STB", _STB },
    { "STCH", _STCH },
    { "STF", _STF },
    { "STI", _STI },
    { "STL", _STL },
    { "STS", _STS },
    { "STSW", _STSW },
    { "STT", _STT },
    { "STX", _STX },
    { "SUB", _SUB },
    { "SUBF", _SUBF },
    { "SUBR", _SUBR },
    { "SVC", _SVC },
    { "TD", _TD },
    { "TIO", _TIO },
    { "TIX", _TIX },
    { "TIXR", _TIXR },
    { "WD", _WD }
};
