#ifndef SIC_MISC
#define SIC_MISC

#include<bits/stdc++.h>

#define endl "\n"

struct instruction {
	uint8_t opcode;
	uint8_t len;
};

struct directives {
	void (*func)();
};

struct imCode {
	std::string ins;
	uint32_t len;
	uint8_t opcode;
	std::string data;
	bool extFormat;
};


struct intermediate {
	std::string name;
	uint32_t baseAddress;
	uint32_t size;
	uint32_t start;
	std::vector<std::pair<uint32_t, uint8_t>> reloctab;
	std::vector<imCode> codes;
	std::unordered_map<std::string, uint32_t> symtab;
};

size_t split(const std::string& txt, std::vector<std::string>& strs, char ch);

std::vector<std::string> parser(std::string line);

std::string getUpper(std::string str);

uint32_t addrExtract(std::string addr);

#endif