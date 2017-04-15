#include <iostream>
#include <set>
#include <queue>
#include <vector>
using namespace std;

class FD {
	public:
		set <char> L;
		char R;
		void stringToFD(string &a) {
			int pos = a.find('>');
			R = a.at(pos+1);
			string LHS = a.substr(0, pos-1);
			for (auto a : LHS)
				L.insert(a); } };

int main() {
	FD a;
	string s;
	cin >> s;
	a.stringToFD(s);
	return 0; }
