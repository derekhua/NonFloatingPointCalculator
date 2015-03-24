#include "Calculator.h"
#include <cmath>

string Logn::simplify(string n, string degree, string op) {
	return "";
}
bool Logn::check(string value1, string value2) {
	return true;
}

string Logn::calculate(string base, string num, string action)
{
	double dubbase;
	double dubnum;
	bool basefraction = false;
	bool numfraction = false;
	bool baseexpo = false;
	bool numexpo = false;
	//cout << "The base is " << base << endl;
	//cout << "The num is " << num << endl;
	//returns 1 if base and num are same
	if (base == "pi" && num == "pi")
		return "1";
	if (base == "e" && num == "e")
		return "1";
	//if the num is the same as the base, but raised to a power....log_e:e ^ 3
	if (base == "e" || base == "pi")
	{
		for (int i = 0; i < num.length(); i++)
		{
			if (num[i] == '^')
			{
				int left;
				int rightp;
				for (int x = i; x < num.length(); x++)
				{
					string exponent;
					if (num[x] == '(')
						left = x;
					else if (num[x] == ')')
					{
						rightp = x;
						exponent = num.substr(left + 1, (rightp - left) - 1);
					}
					else
					{
						exponent = num.substr(i + 2);
					}
					//cout << "the exponent is: " << exponent << endl;
					if (base == num.substr(0, i - 1))
						return exponent;
				}
			}
		}
	}
	if (num == "e" || num == "pi")
	{
		//if the base is the same as the num, but raised to a power...log_e ^ 3:e
		for (int i = 0; i < base.length(); i++)
		{
			if (base[i] == '^')
			{
				int left;
				int rightp;
				for (int x = i; x < base.length(); x++)
				{
					string exponent;
					if (base[x] == '(')
						left = x;
					else if (base[x] == ')')
					{
						rightp = x;
						exponent = base.substr(left + 1, (rightp - left) - 1);
					}
					else
					{
						exponent = base.substr(i + 2);
					}
					//cout << "the exponent is: " << exponent << endl;
					if (num == base.substr(0, i))
					{
						string Result;
						Result = "1 / " + exponent;
						return exponent;
					}
				}
			}
		}
	}
	//checks if base has exponent
	int j; //location of the '^' for the base
	for (j = 0; j < base.length(); j++)
	{
		if (base[j] == '^')
		{
			baseexpo = true;
			break;
		}
	}
	//checks if base has a fraction
	int i; //location of the '/' for the base
	for (i = 0; i < base.length(); i++)
	{
		if (base[i] == '/')
		{
			basefraction = true;
			break;
		}
	}
	//if base is a fraction, this converts the base to a double
	double num1, num2;
	if (basefraction == true && baseexpo == false)
	{
		stringstream str2;
		stringstream str3;
		string numerator = base.substr(0, i);
		string denominator = base.substr(i + 1);
		str2 << numerator;
		str3 << denominator;
		str2 >> num1;
		str3 >> num2;
		dubbase = num1 / num2;
	}
	//this makes the base to a "int" if not a fraction and doesnt have expo
	if (basefraction == false && baseexpo == false)
	{
		string number = base.substr(0);
		stringstream str;
		str << number;
		str >> dubbase;
	}
	//checks to see if the num has a fraction
	int y; //location of '/' for num
	for (y = 0; y < num.length(); y++)
	{
		if (num[y] == '/')
		{
			numfraction = true;
			break;
		}
	}
	//checks to see if the num has an expo
	int z; //location of '^' for num
	for (z = 0; y < num.length(); z++)
	{
		if (num[z] == '^')
		{
			numexpo = true;
			break;
		}
	}
	//turns the num into a double if its a fraction....1 / 2
	double num3, num4;
	if (numfraction == true && numexpo == false)
	{
		stringstream str4;
		stringstream str5;
		string numerator2 = num.substr(0, y - 1);
		string denominator2 = num.substr(y + 2);
		//cout << "the numerator is: " << numerator2 << endl;
		//cout << "the denominator is: " << denominator2 << endl;
		//cout << "the num is: " << num << endl;
		str4 << numerator2;
		str5 << denominator2;
		str4 >> num3;
		str5 >> num4;
		dubnum = num3 / num4;
		//cout << "The num is: " << dubnum << endl;
	}
	//turns num into a double if not a fraction and doesnt have exponent
	if (numfraction == false && numexpo == false)
	{
		stringstream str1;
		str1 << num;
		str1 >> dubnum;
		//cout << "The num is: " << intnum << endl;
	}
	//turns base into a double if has exponent and fraction
	if (basefraction == true && baseexpo == true && i>j) // log_2 ^ (1 / 2):4
	{
		stringstream str;
		stringstream str2;
		stringstream str3;
		//j location of ^	
		string subbase = base.substr(0, j - 1);
		double dubsubbase;
		//j+2 location of (
		int leftp = j + 2;
		int rightp;
		for (int x = 0; x < base.length(); x++)
		{
			if (base[x] == ')')
			{
				rightp = x;
				break;
			}
		}
		string numerator = base.substr(leftp + 1, i - leftp - 2);

		//cout << "numerator: "<<numerator << endl;
		string denominator = base.substr(i + 2, rightp - i - 2);
		//cout << "denominator: "<<denominator << endl;
		str2 << numerator;
		str3 << denominator;
		str2 >> num1;
		str3 >> num2;
		//cout << num1 << endl;
		//cout << num2 << endl;
		double exponent = num1 / num2;
		str << subbase;
		str >> dubsubbase;
		dubbase = pow(dubsubbase, exponent);
		//cout << "dubbase" << dubbase << endl;
	}
	//turns num into a double if has exponent and fraction
	if (numfraction == true && numexpo == true && y>z) // log_e:4 ^ (1 / 2)
	{
		//z location of ^
		string subnum = num.substr(0, z);
		double dubsubnum;
		//z+2 location of (
		int leftp = z + 2;
		int rightp;
		for (int i = z; i < num.length(); i++)
		{
			if (num[i] == ')')
			{
				rightp = i;
				break;
			}
		}
		stringstream str2;
		stringstream str3;
		string numerator = num.substr(leftp + 1, y - leftp - 2);
		string denominator = num.substr(y + 2, rightp - y - 2);
		str2 << numerator;
		str3 << denominator;
		str2 >> num1;
		str3 >> num2;
		double exponent = num1 / num2;
		stringstream str;
		str << subnum;
		str >> dubsubnum;
		dubnum = pow(dubsubnum, exponent);
	}
	//turns num into a double if has exponent and fraction
	if (numfraction == true && numexpo == true && y<z) // log_e:(1 / 2) ^ 2
	{
		//z location of ^
		string exponent = num.substr(z + 1);
		double dubexpo;
		int leftp = 0;
		int rightp;
		for (int i = z; i < num.length(); i++)
		{
			if (num[i] == ')')
			{
				rightp = i;
				break;
			}
		}
		stringstream str2;
		stringstream str3;
		string numerator = num.substr(leftp + 1, y - leftp - 2);
		string denominator = num.substr(y + 2, rightp - y - 2);
		str2 << numerator;
		str3 << denominator;
		str2 >> num1;
		str3 >> num2;
		double numbase = num1 / num2;
		stringstream str;
		str << exponent;
		str >> dubexpo;
		dubnum = pow(numbase, dubexpo);
	}

	if (dubnum == dubbase)
		return "1";
	if (true)
	{
		for (int i = 0; i < 10; i++)
		{
			double power = ((double)1 / (double)i);
			double check = pow(dubbase, power);
			//round up or down really close
			if (abs(check - dubnum) < 0.000001 && floor(check) == dubnum)
				check = floor(check);
			if (abs(check - dubnum) < 0.000001 && ceil(check) == dubnum)
				check = ceil(check);
			if (dubnum == check)
			{
				string Result;
				ostringstream convert;
				convert << i;
				Result = convert.str();
				string total;
				total = "1 / " + Result;
				return total;
				break;
			}
		}
		//cout << "dubbase: " << dubbase << endl;
		for (int i = (-100); i<100; i++)
		{
			double input = pow(dubbase, i);
			if (abs(ceil(input) - dubnum) < 0.000001 || abs(floor(input) - dubnum) < 0.000001)
			{
				string Result; // string which will contain the result
				ostringstream convert; // stream used for the conversion
				convert << i; // insert the textual representation of 'Number' in the characters in the stream
				Result = convert.str();
				return Result;
				break;
			}
		}
	}
	//if none of the above return values, then the input will be returned.
	//splits the log and uses the change of base formula
	if (numfraction == false)
	{
		vector<int> primefactors;
		primeFactorizationD(dubnum, primefactors, 2);
		string total = "";
		string Result;
		int count1 = 0;
		int count2 = 0;
		int distinct = 1;
		for (int i = 0; i<primefactors.size() - 1; i++)
		{
			if (primefactors.at(i) == primefactors.at(i + 1))
			{
			}
			else
			{
				distinct++;
			}
		}
		//cout << "distinct: " << distinct << endl;
		for (int i = 0; i<primefactors.size(); i++)
		{
			ostringstream convert;
			convert << primefactors.at(i);
			Result = convert.str();
			if (Result == base)
			{
				count1++;
			}
			if (Result != base)
			{
				count2++;
			}
		}
		if (count1 > 0)
		{
			stringstream str;
			str << count1;
			string counter1;
			str >> counter1;
			total += counter1 + " + ";
		}
		vector<string> temp;
		//temp[0] = primefactors.at(0);
		for (int i = 0; i<primefactors.size(); i++)
		{
			ostringstream convert;
			convert << primefactors.at(i);
			Result = convert.str();
			if (Result != base)
			{
				string returner = "(log_10:" + Result + "/log_10:" + base + ")";
				temp.push_back(returner);
			}
		}
		//cout << temp.size() << endl;
		//cout << temp.at(0) << endl;
		int track = 1;
		//temp.push_back("");
		for (int i = 1; i<temp.size() + 1; i++)
		{
			if (i == temp.size())
			{
				ostringstream convert;
				convert << track;
				Result = convert.str();
				total += Result + temp.at(i - 1) + " + ";
				break;
			}
			if (temp.at(i) == temp.at(i - 1))
			{
				track++;
			}
			else
			{
				ostringstream convert;
				convert << track;
				Result = convert.str();
				total += Result + temp.at(i - 1) + " + ";
				track = 1;
			}
		}
		total.pop_back();
		total.pop_back();
		return total;
	}

	//returns the log if it can’t be simplified or split apart
	string concat = "(log_10:" + num + " / log_10:" + base + ")";
	return concat;
	//return "end";
}




Logn::Logn() {
	//do nothing
}
Logn::~Logn() {
	//do nothing
}
void Logn::primeFactorizationD(int num, vector<int>& factors, int primes)
{
	if (num % primes == 0)
	{
		factors.push_back(primes);
		primeFactorizationD(num / primes, factors, primes);
	}
	else if (primes <= num)
	{
		primeFactorizationD(num, factors, primes + 1);
	}
}
