#include "Calculator.h"


Division::Division() {

}
Division :: ~Division() {

}
bool Division::isAlpha(string value) {
	bool n = false;
	for (size_t i = 0; i < value.size(); i++)
	if (isalpha(value[i]))
		n = true;
	return n;

}
bool Division::isFraction(string value) {
	bool isFraction = false;
	for (size_t i = 0; i < value.size(); i++)
	{
		if (value[i] == '/') {
			isFraction = true;
		}
	}
	return isFraction;
}
bool Division::check(string value1, string value2) {
	return true;
}
string  Division::simplify(string value1, string value2, string operation) {

	return "";
}
string Division::calculate(string value1, string value2, string ope) {
	string a;
	double b = 0, c = 0, d = 0, e = 0, top = 0, bot = 0;
	string str = "";
	string use1 = "";
	string use2 = "";
	unsigned int v1 = 0;
	int v2 = 0;
	vector <string> vect1;
	vector <string> vect2;
	vector <char> opera1;
	vector <char> opera2;
	 //if "/" is in string1 and string2 contains "/", call mult calc
							//if string2 doesn't contain "/", insert "1/" over string2 then call mult calc
	//value1 = "5 / 2";
	//value2 = "1 / 2";
	str = value1 + ope + value2;
	Multiplication* mult = new Multiplication();
	Division* div = new Division();
	if (value1.find('/') != string::npos) {
		if (value2.find('/') != string::npos) {
			str = mult->calculate(value1, value2, ope);
		}
		else {
			value2 = "1 / " + value2;
			str = mult->calculate(value1, value2, ope);
		}
	}
	else if (value2.find('/') != string::npos) {
		if (value1.find('/') != string::npos) {
			str = mult->calculate(value1, value2, ope);
			//str = div->calculate("1", str, ope);
		}
		else {
			value1 = "1 / " + value1;
			str = mult->calculate(value1, value2, ope);
			//str = div->calculate("1", str, ope);
		}
	}
	/*else {
		value1 = "1 / " + value1;
		str = mult->calculate(value1, value2, ope);
	}*/

	/*while (v1 < value1.length()){
		if (!(value1.at(v1) == '+' || value1.at(v1) == '-' || value1.at(v1) == ' ' || value1.at(v1) == '(' || value1.at(v1) == ')'))
		{
			use1 += value1.at(v1);     // appeding if the are no operators
		}
		else {
			if (value1.at(v1) == '-' &&  value1.at(v1 + 1) != ' ') {
				use1 += value1.at(v1);
			}
			opera1.push_back(value1.at(v1));  // stacking the operators
		}
		v1++;

	}
	vect1.push_back(use1);   // adding the separeted string to the vector 


	vect2.push_back(use2);  // adding the separeted string to the vector */
	str = Operation::fractionReduction(str);

	
	return str;

}
