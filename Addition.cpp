#include "Calculator.h"


Addition::Addition() {

}

Addition::~Addition() {

}

bool Addition::check(string value1, string value2)

{
	string nonDigit1 = "";
	string nonDigit2 = "";
	containsNonDigit(value1, &nonDigit1);
	containsNonDigit(value2, &nonDigit2);
	if (nonDigit1 == nonDigit2) {
		return true;
	}
	else
	{
		return false;
	}
}

string Addition::calculate(string value1, string value2, string oper) {

	//value1 = simplify(value1,"","");
	//value2 = simplify(value2,"","");

	string results = "";

	string numeratorOfNonDigits1 = "";
	string numerator1 = "";
	string denominator1 = "";
	string denominatorOfNonDigits1 = "";
	string NonDigits1;



	string numeratorOfNonDigits2 = "";
	string numerator2 = "";
	string denominator2 = "";
	string denominatorOfNonDigits2 = "";
	string NonDigits2;
	bool isFraction2 = checkIfFraction(value2, &numerator2, &numeratorOfNonDigits2, &denominator2, &denominatorOfNonDigits2);

	vector <string> secondQ;
	vector <string> express;
	//  secondQ.push_back(value1);

	string newValue = "";

	//int k = 0;

	for (int i = 0; i < value1.size(); i++) {
		if (value1[i] == '+') {
			secondQ.push_back(newValue);
			express.push_back(newValue);
			newValue = "";
		}
		else if (value1[i] == ' ') {
			continue;
		}
		else{
			newValue = newValue + value1[i];

		}
	}

	secondQ.push_back(newValue);
	//value1 = secondQ[0];

	//printVector(secondQ);

	string n, nd, d, dd;

	for (int i = 0; i < secondQ.size(); i++) {
		n = ""; nd = ""; d = ""; dd = "";

		checkIfFraction(secondQ[i], &n, &nd, &d, &dd);

		if (nd == numeratorOfNonDigits2 && secondQ.size() > 1) {

			value2 = calculate(value2, secondQ[i], "");

			value1 = secondQ[i + 1];


		}

		else
		{
			value1 = secondQ[i];
		}

	}



	bool isFraction1 = checkIfFraction(value1, &numerator1, &numeratorOfNonDigits1, &denominator1, &denominatorOfNonDigits1);
	isFraction2 = checkIfFraction(value2, &numerator2, &numeratorOfNonDigits2, &denominator2, &denominatorOfNonDigits2);






	ostringstream oss;

	double numeratorD1;
	double numeratorD2;
	double denominatorD1;
	double denominatorD2;





	int resultsN;


	if (!doesContainNum(denominator1)) {
		if (denominator1[0] == '-')
			denominatorD1 = -1;
		else
			denominatorD1 = 1;
	}
	else
	{
		denominatorD1 = stod(denominator1);
	}

	if (!doesContainNum(denominator2)) {
		if (denominator2[0] == '-')
			denominatorD2 = -1;
		else
			denominatorD2 = 1;

	}
	else
	{
		denominatorD2 = stod(denominator2);
	}

	if (!doesContainNum(numerator1)){
		if (numerator1[0] == '-')
			numeratorD1 = -1;
		else
			numeratorD1 = 1;
	}
	else
	{
		numeratorD1 = stod(numerator1);
	}

	if (!doesContainNum(numerator2)) {
		if (numerator2[0] == '-')
			numeratorD2 = -1;
		else
			numeratorD2 = 1;
	}
	else
	{
		numeratorD2 = stod(numerator2);
	}
	ostringstream changeToFraction1;
	changeToFraction1 << numeratorD1 << numeratorOfNonDigits1 << " / " << denominatorD1 << denominatorOfNonDigits1;
	value1 = changeToFraction1.str();

	ostringstream changeToFraction2;
	changeToFraction2 << numeratorD2 << numeratorOfNonDigits2 << " / " << denominatorD2 << denominatorOfNonDigits2;
	value2 = changeToFraction2.str();


	isFraction1 = checkIfFraction(value1, &numerator1, &numeratorOfNonDigits1, &denominator1, &denominatorOfNonDigits1);
	isFraction2 = checkIfFraction(value2, &numerator2, &numeratorOfNonDigits2, &denominator2, &denominatorOfNonDigits2);

	numeratorD1 = numeratorD1 * denominatorD2;
	numeratorD2 = numeratorD2 * denominatorD1;
	denominatorD2 = denominatorD1 * denominatorD2;


	if (isFraction1 && isFraction2) {
		int resultsD;


		if (check(denominatorOfNonDigits1, denominatorOfNonDigits2) && check(numeratorOfNonDigits1, numeratorOfNonDigits2))
		{
			if (numeratorOfNonDigits1 == numeratorOfNonDigits2 && numeratorOfNonDigits2 == denominatorOfNonDigits1 && numeratorOfNonDigits1 != "")
			{
				resultsN = numeratorD1 + numeratorD2;
				resultsD = denominatorD2;

				oss << resultsN << " / " << resultsD;


				if (resultsN == 0) {
					oss << 0;
					results = simplify(oss.str(), "", "");
				}
				else
				{


					results = simplify(oss.str(), "", "");

				}

			}
			else if (numeratorOfNonDigits1 == numeratorOfNonDigits2) {


				resultsN = numeratorD1 + numeratorD2;

				resultsD = denominatorD2;

				oss << resultsN << numeratorOfNonDigits1 << " / " << resultsD << denominatorOfNonDigits1;


				if (resultsN == 0) {
					oss << 0;
					results = simplify(oss.str(), "", "");
				}
				else
				{


					results = simplify(oss.str(), "", "");

				}

			}
		}

		else
		{
			results = simplify(value1, "", "") + " + " + simplify(value2, "", "");
		}

	}
	else if (isFraction1 || isFraction2)
	{

		results = simplify(value1, "", "") + " + " + simplify(value2, "", "");
	}
	else
	{
		if (numeratorOfNonDigits1 == numeratorOfNonDigits2) {

			resultsN = numeratorD1 + numeratorD2;




			if (resultsN == 0) {
				oss << 0;
				results = simplify(oss.str(), "", "");
			}
			else
			{
				oss << resultsN << numeratorOfNonDigits1;




				results = simplify(oss.str(), "", "");

			}
		}

		else
		{

			results = simplify(value1, "", "") + " + " + simplify(value2, "", "");
		}








	}


















	/*

	if(check(denominatorOfNonDigits1,denominatorOfNonDigits2))
	{

	if (numeratorOfNonDigits1 == numeratorOfNonDigits2 && numeratorOfNonDigits2 == denominatorOfNonDigits1 && numeratorOfNonDigits1 != "") {
	cout<<"tes";

	//doubleResults = val1 + val2;
	resultsN = numeratorI1 + numeratorI2;
	//  resultsD = denominatorI1 + denominatorI2;
	cout<<resultsN;

	oss << resultsN / resultsD;
	results = simplify(oss.str(),"","");
	}
	else if (numeratorOfNonDigits1 == numeratorOfNonDigits2) {


	//doubleResults = val1 + val2;
	resultsN = numeratorI1 + numeratorI2;
	resultsD = denominatorI1 + denominatorI2;

	if (resultsN == 0) {
	oss << 0;
	results = simplify(oss.str(),"","");
	}
	else
	{
	oss << resultsN / resultsD;
	results = simplify(oss.str(),"","") + numeratorOfNonDigits1;
	}


	}
	else if (denominatorOfNonDigits1 != "") {

	if (numeratorOfNonDigits1 != numeratorOfNonDigits2)
	{

	results = simplify(value1,"","") + "+" + simplify(value2,"","");

	}
	else
	{
	ostringstream change1;
	ostringstream ossNum1;
	ostringstream ossDen1;

	double numeratorD1 = stod(numerator1) * stod(denominator2);
	double denominatorD1 = stod(denominator1) * stod(denominator2);
	ossNum1<<numeratorD1;
	ossDen1<<denominatorD1;

	numerator1 = ossNum1.str();
	denominator1 = ossDen1.str();
	change1 << numerator1 << "/" << denominator1;
	value1 = change1.str();

	///////////////////////////////////
	ostringstream change2;
	ostringstream ossNum2;
	ostringstream ossDen2;

	double numeratorD2 = stod(numerator2) * stod(denominator1);
	double denominatorD2 = stod(denominator2) * stod(denominator1);
	ossNum2<<numeratorD2;
	ossDen2<<denominatorD2;

	numerator2 = ossNum2.str();
	denominator2 = ossDen2.str();
	change2 << numerator2 << "/" << denominator2;
	value2 = change2.str();

	// val1 = changeFractionToDecimal(value1,&NonDigits1);
	//val2 = changeFractionToDecimal(value2,&NonDigits2);

	//doubleResults = val1 + val2;

	resultsN = numeratorI1 + numeratorI2;
	resultsD = denominatorI1 + denominatorI2;

	oss << resultsN / resultsD;


	if (resultsD == 0) {
	oss << 0;
	results = simplify(oss.str(),"","");
	}
	else
	{
	oss << resultsN / resultsD;
	results = simplify(oss.str(),"","") + numeratorOfNonDigits1;
	}

	}
	}
	else
	{
	results = simplify(value1,"","") + "+" + simplify(value2,"","");
	}

	}
	else
	{

	results = simplify(value1,"","") + "+" + simplify(value2,"","");
	}

	*/



	return results;



}



string Addition::simplify(string results, string oper, string oper2)

{
	string simplify;
	simplify = fractionReduction(results);
	return simplify;
}
