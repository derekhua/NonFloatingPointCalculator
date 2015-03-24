#include "Calculator.h"


Factorial::Factorial(){
	//donothing
}

Factorial::~Factorial() {
	//do nothing
}

string Factorial::simplify(string n, string degree, string op) {
	return "";
}
bool Factorial::check(string value1, string value2) {
	return true;
}

string Factorial::calculate(string num1, string num2, string action)
{
	for (int i = 0; i < num1.length(); i++)
	{
		if (num1[i] == '-')
		{
			return "can’t contain negative numbers";
			break;
		}
		if (num1[i] == '/')
		{
			return "can’t contain fractions";
			break;
		}
	}
	stringstream str;
	str << num1;
	int factorial;
	str >> factorial;
	int total = factorialHelper(factorial);
	string Result;
	ostringstream convert;
	convert << total;
	Result = convert.str();
	return Result;
}

int Factorial::factorialHelper(int factorial)
{
	if (factorial <= 0)
		return 1;
	else
		return factorial * factorialHelper(factorial - 1);
}
