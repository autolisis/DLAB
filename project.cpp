#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

class employee
{
	public:
		string SSN;
		string firstName;
		string middleName;
		string lastName;
		string DOB;
		string gender;
		string salary;
		string superSSN;
		string DNo;
		string mobileNo;
		string address;
} e;

int project(char * attrName)
{
	if(strcmp(attrName,"firstName")==0)
		cout<<e.firstName<<" ";
	else if(strcmp(attrName,"middleName")==0)
		cout<<e.middleName<<" ";
	else if(strcmp(attrName,"lastName")==0)
		cout<<e.lastName<<" ";
	else if(strcmp(attrName,"SSN")==0)
		cout<<e.SSN<<" ";
	else if(strcmp(attrName,"DOB")==0)
		cout<<e.DOB<<" ";
	else if(strcmp(attrName,"address")==0)
		cout<<e.address<<" ";
	else if(strcmp(attrName,"gender")==0)
		cout<<e.gender<<" ";
	else if(strcmp(attrName,"salary")==0)
		cout<<e.salary<<" ";
	else if(strcmp(attrName,"superSSN")==0)
		cout<<e.superSSN<<" ";
	else if(strcmp(attrName,"DNo")==0)
		cout<<e.DNo<<" ";
	else if(strcmp(attrName,"mobileNo")==0)
		cout<<e.mobileNo<<" ";
}

int main(int argN, char* argv[])
{
	if(argN == 1)
		return 2;

	ifstream fin(argv[1], ios::in);
	fin.seekg(0);

	for(int i = 2; i<= argN-1; i++)
		cout<<argv[i]<<" ";
	cout<<endl;
	while (!fin.eof())
	{
		fin >> e.firstName >> e.middleName >> e.lastName >> e.SSN 
			>> e.DOB >> e.address >> e.gender >> e.salary >> e.superSSN >> e.DNo >> e.mobileNo;

		for(int i = 2; i<= argN-1; i++)
			project(argv[i]);
		cout<<endl;
	}
	fin.close();
	return 0;
}
