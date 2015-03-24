#include "Calculator.h"

Operation::Operation(){
	//nothing to construct
}
Operation::~Operation(){
	//nothing to destruct
}


string Operation::fractionReduction(string input){

	//initialization of variables
	string numerator = "";
	string decimal = "0";
	string numeratorOfNonDigits = "";
	string denominatorOfNonDigits = "";
	string denominator = "1";
	string results = "";
	int intOfresults;
	int round = 0;
	bool isFraction = false;
	bool isDecimel = false;


	//check for negative value
	bool isNegative = false;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '-') {
			isNegative = true;
		}
	}

	//check for powers
	bool numIsPower = false;
	bool denoIsPower = false;
	int powerNum = 1;
	int powerDen = 1;
	int i = 0;
	//check numerator powers
	while (i < input.length() && input[i] != '/' && input[i] != ')') {
		if (numIsPower && isdigit(input[i])) {
			stringstream str;
			str << input[i];
			str >> powerNum;
		}
		else if (input[i] == '^') {
			numIsPower = true;
		}

		i++;
	}
	i++;

	//check denominator powers
	while (i < input.length() && input[i] != ')') {
		if (denoIsPower && isdigit(input[i])) {
			stringstream str;
			str << input[i];
			str >> powerDen;
		}
		else if (input[i] == '^') {
			denoIsPower = true;
		}

		i++;
	}


	//check if function

	isFraction = checkIfFraction(input, &numerator, &numeratorOfNonDigits, &denominator, &denominatorOfNonDigits);
	if (!isFraction){

		isDecimel = checkIfDecimal(input, &numerator, &numeratorOfNonDigits, &decimal, &round);
	}


	//simplify if it is a function
	if (isFraction)
	{

		int num;
		int deno;

		if (numerator == "") {

			num = 1;
		}
		else {
			num = stoi(numerator);
		}


		if (denominator == "") {
			deno = 1;

		}
		else {
			deno = stoi(denominator);
		}



		//adjust according to powers
		stringstream pn;
		stringstream dn;

		if (numeratorOfNonDigits == denominatorOfNonDigits) {

			if (powerNum == powerDen) {


				numeratorOfNonDigits = "";
				denominatorOfNonDigits = "";
			}
			else if (powerNum > powerDen) {
				powerNum = powerNum - powerDen;
				pn << powerNum;
				numeratorOfNonDigits = numeratorOfNonDigits + " ^ ( " + pn.str() + " ) ";
				denominatorOfNonDigits = "";
			}
			else if (powerNum < powerDen) {


				powerDen = powerDen - powerNum;
				dn << powerDen;
				denominatorOfNonDigits = denominatorOfNonDigits + " ^ ( " + dn.str() + " ) ";
				numeratorOfNonDigits = "";
			}
		}
		else {

			if (powerNum > 1) {
				pn << powerDen;
				numeratorOfNonDigits = numeratorOfNonDigits + " ^ ( " + pn.str() + " ) ";
			}
			if (powerDen > 1) {

				dn << powerDen;
				denominatorOfNonDigits = denominatorOfNonDigits + " ^ ( " + dn.str() + " ) ";
			}
		}

		//if it is a function and denominator is 0 then it throws an error!
		if (deno == 0) {
			throw invalid_argument("error! denominator can not be 0!");
		}
		//check if a whole number!
		else if (num % deno == 0)
		{


			//check if it is a non digigt simplify 2 pi / 4
			intOfresults = num / deno;

			//cout<<"fraction " << numerator<<numeratorOfNonDigits<<"/"<< denominator<<denominatorOfNonDigits;
			//cout<<" can be reduced to whole number: " << intOfresults<<numeratorOfNonDigits <<endl;
			ostringstream oss;
			if (denominatorOfNonDigits != " " && denominatorOfNonDigits != "")
			{
				oss << intOfresults;
				results = oss.str() + numeratorOfNonDigits + " / " + denominatorOfNonDigits;
			}
			else {

				oss << intOfresults;
				results = oss.str() + numeratorOfNonDigits;
			}
		}
		//else simplify the fraction
		else {

			results = fractionReductionHelper(2, num, deno, numeratorOfNonDigits, denominatorOfNonDigits);
		}

	}
	else if (isDecimel) {
		// int createNum = stoi(decimal);
		int decimalPlaces;
		if (round == 1) {
			decimalPlaces = 10;
		}
		else if (round == 2) {
			decimalPlaces = 100;

		}
		else if (round == 3) {
			decimalPlaces = 1000;

		}


		numerator = numerator + decimal;
		int numDecimals = stoi(numerator);
		results = fractionReductionHelper(2, numDecimals, decimalPlaces, numeratorOfNonDigits, denominatorOfNonDigits);
	}
	else
	{
		//cout<<"number is simplified";
		denominator = 1;
		if (powerNum>1) {
			ostringstream pn;
			pn << powerNum;
			results = numerator + numeratorOfNonDigits + " ^ ( " + pn.str() + " ) ";
		}
		else {
			results = numerator + numeratorOfNonDigits;
		}

	}

	if (isNegative) {
		// results = "-" + results;
	}

	//cout<<"results: "<< results<<endl;
	return results;


}

