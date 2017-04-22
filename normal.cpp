#include <iostream>
#include <set>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class FD {
	public:
		set <char> L;
		char R;
		FD(string &lhs, char rhs) {
			for (auto i:lhs)
				L.insert(i);
			R=rhs;
		}
};

/* in */
int main() {
	vector <FD> fds;
	string s;
	while (1) {
		cin >> s;
		int split=s.find('>');
		if (split==0)
			break;
		string l=s.substr(0, split);
		string r=s.substr(split+1);
		for (auto ch : r) {
			FD newfd(l, ch);
			fds.push_back(newfd);
		}
	}
	return 0; 
}
