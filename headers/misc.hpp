#ifndef SIC_MISC
#define SIC_MISC

#include<bits/stdc++.h>

#define endl "\n"

struct locptr {
	std::string label;
	int32_t address;
};

struct instruction {
	int8_t opcode;
	int8_t n;
	int8_t i;
	int8_t x;
	int8_t b;
	int8_t p;
	int8_t e;
	
	int32_t target;
	int32_t disp;

	int8_t format;
	int8_t r1;
	int8_t r2;
};

size_t split(const std::string& txt, std::vector<std::string>& strs, char ch);

inline std::string &ltrim(std::string &s);
inline std::string &rtrim(std::string &s);
std::string trim(std::string &s);

#endif