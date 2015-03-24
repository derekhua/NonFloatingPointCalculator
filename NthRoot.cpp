#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#define EPSILON .00000001
#include <map>
#include "Calculator.h"
#include <cmath>

using namespace std;

NthRoot::NthRoot(){

};
NthRoot::~NthRoot(){

};

bool NthRoot::isNeg(string input) {
	bool isNegative = false;
	for (int i = 0; i < input.size(); i++){
		if (input[i] == '-') {
			isNegative = true;
		}
	}
	return isNegative;
}


bool NthRoot::isAlpha(string value){    //checks if input string is non doubleeger/a letter from alphabet
	bool n = false;
	for (size_t i = 0; i < value.size(); i++)
	if (isalpha(value[i]))
		n = true;
	return n;
}

bool NthRoot::isFraction(string value){
	bool isFraction = false;
	for (size_t i = 0; i < value.size(); i++)
	{
		if (value[i] == '/') {
			isFraction = true;
		}
	}
	return isFraction;
}
void NthRoot::primeFacroot(int num, vector<int>& factors, int primes)
{
	if (num % primes == 0)
	{
		factors.push_back(primes);
		primeFacroot(num / primes, factors, primes);
	}
	else if (primes <= num)
	{
		primeFacroot(num, factors, primes + 1);
	}
}


string NthRoot::simplify(string degree, string n, string op) {
	vector<int> primefactors;
	map<int, int> primes;
	int w = 0;
	double root, base, mid;
	double num, den, result;
	double a, b;
	string s, t;


	stringstream sn(n);
	sn >> base;
	stringstream sb(degree);
	sb >> root;

	primeFacroot(base, primefactors, 2);
	int j;
	if (isFraction(degree) == true) {
		for (j = 0; j < degree.size(); j++) {
			if (degree[j] == '/') {
				break;
			}
		}
		string str = degree.substr(0, j);
		string str2 = degree.substr(j + 1);
		stringstream ss(str);
		ss >> num;
		stringstream sm(str2);
		sm >> den;
	}
	else if (isFraction(degree) == false) {
		num = 1;
		den = root;
	}
	//  3/4


	//  cout << num << endl;

	for (int i = 0; i < primefactors.size(); i++) {
		primes[primefactors[i]]++;
	}

	//cout << "Res: " << res << endl;
	//cout << "int: " << (int)res << endl;
	//double test = -1;
	//cout << test << endl;

	if (base < 0) {
		base *= -1;
		double res = (pow(base, (num / den)));
		if (abs(ceil(res) - res) < 0.000001 || abs(floor(res) - res) < 0.000001) {
			int y;
			y = (int)num;
			if (y % 2 == 0) {
				stringstream ss;
				ss << res;
				string k = ss.str();
				s = ss.str();
			}
			else {
				stringstream ss;
				ss << "-" << res;
				string k = ss.str();
				s = ss.str();
			}
		}
		else {
			base *= -1;
			for (map<int, int>::iterator i = primes.begin(); i != primes.end(); ++i)
			{
				//cout << (*i).first << "-" << (*i).second << endl;
				if ((*i).second == den)
				{
					base = (*i).first;
					a = ((*i).second)*num;
					if (a < 0){
						a *= -1;
						b = (pow(base, a / den));
						ostringstream ss;
						ss << "-1 / " << b;
						s = ss.str();
					}
					else if (a > 0) {
						b = (pow(base, a / den));
						ostringstream ss;
						ss << "-" << b;
						s = ss.str();
					}
					// cout << base << "^" << a << "/" << den << endl;   

				}
				else if ((*i).second < den)
				{
					//if((*i).second == w) {
					//	base = (*i).first;
					//	a = (*i).second;
					//	ostringstream ss;
					//	w*=base; //6
					//	
					//} 
					//else { 
					base = (*i).first;
					a = ((*i).second)*num;
					ostringstream ss;
					ss << "-" << base << " ^ ( " << a << " / " << den << " )";
					t = ss.str();              //2^(2/3)

				}
				else if ((*i).second > den)
				{
					if (den < 0)
					{
						den *= -1;
						if ((*i).second == den)
						{
							base = (*i).first;
							ostringstream ss;
							a = (*i).second*num;
							b = (pow(base, a / den));
							if (b < 0)
							{
								b *= -1;
							}
							ss << "-1 / " << b;
							t = ss.str();
						}
					}
					else {
						base = ((*i).first);   //2
						a = ((*i).second)*num;     //4
						ostringstream ss;
						ss << "-" << base << " ^ ( " << a << " / " << den << " )";
						t = ss.str();
					}
				}
				w = (*i).second;
				mid = (*i).first;
			}
		}
	}
	else {
		double res = (pow(base, (num / den)));
		if (abs(ceil(res) - res) < 0.000001 || abs(floor(res) - res) < 0.000001) {

			stringstream ss;
			ss << res;
			string k = ss.str();
			s = ss.str();
		}
		else {
			for (map<int, int>::iterator i = primes.begin(); i != primes.end(); ++i)
			{
				//cout << (*i).first << "-" << (*i).second << endl;
				if ((*i).second == den)
				{
					base = (*i).first;
					a = ((*i).second)*num;
					if (a < 0)
					{
						a *= -1;
						b = (pow(base, a / den));
						ostringstream ss;
						ss << "1 / " << b;
						s = ss.str();
					}
					else if (a > 0)
					{
						b = (pow(base, a / den));
						ostringstream ss;
						ss << b;
						s = ss.str();
					}
					// cout << base << "^" << a << "/" << den << endl;   

				}
				else if ((*i).second < den)
				{
					//if((*i).second == w) {
					//	base = (*i).first;
					//	a = (*i).second;
					//	ostringstream ss;
					//	w*=base; //6
					//	
					//} 
					//else { 
					base = (*i).first;
					a = ((*i).second)*num;
					if (a < 0)
					{
						a *= -1;
						ostringstream ss;
						ss << "1 / (" << base << " ^ ( " << a << " / " << den << " )";
						t = ss.str();
					}
					else
					{
						ostringstream ss;
						ss << base << " ^ ( " << a << " / " << den << " )";
						t = ss.str();              //2^(2/3)
					}
				}
				else if ((*i).second > den)
				{
					base = ((*i).first);   //2
					a = ((*i).second)*num;     //4
					if (den < 0)
					{
						den *= -1;
						if ((*i).second == den)
						{
							ostringstream ss;
							ss << "1 / " << base;
							t = ss.str();
						}
					}
					else
					{
						ostringstream ss;
						ss << base << " ^ ( " << a << " / " << den << " )";
						t = ss.str();
					}
				}
				w = (*i).second;
				mid = (*i).first;
			}
		}
	}

	if (s == "")
		return t;
	else if (t == "")
		return s;
	else
		return s + " * " + t;
}

