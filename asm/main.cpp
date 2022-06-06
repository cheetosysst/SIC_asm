#include "asm.hpp"
#include "misc.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    printf("SIC/XE compiler\n");

    ifstream sourceFile;
    sourceFile.open("sample.sic");

    passOne(sourceFile);

    return 0;
}