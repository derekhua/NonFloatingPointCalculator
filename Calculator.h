#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <exception>
#include <string>
#include <math.h>
#include <ctype.h>
#include <map>

using namespace std;

template class std::stack <char>;
template class std::stack <string>; //all three are new to compile
template class std::queue <string>;

class Algorithm {
private:
	stack<char> mystack;//for operators (each are 1 digit)
	stack<string> mystack2;
	queue<string> myqueue;
	vector <string> queue;
	vector <char> stack; //change from vector of strings
	string compInput; //change from input
	string result;
public:
	void shuntingYard(string expression); //change from return type string
	string reversePolish(string expression);
	string formatExpression(string expression);
	bool enclosingParens(string expression);
	void ensureEnclosingParens(string* exp);
	string ensureEnclosingParens(string expression);
	bool replace(std::string& str, const std::string& from, const std::string& to);
	string replaceAll(std::string& str, const std::string& from, const std::string& to);
	void formatSQRT(string* exp);
	void formatNRT(string* exp);
	void formatFAC(string* exp);
	void formatLOG(string* exp);
	void formatLOGS(string* exp);
	void formatNEG(string* exp);
	void formatNEGfront(string* exp);
	void formatNegOper(string* exp);
	void formatCompress(string* exp);
	void formatImpMult(string* exp);
	bool isOperator();
	bool isSelection(string selection);
	bool isNumNext(int i, string expression);
	bool ansFound(string* exp);
	bool ansFoundNth(string* exp);
	void formatANSfromN(string* exp);
	void formatANSfromNMult(string* exp);
	void formatANS(string* exp);
	bool wantDouble();
	void formatMultOpe(string* exp);
	double toDouble(string answer);
	string acceptableAns();
	bool isFOIL(string* exp);
	void formatFOIL(string* exp);
	bool isAcceptableAns();
	void turningSign(string* exp);
	Algorithm(); //constructor
	~Algorithm(); //deconstructor
};


class Operation {
	

	private:
		string input;
		string results;

	public:
		Operation();
		~Operation();
		virtual bool check(string value1, string value2) = 0;
		virtual string calculate(string value1, string value2, string oper) = 0;
		virtual string simplify(string results, string oper, string oper2) = 0;
		string fractionReduction(string input);
		string fractionReductionHelper(int i, int num, int deno, string numeratorOfNonDigits, string denominatorOfNonDigits);
		double changeFractionToDecimal(string fraction, string *numeratorOfNonDigits);
		bool checkIfFraction(string input, string *numerator, string *numeratorOfNonDigits, string *denominator, string *denominatorOfNonDigits);
		bool checkIfDecimal(string input, string *numerator, string *numeratorOfNonDigits, string *decimal, int *round);
		bool containsNonDigit(string input, string *nonDigit);
		vector<int> primeFactorization(int num);
		void primeFactorizationHelper(int i, int num, vector<int> *primes);
		void printVector(vector<int> primes);
		bool isOperand(char value);
		int gcd(int x, int y);
		bool doesContainNum(string oper);


	};


class Adding { //dummy class used for early testing (ints only)
private:
	//nothing
public:
	Adding();
	~Adding();
	string calculate(string value1, string value2, string action);
};


class Addition : public Operation{

public:
	Addition();
	~Addition();
	bool check(string value1, string value2);
	string calculate(string value1, string value2, string oper);
	string simplify(string results, string oper, string oper2);
};


class Subtraction : public Operation{

public:
	Subtraction();
	~Subtraction();
	bool check(string value1, string value2);
	string calculate(string value1, string value2, string oper);
	string simplify(string results, string oper, string oper2);

};



class Multiplication : public Operation{
private:
	//nothing
public:
	Multiplication();
	~Multiplication();
	bool isAlpha(string value);
	bool isFraction(string value);
	bool check(string value1, string value2);
	string simplify(string value1, string value2, string operation);
	string calculate(string numb1, string numb2, string ope);
};


class Division : public Operation{
private:
	//nothing
public:
	Division();
	~Division();
	bool isAlpha(string value);
	bool isFraction(string value);
	bool check(string value1, string value2);
	string  simplify(string value1, string value2, string operation);
	string calculate(string numb1, string numb2, string ope);
};


class Exponents : public Operation{
private: 
	//nothing
public:
	Exponents();
	~Exponents();
	bool isAlpha(string value);
	bool isFraction(string value);
	void primeFacexpo(int num, vector<int>& factors, int primes);
	bool check(string value1, string value2);
	string simplify(string value1, string value2, string operation);
	string calculate(string value1, string value2, string operation);

};


class NthRoot : public Operation{
public:
	NthRoot();
	~NthRoot();
	bool isFraction(string value);
	bool isNeg(string input);
	bool isAlpha(string value);
	void primeFacroot(int num, vector<int> &some, int p);
	string simplify(string n, string degree, string op);
	bool check(string value1, string value2);
	string calculate(string value1, string value2, string operation);

	};


class Logn : public Operation{
private:
	//nothing
public:
	Logn();
	~Logn();
	string simplify(string n, string degree, string op);
	bool check(string value1, string value2);
	string calculate(string base, string num, string action);
	void primeFactorizationD(int num, vector<int>& factors, int primes);
};


class Factorial : public Operation{
private:
	//nothing
public:
	Factorial();
	~Factorial();
	string calculate(string num1, string num2, string action);
	string simplify(string n, string degree, string op);
	bool check(string value1, string value2);
	int factorialHelper(int factorial);
};
