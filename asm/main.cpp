#include "asm.hpp"
#include "misc.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    printf("SIC/XE compiler\n");

    ifstream sourceFile;
    ofstream compiledFile;
    sourceFile.open("sample.sic");
    compiledFile.open("export.txt");

    passOne(sourceFile);
    passTwo(compiledFile);

    sourceFile.close();
    compiledFile.close();

    return 0;
}