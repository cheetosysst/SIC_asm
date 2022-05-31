#include <bits/stdc++.h>
#include "misc.hpp"
#include "asm.hpp"

using namespace std;

int main() {
	printf("SIC/XE compiler\n");

	ifstream sourceFile;
	sourceFile.open("test.sic");

	passOne(sourceFile);
	

	return 0;
}