string Operation::fractionReductionHelper(int i, int num, int deno, string numeratorOfNonDigits, string denominatorOfNonDigits) {
	//cout<<"reduce ";
	string results;
	string numerator;
	string denominator;


	int gcdf = gcd(num, deno);
	num = num / abs(gcdf);
	deno = deno / abs(gcdf);

	ostringstream oss;

	if (deno == 1) {

		if (denominatorOfNonDigits != "") {

			oss << num << numeratorOfNonDigits << " / " << deno << denominatorOfNonDigits;
			results = oss.str();
		}
		else {

			oss << num << numeratorOfNonDigits;
			results = oss.str();
		}

	}
	else{

		oss << num << numeratorOfNonDigits << " / " << deno << denominatorOfNonDigits;
		results = oss.str();
	}

	/*
	vector<int> numPrimes = primeFactorization(abs(num));
	vector<int> denoPrimes = primeFactorization(abs(deno));

	int numPrimesLength = numPrimes.size();
	int denoPrimesLength = denoPrimes.size();
	int length;
	if (numPrimesLength >= denoPrimesLength) {
	length = numPrimesLength;
	}
	else
	{
	length = denoPrimesLength;
	}

	for (int i = 0; i < numPrimesLength; i++) {
	for (int j = 0; j < denoPrimesLength; j++) {
	if (numPrimes[i] == denoPrimes[j]) {
	//cout<<"num: "<<num<<" numeratr primes"<<numPrimes[i]<<endl;
	numPrimes[i] = 1;
	denoPrimes[j] = 1;
	break;
	}
	}
	}

	//cout<<"after"<<endl;
	int numI = 1;
	int denI = 1;
	for (int i = 0; i<numPrimesLength; i++) {
	numI = numI * numPrimes[i];
	//cout<<"num: "<<num<<" numeratr primes"<<numPrimes[i]<<endl;
	}
	for (int i = 0; i<denoPrimesLength; i++) {
	denI = denI * denoPrimes[i];
	// cout<<"den: "<<deno<<" den primes"<<denoPrimes[i]<<endl;
	}

	ostringstream oss;
	oss << numI << numeratorOfNonDigits << " / " << denI << denominatorOfNonDigits;
	results = oss.str();


	*/


	/*


	if (i > deno || i > num) {

	ostringstream oss;
	oss << num << numeratorOfNonDigits << " / " << deno << denominatorOfNonDigits;
	results = oss.str();
	}
	else if ( (num % i == 0) && (deno % i == 0)  ) {
	num = num / i;
	deno = deno / i;
	results = fractionReductionHelper(2,num,deno,numeratorOfNonDigits,denominatorOfNonDigits);
	}
	else {
	results = fractionReductionHelper(i+1,num,deno,numeratorOfNonDigits,denominatorOfNonDigits);
	}
	*/

	return results;
}

vector<int> Operation::primeFactorization(int num){
	vector<int> primes;
	primeFactorizationHelper(2, num, &primes);
	return primes;
}

void Operation::primeFactorizationHelper(int i, int num, vector<int> *primes) {




	if (num % i == 0)
	{
		primes->push_back(i);
		primeFactorizationHelper(i, num / i, primes);
	}
	else if (i <= num)
	{
		primeFactorizationHelper(i + 1, num, primes);
	}


}


void Operation::printVector(vector<int> vector)
{
	cout << "This vector has ";
	for (int i = 0; i < vector.size(); i++) {
		cout << vector[i] << ",";
	}
	cout << endl;
}




