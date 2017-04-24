#include<iostream>
#include<algorithm>
#include<stdlib.h>
#define bSIZE 100
#define tSIZE 10
using namespace std;

class fd {
	public:
		string L;
		char R;
		void load(string Lin, char Rin) {
			L = Lin;
			R = Rin;
		}
};

class relation {
	public:
		string attr_set;
		int keylimiter;
		string getKey() {
			return attr_set.substr(0,keylimiter);
		}
		string getnonKey() {
			if(keylimiter==attr_set.length())
				return "";
			return attr_set.substr(keylimiter);
		}
		void keyLoad(string key) {
			attr_set = key;
			keylimiter = key.length();
		}
		void nonkeyLoad(char c) {
			attr_set.append(1,c);
		}
		void simpleDisplay() {
			cout<<getKey()<<" "<<getnonKey()<<endl;
		}
};

 //UTILITY - Returns 1 if s1 is a subset of s2, otherwise 0
int strIsSubset(string s1, string s2) {
	for(int i=0;i<s1.length();i++)
		if(s2.find(s1.at(i))==string::npos)
			return 0;
	return 1;
}

void strUnion(string &s1, string s2) {
	for(int i=0;i<s2.length();i++) {
		if(s1.find(s2.at(i))==string::npos)
			s1.append(1,s2.at(i));
	}
	sort(s1.begin(),s1.end());
}

void strUnion(string &s1, char c) {
	string s2;
	s2.append(1,c);
	strUnion(s1,s2);
}

void fdsCopier(fd fdsrc[],fd fdst[],int sSIZE) {
	for(int i=0;i<sSIZE;i++) {
		fdst[i].L = fdsrc[i].L;
		fdst[i].R = fdsrc[i].R;
	}
}

void crHelper(fd fds[], fd fdcr[], int SIZE, int fdnum) {
	int k = 0;
	for(int i=0;i<SIZE;i++)
		if(fdnum!=i) {
			fdcr[k].L = fds[i].L;
			fdcr[k].R = fds[i].R;
			k++;
		}
}

string allAttributes(fd fds[],int SIZE) {
	string attr_set;
	for(int i=0;i<SIZE;i++) {
		strUnion(attr_set, fds[i].L);
		strUnion(attr_set, fds[i].R);
	}
	return attr_set;
}

int bulkInput(fd fds[], int SIZE) {
	int j = 0;
	string s;
	for(int i=0;i<SIZE;i++) {
		cout<<"Enter FD "<<i<<": ";
		cin>>s;
		int split=s.find('>');
		if (split==0)
			break;
		string Lin=s.substr(0, split);
		string Rin=s.substr(split+1);
		sort(Lin.begin(),Lin.end());
		Lin.erase(std::unique(Lin.begin(), Lin.end()), Lin.end());
		for(int k=0;k<Rin.length();k++) {
			fds[j].load(Lin,Rin[k]);
			j++;
		}
	}
	return j;
}

string closure(fd fds[], string fplus, int SIZE) {
	string ofplus;
	do {
		ofplus = fplus;
		for(int i=0;i<SIZE;i++)
			if(strIsSubset(fds[i].L,fplus)==1)
				strUnion(fplus,fds[i].R);
	}
	while(fplus.compare(ofplus)!=0);
	return fplus;
}

string keyFinder(fd fds[], int SIZE) {
	string key, attr_set, keycr;
	key = attr_set = allAttributes(fds, SIZE);
	int i = 0;
	while(i<key.length()) {
		if(key.length()>1) {
			keycr = key;
			keycr.erase(i,1);
			if(attr_set.compare(closure(fds,keycr,SIZE))==0)
				key = keycr;
			else
				i++;
		}
		else
			return key;
	}
	return key;
}

int fdCover(fd fds1[], fd fds2[], int SIZE1, int SIZE2) {
	for(int i=0;i<SIZE2;i++)
		if(closure(fds1,fds2[i].L,SIZE1).find(fds2[i].R)==string::npos)
			return 0;
	return 1;
}

int equivalence(fd fds1[], fd fds2[], int SIZE1, int SIZE2) {
	return(fdCover(fds1,fds2,SIZE1,SIZE2) && fdCover(fds2,fds1,SIZE2,SIZE1));
}

int minCover(fd fds[], int SIZE) {
	int j;
	fd fdcr[bSIZE];
	for(int i=0;i<SIZE;i++) {
		j=0;
		while(j<fds[i].L.length()) {
			if(fds[i].L.length()>1) {
				fdsCopier(fds,fdcr,SIZE);
				fdcr[i].L.erase(j,1);
				if(equivalence(fds,fdcr,SIZE,SIZE)==1)
					fdsCopier(fdcr,fds,SIZE);
				else
					j++;
			}
			else
				break;
		}
	}

	j=0;
	while(j<SIZE) {
		crHelper(fds,fdcr,SIZE,j);
		if(equivalence(fds,fdcr,SIZE,SIZE-1)==1) {
			fdsCopier(fdcr,fds,SIZE-1);
			SIZE-=1;
		}
		else
			j++;
	}
	return SIZE;
}

int NF3(fd fds[], int &SIZE, relation rset[]) {
	int rSIZE = 0;
	string key = keyFinder(fds, SIZE);
	SIZE = minCover(fds, SIZE); //1. Reduce FD Set to Minimal Cover.
	for(int i=0;i<SIZE;i++) {//2. Put FDs into relations GROUP BY LHS and set KEY = LHS.
		int j;
		for(j=0;j<rSIZE;j++)
			if(fds[i].L.compare(rset[j].getKey())==0) {
				rset[j].nonkeyLoad(fds[i].R);
				break;
			}

		if(j==rSIZE) {
			rset[j].keyLoad(fds[i].L);
			rset[j].nonkeyLoad(fds[i].R);
			rSIZE++;
		}
	}
	//At this stage, 3NF is complete but may be lossy.
	for(int i=0;i<rSIZE;i++) {//3. Test if Relation Set possibly requires fixing for Lossless Design.
		if(strIsSubset(key,rset[i].attr_set)==1)
			return rSIZE;
	}

	for(int i=0;i<rSIZE;i++) {//4. Ensure Lossless property by adding new 'key-only' relation.
		if(strIsSubset(rset[i].attr_set,key)==1) {
			rset[i].keyLoad(key);
			return rSIZE;
		}
	}
	rset[rSIZE].keyLoad(key);
	return rSIZE+1;
}

int isBCNF(relation rset[], fd fds[], int rSIZE, int fSIZE) {
	for(int i=0;i<fSIZE;i++)
		for(int j=0;j<rSIZE;j++)
			if((strIsSubset(fds[i].L,rset[j].attr_set)==1) && (rset[j].attr_set.find(fds[i].R)!=string::npos))
				if(strIsSubset(rset[j].attr_set,closure(fds,fds[i].L,fSIZE))!=1)
					return 0;
	return 1;
}

int main() {
	fd fds1[bSIZE], fds2[bSIZE];
	relation rset[bSIZE];
	int n1,rs1, nFd;
	cout << "Enter number of FDs: ";
	cin >> nFd;
	n1 = bulkInput(fds1,nFd);
	cout<<"3NF Set\n";
	rs1 = NF3(fds1, n1, rset);
	cout << "\nNormalized relations(3NF): (Keyset Restof Relation)\n";
	for(int i=0;i<rs1;i++)
		rset[i].simpleDisplay();
	if(isBCNF(rset,fds1,rs1,n1))
		cout<<"It is in BCNF";
	else
		cout<<"It is not in BCNF";
	cout <<endl;
}
