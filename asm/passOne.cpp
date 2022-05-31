
#include "misc.hpp"

using namespace std;

void passOne(ifstream &source) {
	
	string line;
	vector<string> splitLine;
	while (getline(source, line)) {
		split(line, splitLine, ' ');
		for (auto l: splitLine) cout << trim(l) <<endl;
	}
}