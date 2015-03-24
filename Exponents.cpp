#include "Calculator.h"
#include <cmath>
//#define EPSILON .00000001

using namespace std;

Exponents::Exponents(){

}
Exponents::~Exponents(){

}


bool Exponents::isAlpha(string value){    //checks if input string is non doubleeger/a letter from alphabet
	bool n = false;
	for (size_t i = 0; i < value.size(); i++)
	if (isalpha(value[i]))
		n = true;
	return n;
}
bool Exponents::isFraction(string value) {
	bool isFraction = false;
	for (size_t i = 0; i < value.size(); i++)
	{
		if (value[i] == '/') {
			isFraction = true;
		}
	}
	return isFraction;

}
/*
bool isPrime (int n) {
if (n < 2){
return false;
}
for (int i=2; i<=sqrt(n); i++){

if ((n%i) == 0) {
return false;
}
}
return true;
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Exponents::check(string v1, string v2) {
	bool result = false;
	if (isFraction(v1) == true && isFraction(v2) == false) {
		//simplify v1
		result = true;
		return result;
	}
	else if (isFraction(v1) == false && isFraction(v2) == true) {
		//simplify v2
		result = true;
		return result;
	}
	else if (isFraction(v1) == false && isFraction(v2) == false) {
		result = true;
		return result;
	}
	else
		result = false;
	return  result;
}

void Exponents::primeFacexpo(int num, vector<int>& factors, int primes)
{
	if (num % primes == 0)
	{
		factors.push_back(primes);
		primeFacexpo(num / primes, factors, primes);
	}
	else if (primes <= num)
	{
		primeFacexpo(num, factors, primes + 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Exponents::simplify(string n, string degree, string op) {
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

	primeFacexpo(base, primefactors, 2);
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
				cout << den << endl;
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
					ss << "-" << base << " ^ (" << a << " / " << den << ")";
					t = ss.str();              //2^(2/3)

				}
				else if ((*i).second > den)
				{
					if (den < 0)
					{
						den *= -1;
						if ((*i).second == den)
						{
							ostringstream ss;
							b = (pow(base, den));
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
						ss << "-" << base << " ^ (" << a << " / " << den << ")";
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
						ss << "1 / " << base << " ^ (" << a << " / " << den << ")";
						t = ss.str();
					}
					else
					{
						ostringstream ss;
						ss << base << " ^ (" << a << " / " << den << ")";
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
						ss << base << " ^ (" << a << " / " << den << ")";
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Exponents::calculate(string v1, string v2, string op) {

	string a, o, n;
	double b, c, d, e, top, bot, orange, banana;
	stringstream sn(v1);
	sn >> d;
	stringstream ss(v2);
	ss >> e;

	if (isAlpha(v2) == false && isFraction(v2) == true){
		int d, e;
		string f2 = "/";
		size_t slash = v2.find(f2);
		string den = v2.substr(slash + 1);
		stringstream st(den);
		st >> e;
		stringstream sn(v1);
		sn >> d;

		if (d < 0 && e % 2 == 0) { //&& (v1 != "e" || v2 !="e") && (v1!= "pi" ||v2 != "pi")) {
//			throw exception("Error: cannot take the even root of a negative number");

		}
	}

	//start
	if (v1 == "e" || v1 == "pi") {
		if (v2 == "0") {
			a = "1";
		}
		else if (v2 == "1"){
			a = v1;
		}
		else if (isFraction(v2) == true) {
			a = v1 + " ^ " + "(" + v2 + ")";
		}
		else {
			a = v1 + " ^ " + v2;
		}

	}
	else if (v2 == "e" || v2 == "pi") {
		if (v1 == "0")
		{
			a = "0";
		}
		else if (v1 == "1")
		{
			a = "1";
		}
		else if (isFraction(v1) == true) {
			a = "(" + v1 + ") ^ " + v2;
		}
		else {
			a = v1 + " ^ " + v2;
		}
	}
	else if ((v1 != "e" || v2 != "e") && (isAlpha(v1) == true || isAlpha(v2) == true)){
		if (e == 1)
		{
			a = v1;
		}
		else if (isFraction(v1) == true) {
			a = "(" + v1 + ") ^ " + v2;
		}
		else if (e < 0)
		{
			if (isFraction(v2) == true) {
				int i;
				for (i = 0; i < v2.size(); i++)
				{
					if (v2[i] == '/')
					{
						break;
					}
				}
				string str = v2.substr(0, i);
				string str2 = v2.substr(i + 1);
				stringstream ss(str);      //num
				ss >> orange;
				stringstream sm(str2);    //den
				sm >> banana;
				if (orange < 0) {
					orange *= -1;
					ostringstream sb;   //num
					sb << orange;
					ostringstream sg;   //den
					sg << banana;
					o = sb.str();
					n = sg.str();
					a = "1 / " + v1 + " ^ (" + o + " / " + n + ")";
				}
				else {
					e *= -1;
					string t;
					ostringstream ss;
					ss << e;
					t = ss.str();
					a = "1 / " + v1 + " ^ " + t;
				}
			}

			else if (e == -1) {
				a = "1 / " + v1;
			}

			else if (e != 0)
			{
				a = v1 + " ^ " + v2;

			}
		}
		else
		{
			a = "1";
		}
	}
	else if (isFraction(v1) == true && isFraction(v2) == false) { //if the first operand is a fraction, second is not, e.g. (1/2)^2
		//  string openPar = "(";
		string f2 = "/";
		size_t slash = v1.find(f2);		//position of "/"
		//size_t par = v1.find(openPar);	//pos of open parentheses
		string num = v1.substr(0, slash);	//take in whatever is after open parentheses to be numerator
		string den = v1.substr(slash + 1);   //take in whatever is after "/" to be denominator
		stringstream numerator(num);			//convert string of numerator and denominator to double
		numerator >> top;
		stringstream denominator(den);
		denominator >> bot;
		b = top;
		c = bot;
		if (bot != 0) {
			for (double i = 1; i < e; i++) {   //raise the numerator by the power
				b = b*top;
			}
			for (double j = 1; j < e; j++) {   //raise the denominator by the power
				c = c*bot;
			}
			ostringstream frac;			//convert to string
			frac << "(" << b << " / " << c << ")";
			string k = frac.str();
			string t = Operation::fractionReduction(k);
			a = t;

		}
		else if (b == c){
			a = "1";
		}
		else if (e == 0) {
			a = "1";
		}

		return a;
	}

	else if ((isFraction(v1) == false && isFraction(v2) == true)){
		NthRoot* root = new NthRoot();
		a = root->simplify(v2, v1, op);

	}
	else if ((isFraction(v1) == true && isFraction(v2) == true)) {
		return v1 + " ^ " + v2;
	}
	else {
		b = d;
		if (e == 0) {
			b = 1;
			ostringstream general;
			general << b;
			a = general.str();
		}
		else {
			for (double i = 1; i < e; i++) {
				b = b*d;       //25*25
			}
			ostringstream general;
			general << b;
			a = general.str();
		}

		if (b < 0 && e < 0) {          //negative exponents
			e *= -1;
			for (double i = 1; i < e; i++) {
				b = b*d;
			}
			int y;
			y = (int)e;
			if (y % 2 == 0) {         //even
				ostringstream gen;
				gen << b;
				a = "(-1 / " + gen.str() + ")";
			}
			else {                 //odd
				b *= -1;
				ostringstream gen;
				gen << b;
				a = "(-1 / " + gen.str() + ")";
			}
		}

		else if (e < 0) {
			e *= -1;
			for (double i = 1; i < e; i++) {
				b = b*d;
			}
			ostringstream general;
			general << b;
			a = "(1 / " + general.str() + ")";
		}
	}

	return a;
}



////////////////////////////////////////////////////////////////////////////////////////