bool NthRoot::check(string v1, string v2) {
	return " ";
}

string NthRoot::calculate(string v1, string v2, string op) {
	string a;
	int root;
	int base;
	double orange, banana;
	string o, n;

	if (isAlpha(v2) == false){
		stringstream sn(v1);    //string v1 conver to double root
		sn >> root;
		stringstream ss(v2);
		ss >> base;

		if (base < 0 && root % 2 == 0) { //&& (v1 != "e" || v2 !="e") && (v1!= "pi" ||v2 != "pi")) {
//			throw exception("Error: cannot take the even root of a negative number");

		}
	}
	if (v1 == "0") {
//		throw exception("Error: cannot have a zero root term");
	}

	if (v1 == "e" || v2 == "e"){
		if (v2 == "0") {
			a = "0";
		}
		else if (v1 == "1") {
			a = v2;
		}
		else if (v2 != "0" && v1 != "1") {
			a = v2 + " ^ " + v1;
		}

	}
	else if (v1 == "pi" || v2 == "pi"){
		if (v2 == "0") {
			a = "0";
		}
		else if (v1 == "1") {
			a = v2;
		}
		else if (v2 != "0" && v1 != "1") {
			a = v2 + " ^ " + v1;
		}
	}
	else if (isAlpha(v1) == true || isAlpha(v2) == true) {
		if (v1 == "1")
		{
			a = v2;
		}
		else if (isFraction(v1) == false) {
			a = v2 + " ^ (1 /" + v1;
		}
		else if (isFraction(v1) == true) {
			int i;
			for (int i = 0; i < v1.size(); i++) {
				if (v1[i] == '/') {
					break;
				}
			}
			string str = v1.substr(0, i);
			string str2 = v1.substr(i + 1);
			stringstream ss(str);      //num
			ss >> orange;
			stringstream sm(str2);    //den
			sm >> banana;
			ostringstream sb;   //num
			sb << orange;
			ostringstream sg;   //den
			sg << banana;
			o = sb.str();
			n = sg.str();
			a = v2 + " ^ (" + n + " / " + o + ")";
		}
	}
	else if (isFraction(v1) == false && isFraction(v2) == false && v1 != "0" && v1 != "1"){  //e.g. 3rt:8 = 2, e.g. 3rt:4= 4^(1/3)
		a = simplify(v1, v2, op);
	}
	else if (isFraction(v1) == true && isFraction(v2) == false && v1 != "0" && v1 != "1") {
		int i;
		for (i = 0; i < v1.size(); i++) {
			if (v1[i] == '/') {
				break;
			}
		}

		double fun, done;
		string stop = v1.substr(0, i);
		string sbot = v1.substr(i + 1);
		//stringstream sl(stop);
		//sl >> fun;                               //the numerator of fraction of root
		//stringstream sk(sbot);
		//sk >> done; 
		//done*=-1;
		//fun*=-1;
		//ostringstream h;                        //conver this back to string but switch num and den
		//h << done << " / " << fun;
		//string y = h.str();
		//      a = simplify(y, v2, op);
		//}
		//else { 
		if (isNeg(stop) == true || isNeg(sbot) == true) {
			stringstream sl(stop);
			sl >> fun;                               //the numerator of fraction of root
			stringstream sk(sbot);
			sk >> done;
			ostringstream h;                        //conver this back to string but switch num and den
			h << "-" << done << " / " << fun;
			string y = h.str();
			a = simplify(y, v2, op);
		}
		else {
			stringstream sl(stop);
			sl >> fun;                               //the numerator of fraction of root
			stringstream sk(sbot);
			sk >> done;
			ostringstream h;                        //conver this back to string but switch num and den
			h << done << " / " << fun;
			string y = h.str();
			a = simplify(y, v2, op);
		}

		//a = simplify(v1, v2, op);
	}
	else if (v2 == "0") {
		a = "0";
		return a;
	}
	else if (v1 == "0") {          //if 0rt:2 = 2^0, = 1
		a = "undefined";
	}
	else if (v1 == "1") {          //if 1rt:2 = 2^1, =2
		a = v2;
	}
	return a;
}
