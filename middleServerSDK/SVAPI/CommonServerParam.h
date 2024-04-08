#pragma once
#include <string>
using namespace std;
class CommonServerParam
{
private:
	string mCardPassword;
	string mParam; 
public:
	CommonServerParam(string cardPwd,string param);

	string getRequestString();
};

