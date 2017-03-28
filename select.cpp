#include <iostream>
#include <fstream>

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

bool select(string condition)
{
	int j = condition.find("=");
	string attribute  = condition.substr(0,j);
	string value = condition.substr(j+1,condition.length());

	if(attribute == "firstName")
		return (value == e.firstName);
	else if(attribute == "middleName")
		return (value == e.middleName);
	else if(attribute == "lastName")
		return (value == e.lastName);
	else if(attribute == "SSN")
		return (value == e.SSN);
	else if(attribute == "DOB")
		return (value == e.DOB);
	else if(attribute == "address")
		return (value == e.address);
	else if(attribute == "gender")
		return (value == e.gender);
	else if(attribute == "salary")
		return (value == e.salary);
	else if(attribute == "superSSN")
		return (value == e.superSSN);
	else if(attribute == "DNo")
		return (value == e.DNo);
	else if(attribute == "mobileNo")
		return (value == e.mobileNo);

	return false;
}

int main(int argN , char* argv[])
{
	if(argN == 1)
		return 2;

	ifstream fin(argv[1],ios::in);
	fin.seekg(0);

	bool result = true;
	bool emptyset = true;

	while(fin)
	{
		result = true;
		fin >> e.firstName >> e.middleName >> e.lastName >> e.SSN 
			>> e.DOB >> e.address >> e.gender >> e.salary >> e.superSSN >> e.DNo >> e.mobileNo;

		for(int i = 2; i<= argN-1; i++)
		{
			string condition = argv[i];
			result = result && select(condition);
		}

		if(result)
		{
			cout << e.firstName <<" "<< e.middleName <<" "<< e.lastName <<" "<< e.SSN <<" "<< e.DOB <<" "<< e.address <<" "<< e.gender <<" "<< e.salary <<" "<< e.superSSN <<" "<< e.DNo <<" "<< e.mobileNo <<" ";
			cout<<endl;
			emptyset = false;
		}
	}
	if(emptyset)
		cout <<"Empty Set\n";

	fin.close();
	return 0;

}
