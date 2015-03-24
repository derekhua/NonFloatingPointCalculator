#include "Calculator.h"

#define EPSILON .00000001

Multiplication::Multiplication() {

}
Multiplication :: ~Multiplication() {

}
bool Multiplication::isAlpha(string value) {
	bool n = false;
	for (size_t i = 0; i < value.size(); i++)
	if (isalpha(value[i]))
		n = true;
	return n;

}
bool Multiplication::isFraction(string value) {
	bool isFraction = false;
	for (size_t i = 0; i < value.size(); i++)
	{
		if (value[i] == '/') {
			isFraction = true;
		}
	}
	return isFraction;
}
bool Multiplication::check(string value1, string value2) {

	bool result = false;
	if (isFraction(value1) == true && isFraction(value2) == false) {
		//simplify value1
		result = true;
		return result;
	}
	else if (isFraction(value1) == false && isFraction(value2) == true) {
		//simplify value2
		result = true;
		return result;
	}
	else if (isFraction(value1) == false && isFraction(value2) == false) {
		result = true;
		return result;
	}
	else
		result = false;
	return  result;


}
string  Multiplication::simplify(string value1, string value2, string operation) {

	double result, top1, bot1, top2, bot2;
	bot1 = 1;
	bot2 = 1;

	if (isFraction(value1) == true) { //if the first operand is a fraction, second is not, e.g. (1/2)^2
		string openPar = "(";
		string f2 = "/";
		size_t slash = value1.find(f2);  //position of "/"
		size_t par = value1.find(openPar); //pos of open parentheses
		string num = value1.substr(par + 1, slash - par - 1); //take in whatever is after open parentheses to be numerator
		string den = value1.substr(slash + 1, value1.size() - (slash + 2));   //take in whatever is after "/" to be denominator
		stringstream numerator(num);   //convert string of numerator and denominator to double
		numerator >> top1;
		stringstream denominator(den);
		denominator >> bot1;
	}
	else
	{
		stringstream sn(value1);
		sn >> top1;
	}


	if (isFraction(value2) == true) { //if the first operand is a fraction, second is not, e.g. (1/2)^2
		string openPar = "(";
		string f2 = "/";
		size_t slash = value2.find(f2);  //position of "/"
		size_t par = value2.find(openPar); //pos of open parentheses
		string num = value2.substr(par + 1, slash - par - 1); //take in whatever is after open parentheses to be numerator
		string den = value2.substr(slash + 1, value2.size() - (slash + 2));   //take in whatever is after "/" to be denominator
		stringstream numerator(num);   //convert string of numerator and denominator to double
		numerator >> top2;
		stringstream denominator(den);
		denominator >> bot2;
	}
	else
	{
		stringstream sn(value2);
		sn >> top2;
	}

	result = pow(top1 / bot1, top2 / bot2);
	double compval = result - floor(result + EPSILON);
	if (-EPSILON < compval && compval < EPSILON)
	{
		string retval;
		ostringstream general;
		general << result;
		retval = general.str();
		cout << retval;
		return retval;//return result as string
	}
	cout << value1 + " ^ " + value2;
	return value1 + " ^ " + value2;//return value1 ^ value2

}
string Multiplication::calculate(string value1, string value2, string ope) {
	string a;


	string use1 = "";
	string use2 = "";
	int v1 = 0;
	int v2 = 0;
	vector <string> vect1;
	vector <string> vect2;
	vector <char> opera1;
	vector <char> opera2;
	string space = " ";
	Algorithm* algo = new Algorithm();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// stacking the numbers and letter in one 
	// stscking the operands and spaces in another 
	while (v1 < value1.length()){
		if (!(value1.at(v1) == '+' || value1.at(v1) == '-' || value1.at(v1) == ' ' || value1.at(v1) == '(' || value1.at(v1) == ')'
			|| value1.at(v1) == '*' || value1.at(v1) == '/' || value1.at(v1) == '^'))
		{
			use1 += value1.at(v1);     // appeding if the are no operators
		}
		if ((value1.at(v1) == '-' &&  value1.at(v1 + 1) != ' ') || (value1.at(v1) == '*' || value1.at(v1) == '/' || value1.at(v1) == '^'
			|| value1.at(v1) == '(' || value1.at(v1) == ')')) {
			use1 += value1.at(v1);
		}
		else if (ispunct(value1.at(v1)) || (value1.at(v1) == ' '))  {

			opera1.push_back(value1.at(v1));  // stacking the operators
			if (!(value1.at(v1) == ' ') && use1 != ""){
				vect1.push_back(use1);// adding the separeted string to the vector 
				use1 = "";
			}
		}
		v1++;
	}
	vect1.push_back(use1);// adding the separeted string to the vector 

	while (v2 < value2.length()){
		if (!(value2.at(v2) == '+' || value2.at(v2) == '-' || value2.at(v2) == ' ' || value2.at(v2) == '(' || value2.at(v2) == ')'
			|| value2.at(v2) == '*' || value2.at(v2) == '/' || value2.at(v2) == '^')){
			use2 += value2.at(v2);
		}
		if ((value2.at(v2) == '-' &&  value2.at(v2 + 1) != ' ') || (value2.at(v2) == '*' || value2.at(v2) == '/' || value2.at(v2) == '^'
			|| value2.at(v2) == '(' || value2.at(v2) == ')')) {
			use2 += value2.at(v2);
		}
		else if (ispunct(value2.at(v2)) || (value2.at(v2) == ' '))  {

			opera2.push_back(value2.at(v2));  // stacking the operators
			if (!(value2.at(v2) == ' ') && use2 != ""){
				vect2.push_back(use2);// adding the separeted string to the vector 
				use2 = "";
			}
		}

		v2++;

	}
	vect2.push_back(use2);// adding the separeted string to the vector 





	for (int i = 0; i < vect1.size(); i++) {
		for (int j = 0; j < vect2.size(); j++) {
			if (isFraction(vect1.at(i)) == false && isFraction(vect2.at(j)) == false) {  // if both of them are not fractions 

				if ((isAlpha(vect1.at(i)) == false && isAlpha(vect2.at(j)) == true))   // first one is a number and second is letter 
				{
					double b = 0, c = 0, d = 0, e = 0;
					double top1 = 0, bot1 = 0;
					double top2 = 0, bot2 = 0;
					string str = vect2.at(j);
					string numb = "";
					string letter = "";
					string ans = "";

					for (int k = 0; k < str.length(); k++) {
						if (isdigit(str.at(k))) {

							while (isdigit(str.at(k))) { // adding the length of thr digits 
								numb += str.at(k);
								k++;
							}
						}
						if (str.at(k) == '-') {
							a += "-";
						}
						if (isalpha(str.at(k))) {  // check if is a letter and addign them

							while (k < str.length() && (isalpha(str.at(k)))) {
								letter += str.at(k);
								k++;
							}
						}
					}

					stringstream sr(numb); // changin from string to numb
					sr >> d;
					stringstream sd(vect1.at(i));
					sd >> e;

					if (d == 0){
						c = e;
					}
					else{
						c = d * e;
					}
					ostringstream general;
					general << c;
					ans = general.str();

					if (!opera2.empty()){
						if (opera2.at(j) == ' '){
							a += ans + letter;
							a += opera2.at(j);

						}
						else {
							a += opera2.at(j) + space + ans + letter;

						}
					}
					else {
						a += ans + letter;
					}
					a = algo->replaceAll(a, "--", "+ ");
					a = algo->replaceAll(a, "- -", "+ ");
					a = algo->replaceAll(a, "- +", "- ");
					a = algo->replaceAll(a, "-+", "- ");


					if (a.at(0) == '+') {
						a = a.substr(1);
					}
				}
				if (isAlpha(vect1.at(i)) == true && isAlpha(vect2.at(j)) == false)    // first one is a letter second is a number 
				{
					double b = 0, c = 0, d = 0, e = 0;
					double top1 = 0, bot1 = 0;
					double top2 = 0, bot2 = 0;
					string str = vect1.at(i);
					string numb = "";
					string letter = "";
					string ans = "";

					for (int k = 0; k < str.length(); k++) {
						if (isdigit(str.at(k))) {

							while (isdigit(str.at(k))) { // adding the length of thr digits 
								numb += str.at(k);
								k++;
							}
						}
						if (str.at(k) == '-') {
							a += "-";
						}
						if (isalpha(str.at(k))) {  // check if is a letter and addign them

							while (k < str.length() && (isalpha(str.at(k)))) {
								letter += str.at(k);
								k++;
							}
						}

					}

					stringstream sr(numb); // changin from string to numb
					sr >> d;
					stringstream sd(vect2.at(j));
					sd >> e;
					if (d == 0){
						c = e;
					}
					else{
						c = d * e;
					}
					ostringstream general;
					general << c;
					ans = general.str();

					if (!opera1.empty()){
						if (opera1.at(i) == ' ') {
							a += ans + letter;
							a += opera1.at(i);

						}
						else {
							a += opera1.at(i) + space + ans + letter;

						}
					}
					else {
						a += ans + letter;

					}
					a = algo->replaceAll(a, "--", "+ ");
					a = algo->replaceAll(a, "- -", "+ ");
					a = algo->replaceAll(a, "- +", "- ");
					a = algo->replaceAll(a, "-+", "- ");
					if (a.at(0) == '+')
					{
						a = a.substr(1);
					}
				}
				if ((isAlpha(vect1.at(i)) == true && isAlpha(vect2.at(j)) == true))  // first one and second are letters
				{

					a = vect1.at(i) + vect2.at(j);

				}
				if (isAlpha(vect1.at(i)) == false && isAlpha(vect2.at(j)) == false)
				{  // if both of them are numbers 
					double b = 0, c = 0, d = 0, e = 0;
					double top1 = 0, bot1 = 0;
					double top2 = 0, bot2 = 0;
					stringstream ss(vect1.at(i));
					ss >> d;
					stringstream sn(vect2.at(j));
					sn >> e;
					c = d * e;
					ostringstream general;
					general << c;



					if (!opera1.empty()){
						if (opera1.at(i) == ' ') {
							a += general.str();
							a += opera1.at(i);

						}
						else {
							a += opera1.at(i) + space + general.str();

						}
					}

					else if (!opera2.empty()){
						if (opera2.at(j) == ' ') {
							a += general.str();
							a += opera2.at(j);
						}
						else {
							a += opera2.at(j) + space + general.str();

						}
					}
					a = algo->replaceAll(a, "--", "+ ");
					a = algo->replaceAll(a, "- -", "+ ");
					a = algo->replaceAll(a, "- +", "- ");
					a = algo->replaceAll(a, "-+", "- ");

					if (!a.empty() && a.at(0) == '+') {
						a = a.substr(1);
					}
					else {
						a += general.str();
					}



				}


			}


			//start

			else if ((isFraction(vect1.at(i)) == true || isFraction(vect2.at(j)) == true)
				&& (vect1.at(i).find('^') == string::npos &&  vect2.at(j).find('^') == string::npos))  { //if the first operand is a fraction or the second 

				// initialize 
				double b = 0, c = 0, d = 0, e = 0;
				double top1 = 0, bot1 = 0;
				double top2 = 0, bot2 = 0;
				string openPar = "(";
				string f2 = "/";
				string str = vect1.at(i);
				string str2 = vect2.at(j);
				size_t slash1 = str.find(f2);		//position of "/"
				size_t slash2 = str2.find(f2);
				double tops = 0;
				double bottoms = 0;

				if (slash1 == string::npos) {
					str += f2 + "1";
					slash1 = str.find(f2);
				}
				if (slash2 == string::npos) {
					str2 += f2 + "1";
					slash2 = str2.find(f2);
				}
				// for the first fraction 
				size_t par1 = str.find(openPar);	//pos of open parentheses
				string num1 = str.substr(0, slash1);	//take in whatever is after open parentheses to be numerator
				string den1 = str.substr(slash1 + 1, str.size() - (slash1 + 1));   //take in whatever is after "/" to be denominator
				stringstream numerator(num1);			//convert string of numerator and denominator to double
				numerator >> top1;
				stringstream denominator(den1);
				denominator >> bot1;


				// this is for the second fraction 
				size_t par2 = str2.find(openPar);	//pos of open parentheses
				string num2 = str2.substr(0, slash2);	//take in whatever is after open parentheses to be numerator
				string den2 = str2.substr(slash2 + 1, str2.size() - (slash2 + 1));   //take in whatever is after "/" to be denominator
				stringstream numerator2(num2);			//convert string of numerator and denominator to double
				numerator2 >> top2;
				stringstream denominator2(den2);
				denominator2 >> bot2;

				if (bot1 != 0 && bot2 != 0) {

					ostringstream topps;			//convert to string
					tops = top1 * top2;
					topps << tops;                  // mutiplying top numbers
					ostringstream bottom;
					bottoms = bot1 * bot2;
					bottom << bottoms;
					a = topps.str() + space + f2 + space + bottom.str();
					a = fractionReduction(a);
				}
				return a;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if ((vect1.at(i).find('^') != string::npos || vect2.at(j).find('^') != string::npos))  { //if the first operand is a fraction or the second 
				// initialize 
				double b = 0, c = 0, d = 0, e = 0;
				double top1 = 0, bot1 = 0;
				double top2 = 0, bot2 = 0;
				double front1 = 0;
				double front2 = 0;
				string openPar = "(";
				string closePar = ")";
				string f2 = "/";
				string car = "^";
				string times = "*";
				string newexp = "1" + times;
				string str = vect1.at(i);
				string str2 = vect2.at(j);


				double bases1 = 0;
				double bases2 = 0;
				double tops = 0;
				double bottoms = 0;
				double frontT = 0;
				double result = 0;

				size_t times2 = str2.find(times); // find * pos
				size_t times1 = str.find(times);
				size_t carrot1 = str.find(car);		//position of "^"
				size_t carrot2 = str2.find(car);

				if (times1 == string::npos) {
					str.insert(0, newexp);
					times1 = str.find(times);
					carrot1 = str.find(car);
				}
				if (times2 == string::npos) {
					str2.insert(0, newexp);
					times2 = str2.find(times);
					carrot2 = str2.find(car);
				}


				if (carrot1 == string::npos) {
					str += car + openPar + "1" + closePar;
					carrot1 = str.find(car);
					times1 = str.find(times);

				}
				if (carrot2 == string::npos) {
					str2 += car + openPar + "1" + closePar;
					carrot2 = str2.find(car);
					times2 = str2.find(times);
				}




				// for the first exponent 
				size_t opar1 = str.find(openPar);
				size_t cpar1 = str.find(closePar);	//pos of open  and close parentheses
				string front_base1 = str.substr(0, times1);
				string base1 = str.substr(times1 + 1, carrot1 - 2);	//take in whatever is afterthe carrot to be base
				string expo = str.substr(carrot1 + 2, (str.size() - 2) - (opar1));   //take in whatever is after "(" to be to fraction
				size_t slash1 = expo.find(f2);		//position of "/"

				// separating numerator and denominator 
				if (slash1 == string::npos) {
					expo += f2 + "1";
					slash1 = expo.find(f2);
				}
				string num1 = expo.substr(0, slash1);	//take in whatever is after open parentheses to be numerator
				string den1 = expo.substr(slash1 + 1, expo.size() - (slash1 + 1));   //take in whatever is after "/" to be denominator
				stringstream numerator(num1);			//convert string of numerator and denominator to double
				numerator >> top1;
				stringstream denominator(den1);
				denominator >> bot1;
				stringstream baser1(base1);			//convert string 
				baser1 >> bases1;
				stringstream base_f(front_base1);
				base_f >> front1;


				// for the second exponent  
				size_t opar2 = str2.find(openPar);
				size_t cpar2 = str2.find(closePar);	//pos of open  and close parentheses
				string front_base2 = str2.substr(0, times2);
				string base2 = str2.substr(times2 + 1, carrot2 - 2);	//take in whatever is afterthe carrot to be base
				string expo2 = str2.substr(carrot2 + 2, (str2.size() - 2) - (opar2));   //take in whatever is after "(" to be to fraction
				size_t slash2 = expo2.find(f2);
				// separating numerator and denominator 
				if (slash2 == string::npos) {
					expo2 += f2 + "1";
					slash2 = expo2.find(f2);
				}
				string num2 = expo2.substr(0, slash2);	//take in whatever is after open parentheses to be numerator
				string den2 = expo2.substr(slash2 + 1, expo2.size() - (slash2 + 1));   //take in whatever is after "/" to be denominator
				stringstream numerator2(num2);			//convert string of numerator and denominator to double
				numerator2 >> top2;
				stringstream denominator2(den2);
				denominator2 >> bot2;
				stringstream baser2(base2);			//convert string 
				baser2 >> bases2;
				stringstream base_f2(front_base2);
				base_f2 >> front2;


				if (base1 == base2) {

					if (bot1 == 1 && top1 == 1) {

						bot1 *= bot2;
						top1 *= bot2;
					}
					if (bot2 == 1 && top2 == 1) {

						bot2 *= bot1;
						top2 *= bot1;
					}

					ostringstream oss, oss2, ossT, ossR;
					oss << top1 << " / " << bot1;
					string result1 = oss.str();
					oss2 << top2 << " / " << bot2;
					string result2 = oss2.str();
					// front bases 
					frontT = front1 * front2;
					ossT << frontT;
					string fresult = ossT.str();
					////////////////////////////////////////////////////////
					Addition* add = new Addition();  /// adding the  exponents
					string ans = add->calculate(result1, result2, ope);
					ostringstream baseans;//convert to string


					if (ans == "1")
					{
						frontT *= bases1;
						baseans << frontT;
						a += baseans.str();
					}
					else{
						Exponents * ex = new Exponents();
						ans = ex->calculate(base1, ans, "^");
						

						if (ans.find('^') != string::npos){
							if (fresult == "1") {
								a += ans;
							}
							else {
								a += fresult + space + times + space + base1 + space + car + space + ans;
							}
						}
						else{
							double baseNn; // to number
							stringstream baseN(ans);
							baseN >> baseNn;
							baseNn *= frontT;
							ostringstream oss;
							oss << baseNn;
							string result1 = oss.str();
							
							a += result1;
						}
					}
				}
				else if (expo2.find(expo) != string::npos) {
					double base_ans = 0;
					ostringstream ossT;
					frontT = front1 * front2;
					ossT << frontT;
					string fresult = ossT.str();



					base_ans = bases1 * bases2;
					ostringstream base_anser;			//convert to string
					base_anser << base_ans;
					Exponents *expon = new Exponents();
					base_anser.str() = expon->calculate(base_anser.str(), expo, "^");
					string answ = base_anser.str();
					if (answ.find('^') != string::npos){
						a += fresult + space + times + space + answ;
					}
					else {
						frontT *= base_ans;
						base_anser << frontT;
						a += base_anser.str();
					}
				}
				else {

					double base_ans = 0;
				
					/////////////////////////////////////////////////////////////
					ostringstream base_anser1; // converting double to string 
					base_anser1 << bases1;
					string base_res1 = base_anser1.str();
					ostringstream base_anser2; // converting double to string 
					base_anser2 << bases2;
					string base_res2 = base_anser2.str();
					// exponents 
					ostringstream oss, oss2;
					oss << top1 << " / " << bot1;
					string result1 = oss.str();
					oss2 << top2 << " / " << bot2;
					string result2 = oss2.str();

					

					
					// bases
					base_ans = bases1 * bases2;
					ostringstream base_anser; // converting double to string
					base_anser << base_ans;
					string base_res = base_anser.str();
					// exponents*/
					
					Exponents *expon = new Exponents();
				    string ans1 = expon->calculate(base1,expo, "^");
					string ans2 = expon->calculate(base2, expo2, "^");
					
					a += ans1 + space + times + space + ans2 ;

				}



				return a;
			}

		}
	}
	return a;


}