bool Operation::checkIfFraction(string input, string *numerator, string *numeratorOfNonDigits, string *denominator, string *denominatorOfNonDigits) {
	bool isFraction = false;
	string decimal;
	*numerator = "";
	*numeratorOfNonDigits = "";
	*denominator = "";
	*denominatorOfNonDigits = "";
	bool isPower = false;
	bool isNegative = false;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '^') {
			isPower = true;
		}
		if (isPower && input[i] == ')')
		{
			isPower = false;
		}
		if (input[i] == '-' && !isNegative) {
			*numerator = *numerator + input[i];
			isNegative = true;
		}
		if (!isPower) {
			if (!isFraction && isdigit(input[i]))
			{

				*numerator = *numerator + input[i];
			}
			else if (!isFraction && !isdigit(input[i]) && !isOperand(input[i]))
			{


				*numeratorOfNonDigits = *numeratorOfNonDigits + input[i];
			}
			else if (input[i] == '/') {
				*denominator = "";
				isFraction = true;
			}
			else if (isFraction && isdigit(input[i])) {

				*denominator = *denominator + input[i];
			}
			else if (isFraction && !isdigit(input[i]) && !isOperand(input[i]))
			{
				*denominatorOfNonDigits = *denominatorOfNonDigits + input[i];
			}
		}



	}
	if (isFraction)
	{
		return true;
	}
	else {
		return false;
	}

}

bool Operation::checkIfDecimal(string input, string *numerator, string *numeratorOfNonDigits, string *decimal, int *round) {


	bool isDecimel = false;
	*numerator = "";
	*numeratorOfNonDigits = "";
	*decimal = "";
	*round = 0;
	bool isPower = false;
	bool isNegative = false;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '^') {
			isPower = true;
		}
		if (isPower && input[i] == ')')
		{
			isPower = false;
		}
		if (input[i] == '-' && !isNegative)
		{

			*numerator = *numerator + input[i];
			isNegative = true;
		}

		if (!isPower) {

			if (isdigit(input[i]) && !isDecimel)
			{

				*numerator = *numerator + input[i];
			}
			else if (!isdigit(input[i]) && !isOperand(input[i]))
			{
				*numeratorOfNonDigits = *numeratorOfNonDigits + input[i];
			}
			else if (input[i] == '.') {
				*decimal = "";
				isDecimel = true;
			}
			else if (isDecimel && isdigit(input[i]) && *round<3) {
				*round = *round + 1;
				*decimal = *decimal + input[i];
			}
		}





	}
	if (isDecimel)
	{
		return true;
	}
	else {
		return false;
	}

}

bool Operation::containsNonDigit(string input, string *nonDigit)
{
	bool isNonDigit = false;
	*nonDigit = "";
	for (int i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i]) && input[i] != '/')
		{
			isNonDigit = true;
			*nonDigit = *nonDigit + input[i];
		}
	}

	return isNonDigit;
}


double Operation::changeFractionToDecimal(string fraction, string *numeratorOfNonDigits)
{
	*numeratorOfNonDigits = "";
	string numerator = "";
	string denominator = "";
	string denominatorOfNonDigits = "";
	bool isFraction = checkIfFraction(fraction, &numerator, numeratorOfNonDigits, &denominator, &denominatorOfNonDigits);
	*numeratorOfNonDigits = *numeratorOfNonDigits + " / " + denominatorOfNonDigits;
	double num = 1;
	if (numerator != "") {
		num = stod(numerator);
	}

	if (isFraction)
	{
		double deno = 1;
		if (numerator != "") {
			deno = stod(denominator);
		}
		return num / deno;
	}
	else
	{

		return num;
	}
}

bool Operation::isOperand(char value)
{
	if (value == '(' || value == ')' || value == '^' || value == '/' || value == '-' || value == '.' || value == ' ') {
		return true;
	}
	else
	{
		return false;
	}
}

int Operation::gcd(int u, int v) {


	if (v != 0) {
		return gcd(v, u%v);
	}
	else
	{
		return u;
	}

}

bool Operation::doesContainNum(string oper)
{
	bool num = false;
	for (int i = 0; i < oper.length(); i++) {
		if (isdigit(oper[i])) {
			num = true;
		}
	}
	return num;
}
