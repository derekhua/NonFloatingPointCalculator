#include "Calculator.h"

//these three things below are declared and inherited in & from the header file:
//stack<char> mystack; //for operators (each are 1 digit) ; used exclusively in shuntingYard method
//stack<string> mystack2; //used exclusively in reversePolish method
//queue<string> myqueue; //for operands, no matter how long they may be ; used in both methods

Algorithm::Algorithm() {
	//nothing to initialize
}

Algorithm::~Algorithm() {
	//nothing to delete
}

//this method is COMPLETE. Only needs to be updated with little fixes to prevent intentional crashing.
void Algorithm::shuntingYard(string expression) { //see wikipedia page for english interpretion of this algorithm (I based it almost entirely off that)
	string strTemp = "";
	string strTemp2 = "";
	string strTemp3 = "";
	int expressionLength = expression.length();
	char variable = ' ';

	for (int i = 0; i < expressionLength; i++) { //sort through entire expression (tokens left to read)

		//sorts operators and numbers according to PEMDAS
		variable = expression.at(i);
		if (variable != ' ') { // operand or operator is being entered
			if (variable == '^') { //exponent
				mystack.push(variable);
			}
			else if (variable == '*' || variable == '/') { //mult or divis
				if (mystack.top() == '+' || mystack.top() == '-' || mystack.empty() || mystack.top() == '(' ) {
					mystack.push(variable);
				}
				else if (mystack.size() >= 1) {
					strTemp2 = mystack.top();
					myqueue.push(strTemp2);
					mystack.pop();
					strTemp2 = "";
					mystack.push(variable);
				}
				else {
//					throw exception("Error: at MD level");
				}
			}
			else if (variable == '+' || variable == '-') { //add or subs
				if (isNumNext(i, expression)) { //if num directly after "-" with no space, then -num will be num
					strTemp += variable;
				}
				else if (mystack.empty() || mystack.top() == '(') {
					mystack.push(variable);
				}
				else {
					strTemp2 = mystack.top();
					myqueue.push(strTemp2);
					mystack.pop();
					strTemp2 = "";
					mystack.push(variable);
				}
			}
			else if (variable == '(') { //open paren
				mystack.push(expression.at(i));
			}
			else if (variable == ')') { //close paren
				if (i == 2) {
//					throw exception("Error: illegal start of expression");
				}
				if (mystack.empty()) {
//					throw exception("Error: mismatching parentheses");
				}
				while (mystack.top() != '(' && mystack.size() > 1) {
					strTemp2 = mystack.top();
					myqueue.push(strTemp2);
					mystack.pop();
					strTemp2 = "";
				}
				if (mystack.empty()) { //no operators left
//					throw exception("Error: mismatched parentheses");
				} else if (mystack.top() == '(') { //last operator
					mystack.pop();
				} else { //???
//					throw exception("Error: mismatched parentheses"); //used to be "figure out who I am"
					//cout << mystack.top() << endl;
				}

			}
			else if (variable == '$') { //nth root ; has same precedence as normal exponent
				mystack.push(variable);
			}
			else if (variable == '#') { //square root ; has same precedence as normal exponent
				mystack.push(variable);
			}
			else if (variable == 'L') { //log ; has same precedence as normal exponent
				mystack.push(variable);
			}
			else if (variable == '!') { ////factorial ; has same precedence as normal exponent
				mystack.push(variable);
			}
			else { //either number, variable, decimal point, or symbolic number is being entered
				strTemp += variable;
				if (expression.at(i + 1) == ')') {			//test this
					if (!strTemp.empty()) {
						myqueue.push(strTemp);
						strTemp = "";
					}
				}
			}
		}

		//updates queue
		if (i < expressionLength - 1 && variable != '^') { //not last iteration ; allow for slighly different exponent input
			if (variable == ' '){ //enter newly complete operand into queue
				if (!strTemp.empty()) {
					myqueue.push(strTemp);
					strTemp = "";
				}
			}
		} else { //for final iteration so an extra ' ' is not required from user
			if (!strTemp.empty()) {
				myqueue.push(strTemp);
				strTemp = "";
			}
		}
	}

	//pop entire stack into the queue (no tokens left to read)
	while (!mystack.empty()) {
		if (mystack.top() == '(' || mystack.top() == ')') {
//			throw exception("Error: mismatched parentheses");
		}
		strTemp3 = mystack.top();
		myqueue.push(strTemp3);
		mystack.pop();
		strTemp3 = "";
	}
	//mystack should now be empty
	// these next 5 lines only exist for testing purposes, will not be part of final solution
	/*int j = myqueue.size();
	for (int i = 0; i < j; i++) {
		cout << myqueue.front() << endl;
		myqueue.pop();
	}	*/
}

//method has been proven functional (with integer-only addition)
string Algorithm::reversePolish(string expression) { //returned string will give ultimate answer
	string value2 = "";
	string value1 = "";
	string action1 = "";
	char action = ' ';

	while (!myqueue.empty()) {
		if (!isOperator()) { //if queue element is a number, then add to stack, delete from queue
			mystack2.push(myqueue.front());
			myqueue.pop();
		}
		else { //if queue element is an action (operator), then evaluate
			if (mystack2.size() < 2 ) { //&& expression.at(3) != '-') {
//				throw exception("Error: user has not input sufficient values in the expression");
			}
			else {
				value2 = mystack2.top(); //value2 is newest value on stack
				mystack2.pop();
				value1 = mystack2.top(); //value1 is second newest value on stack
				mystack2.pop();
				action1 = myqueue.front();
				myqueue.pop();

				//determine which operator class to use (initially)
				//call matching calculate method and stick its result back in mystack2
					//e.g. mystack2.push(specificOperationClassInstancePointer->calculate(value1, value2, action));
				//if necessary, the operations classes will call each other to solve/simplify the given expression
					//one string will ultimately be returned to this (reverse polish interpretation) method, 
					//no matter amount of places (classes) or times the expression needs to be evaluated/simplifed

				if (action1.length() == 1) { //convert string to char so easy switch is possible
					action = action1[0];
				}
				//additional pointers and cases will be created when the pertinent class files are available
				//Adding* add = new Adding();
				Logn* log = new Logn();
				Exponents* expo = new Exponents();
				NthRoot* nth = new NthRoot();
				Factorial* fac = new Factorial();
				Multiplication* mul = new Multiplication();
				Addition* add = new Addition();
				Division* div = new Division();
				Subtraction* sub = new Subtraction();
				switch (action) {
					case '+': mystack2.push(add->calculate(value1, value2, action1));
						break;
					case '-': mystack2.push(sub->calculate(value1, value2, action1));
						break;
					case '*': mystack2.push(mul->calculate(value1, value2, action1));
						break;
					case '/': mystack2.push(div->calculate(value1, value2, action1));
						break;
					case '^': mystack2.push(expo->calculate(value1, value2, action1));
						break;
					case '$': mystack2.push(nth->calculate(value1, value2, action1));
						break;
					case '#' : //obsolete
						break;
					case 'L': mystack2.push(log->calculate(value1, value2, action1));
						break;
					case '!': mystack2.push(fac->calculate(value1, value2, action1));
						break;
					default: cout << "Error: none of the preset switch cases were chosen" << endl;
						break;
				}
				//reset placeholders to empty states
				value1 = "";
				value2 = "";
				action1 = "";
				action = ' '; 
			}
		}						
	}
	int remainingSize = mystack2.size();
	if (remainingSize == 1) {
		result = mystack2.top();
		return result;
	}
	else {
//		throw exception("Error: the user input has too many values (and may be missing an operator)");
	}
	return "";
}

string Algorithm::formatExpression(string expression) {
	string* exp = &expression; //init expression pointer
	ensureEnclosingParens(exp); //handle parentheses
	//formatNegOper(exp);
	formatNEGfront(exp);
	turningSign(exp);
	formatSQRT(exp);
	formatNRT(exp);
	formatLOGS(exp);
	formatFAC(exp);
	//formatANSfromN(exp);
	//formatANS(exp);
	formatANSfromNMult(exp);
	//formatANSfromN(exp);
	formatNEG(exp);
	formatCompress(exp);
	formatMultOpe(exp);
	//formatFOIL(exp);
	formatImpMult(exp);
	formatFOIL(exp);
	ensureEnclosingParens(exp);
	return *exp;
}

bool Algorithm::enclosingParens(string expression) {
	char firstChar = expression.at(0);
	int expressionLength = expression.length();
	char lastChar = expression.at(expressionLength - 1);
	if (firstChar == '(' && lastChar == ')') {
		return true;
	}
	return false;
}

void Algorithm::ensureEnclosingParens(string* exp) {
	string expression = *exp;
	if (!enclosingParens(expression)) {
		expression = "( " + expression + " )";
	}
	*exp = expression;
}

string Algorithm::ensureEnclosingParens(string expression) {
	if (!enclosingParens(expression)) {
		expression = "( " + expression + " )";
	}
	return expression;
}

void Algorithm::formatSQRT(string* exp) {
	string expression = *exp;
	if (expression.find("sqrt:") != string::npos) {
		replaceAll(*exp, "sqrt:", " 2 $ "); //substitute square root operator (modified nth root) if detected 
		ensureEnclosingParens(exp);
	}
}

void Algorithm::formatNRT(string* exp) {
	string expression = *exp;
	if (expression.find("rt:") != string::npos) { //if "sq" does not precede phrase, substitute nth root operator if detected
		if (expression.find("rt:") != expression.find("sqrt:")) {
			replaceAll(*exp, "rt:", " $ ");
			ensureEnclosingParens(exp);
		}
	}
}

void Algorithm::formatLOG(string* exp) {
	string expression = *exp;
	//cout << "formattedExpression: " << expression << endl;
	
	if (expression.find("log_") != string::npos) { //substitute log operator if detected

		//find isolated log string by first finding its length
		int pos0 = exp->find("log_");
		//cout << "pos0: " << pos0 << endl;
		int i = pos0;
		while (exp->at(i) != ' ') {
			i++;
		}
		int logLength = i - pos0;
		//cout << "logLenth: " << logLength << endl;
		string logPart = exp->substr(pos0, logLength);
		//cout << "logPart: " << logPart << endl;
		
		//get num1
		int posNum1 = pos0 + 4;
		int colonPos = posNum1;
		while (exp->at(colonPos) != ':') { //find the difference in location between the two numbers
			colonPos++;
		}
		int num1Length = colonPos - posNum1;
		string num1 = exp->substr(posNum1, num1Length);
		//cout << "num1: " << num1 << endl;

		//get num2
		int posNum2 = colonPos + 1; //account for this space plus the space of the colon
		int num2Length = 0;
		for (int l = colonPos + 1; exp->at(l) != ' '; l++) {
			num2Length++;
		}
		string num2 = exp->substr(posNum2, num2Length); 

		//substitute
		string newEx = " " + num1 + " L " + num2 + " "; // "L" is the new symbol for log
		replaceAll(*exp, logPart, newEx);
		ensureEnclosingParens(exp);
		//cout << "after formatLOG: " << *exp << endl;
	}
}
void Algorithm::formatLOGS(string* exp) {
	while (exp->find("log_") != string::npos) {
		formatLOG(exp);
	}
}

bool Algorithm::replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

string Algorithm::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return "";
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
	return str;
}

bool Algorithm::isOperator() {
	string operators = "^*/+-#$L!";
	string input = myqueue.front();
	if (operators.find(input) == string::npos) return false; //string::npos is returned if no matched value is found
	return true;
}

bool Algorithm::isNumNext(int i, string expression) {
	if (isdigit(expression.at(i + 1)) || isalpha(expression.at(i + 1))) {
		return true;
	}
	else return false;
}
bool Algorithm::ansFound(string* exp) {
	if (exp->find("ans") != string::npos) {
		return true;
	}
	else return false;
}
bool Algorithm::ansFoundNth(string* exp) {
	if (exp->find("ans_") != string::npos) {
		return true;
	}
	else return false;
}
bool Algorithm::wantDouble() {
	char ans = ' ';
		cout << "Want your answer as a decimal? Type Y or N." << endl;
		cin >> ans;
		ans = toupper(ans);
		if (ans == 'Y') {
			return true;
		}
		else if (ans == 'N') {
			return false;
		}
		while (ans != 'Y' && ans != 'N') {
			cout << "Please retype Y or N:" << endl;
			cin >> ans;
			ans = toupper(ans);
			if (ans == 'Y') {
				return true;
			}
			else if (ans == 'N') {
				return false;
			}
		}
    return false;
	//cin.ignore();
}
double Algorithm::toDouble(string answer) {
	/*double doubleAns = atof(answer.c_str());
	return doubleAns;*/
	/*double value;
	try
	{
		value = boost::lexical_cast<double>(my_string);
	}
	catch (boost::bad_lexical_cast const&)
	{
		value = 0;
	}*/
	 double num = stod(answer);
	 return num;
}
void Algorithm::formatMultOpe(string* exp) {
	string expression = *exp;
	int pos = 0;
	int j = 0;
	for (unsigned int i = 0; i < expression.size(); i++){

		if (i + 2 <= expression.size()){ // operations
			if ((expression.at(i) == '+' || expression.at(i) == '-' || expression.at(i) == '*' || expression.at(i) == '/')
				&& !(isalpha(expression.at(i + 2)) || isdigit(expression.at(i + 2)) || expression.at(i + 2) == '(' || expression.at(i + 2) == ' '))
			{
				if (expression.at(i + 2) = '-' && !(isdigit(expression.at(i + 3)) || isalpha(expression.at(i + 3)))){
//					throw exception("Error: two consecutive operators are not allowed");
				}
			}
			if (i + 5 <= expression.size() - 1 && expression.at(i + 2) == '('){
				if ((expression.at(i) == '+' || expression.at(i) == '-' || expression.at(i) == '*' || expression.at(i) == '/') &&
					!(expression.at(i + 5) == 'L' || expression.at(i + 5) == '#' || expression.at(i + 5) == '$'
					|| expression.at(i + 5) == ' ' || isdigit(expression.at(i + 5)) || isalpha(expression.at(i + 5)))) {
//					throw exception("Error: two consecutive operators are not allowed");
				}
			}
			if ((expression.at(i) == '(') && (expression.at(i + 2) == '+' || expression.at(i + 2) == '*'  // for parenthesis
				|| expression.at(i + 2) == '/' || expression.at(i + 2) == '^' ))
			{
//				throw exception("Error: two consecutive operators are not allowed");
			}
		}


		if (i + 1 <= expression.size()){ // exceptions for exponents
			if ((expression.at(i) == '^') && (expression.at(i + 1) == '+' || expression.at(i + 1) == '*'
				|| expression.at(i + 1) == '/' || expression.at(i + 1) == '^' || expression.at(i + 1) == ')'))
			{
//				throw exception("Error: two consecutive operators are not allowed");
			}

		}
		if (i + 2 <= expression.size()) {

			if ((expression.at(i) == '#' || expression.at(i) == '$') && // for roots
				(expression.at(i + 2) == '+' || expression.at(i + 2) == '*'
				|| expression.at(i + 2) == '/' || expression.at(i + 2) == '^'
				|| expression.at(i + 2) == ')'))
			{
//				throw exception("Error: two consecutive operators are not allowed");
			}
			/*if (expression.at(i) == 'L' && expression.at(i + 2) != '(') {   // not sure if this works
			if ((expression.at(i) == '#' || expression.at(i) == '$') &&
			!(expression.at(i + 4) == '+' || expression.at(i + 4) == '-'
			|| expression.at(i + 4) == '*' || expression.at(i + 4) == '/'
			|| expression.at(i + 4) == '^' || expression.at(i + 4) == ')' || expression.at(i + 4) == '('))
			{
			throw exception("Error: two consecutive operators are not allowed");
			}
			}*/

			// exception for logs
			if (expression.at(i) == 'L' && expression.at(i + 2) == '(') {
				j = i + 5;
				while (expression.at(j) != ' ') {
					j++;
				}
				if ((expression.at(i) == 'L') &&
					!(expression.at(j + 1) == '+' || expression.at(j + 1) == '*'
					|| expression.at(j + 1) == '/' || expression.at(j + 1) == '^' || expression.at(j + 1) == ')'
					|| expression.at(j + 1) == '$' || expression.at(j + 1) == '#' || expression.at(j + 1) == 'L'))
				{
//					throw exception("Error: two consecutive operators are not allowed");
				}
			}
			if ((expression.at(i) == 'L') &&
				(expression.at(i + 2) == '+' || expression.at(i + 2) == '-' || expression.at(i + 2) == '*'
				|| expression.at(i + 2) == '/' || expression.at(i + 2) == '^'
				|| expression.at(i + 2) == ')'))
			{
//				throw exception("Error: two consecutive operators are not allowed");
			}
		}

	}
}


void Algorithm::turningSign(string* exp) {
	string expression = *exp;
	if (expression.find("-+") != string::npos) {
		replaceAll(*exp, "-+", "-");
		ensureEnclosingParens(exp);
	}
	else if (expression.find("- +") != string::npos){
		replaceAll(*exp, "- +", "-");
		ensureEnclosingParens(exp);
	}
	if (expression.find("--") != string::npos) {
		replaceAll(*exp, "--", "+");
		ensureEnclosingParens(exp);
	}
	else if (expression.find("- -") != string::npos) {// && !isdigit(expression.find("- -") + 3) && !isalpha(expression.find("- -") + 3)){
		if ((expression.find("- -")+3) == ' ') {
			replaceAll(*exp, "- -", "+");
		}
		else {
			replaceAll(*exp, "- -", "+ ");
		}
		//replaceAll(*exp, "- -", "+ ");
		ensureEnclosingParens(exp);
	}
	if (expression.find(") (") != string::npos)
	{
		replaceAll(*exp, ") (", ") * (");
		ensureEnclosingParens(exp);
	}
	else if (expression.find(")(") != string::npos)
	{
		replaceAll(*exp, ")(", ") * (");
		ensureEnclosingParens(exp);
	}
	string str = "";
	string str2 = "";
	for (int i = 0; i < expression.size(); i++) {
		if (i + 2 <= expression.size()- 1){
			if ((expression.find(isdigit(i)) || expression.find(isalpha(i))) && expression.at(i + 2) == '(') {
				//str = expression.at(i) + ' ' + expression.at(i + 2);
				//str2 = expression.at(i) + ' ' + '*' + ' '  + expression.at(i + 2);
				replaceAll(*exp, str, str2);
				ensureEnclosingParens(exp);
			}
		}
	}
}
void Algorithm::formatFAC(string* exp) {
	string expression = *exp;
	if (expression.find("!") != string::npos) {
		replaceAll(*exp, "!", " ! 1 "); // substitute 1 as dummy placeholder so shunting yard doesn't get confused 
		ensureEnclosingParens(exp);
	}
}
void Algorithm::formatNEG(string* exp) {
	string expression = *exp;
	/*if (expression.find("- (") == 2) {
		int lgth = expression.length() -3 ;
		string expression1 = expression.substr(5, lgth-5);
		string newExp = "-1 * ( " + expression1 + " )";
		replace(*exp, expression, newExp);
		ensureEnclosingParens(exp);
	}
	else if (expression.find("-(") == 2) {
		int lgth = expression.length() - 2;
		string expression1 = expression.substr(4, lgth - 5);
		string newExp = "-1 * ( " + expression1 + " )";
		replace(*exp, expression, newExp);
		ensureEnclosingParens(exp);
	}*/
	//else if (expression.find("-") == 2 && isdigit(expression.at(3)) || isalpha(expression.at(3))//there is are multiple digits/things afterwards) {
	//	//apply neg to whole operand e.g. -1 * (operand)
	//}
	if (expression.find("- (") != string::npos) {
		if (expression.find("- (") == 2){
			replaceAll(*exp, "- (", "-1 * (");
			ensureEnclosingParens(exp);
		}
		/*else {
			replaceAll(*exp, "- (", "+ (-1) * (");
			ensureEnclosingParens(exp);
		}*/
		//replaceAll(*exp, "- (", "-1 * (");
		//ensureEnclosingParens(exp);
	}
	if (expression.find("-(") != string::npos) {
		//replaceAll(*exp, "-(", "-1 * (");
		//ensureEnclosingParens(exp);
		if (expression.find("-(") == 2){
			replaceAll(*exp, "-(", "-1 * (");
			ensureEnclosingParens(exp);
		}
		else {
			replaceAll(*exp, "-(", "+ (-1) * (");
			ensureEnclosingParens(exp);
		}
	}
}
void Algorithm::formatNEGfront(string* exp) {
	string expression = *exp;
	//if (expression.find("-") == 2 && isdigit(expression.at(3)) || isalpha(expression.at(3))) { //there is are multiple digits/things afterwards
	//	//apply neg to whole operand e.g. -1 * (operand)
	//	int j = 3;
	//	while (isdigit(expression.at(j)) || isalpha(expression.at(j))) {
	//		j++;
	//	}
	//	int lgth = j - 3;
	//	string expression1 = expression.substr(3, lgth - 3);
	//	string newExp = "-1 * ( " + expression1 + " )";
	//	replace(*exp, expression, newExp);
	//	ensureEnclosingParens(exp);
	//}
	if (expression.find("- (") == 2) {
		//find length of operand
		//substr from 5 to end of operand
		//replace this part of string with modified substr

		//if (expression.find("- ( ") == 2) {
		//	int j = 6;
		//	while (expression.at(j) != ' ' && j <= expression.length()) {
		//		j++;
		//	}
		//	int lgth = j - 6;
		//	string expression1 = expression.substr(6, lgth);
		//	string expression0 = expression.substr(2, lgth); //the substr + the part before with "-"
		//	string newExp = "-1 * ( " + expression1 + " )";
		//	replace(*exp, expression0, newExp);
		//	ensureEnclosingParens(exp);
		//}
		//else {
		//	int j = 5;
		//	while (expression.at(j) != ' ' && j <= expression.length()) {
		//		j++;
		//	}
		//	int lgth = j - 5;
		//	string expression1 = expression.substr(5, lgth);
		//	string expression0 = expression.substr(2, lgth); //the substr + the part before with "-"
		//	string newExp = "-1 * ( " + expression1 + " )";
		//	replace(*exp, expression0, newExp);
		//	ensureEnclosingParens(exp);
		//
		//}
			
		

		//for (int i = 2; i < expression.length() - 1; i++) {
		//	if (expression.at(i) == '-' && isdigit(expression.at(i + 1)) || isalpha(expression.at(i + 1))) {
		//		//apply neg to whole operand e.g. -1 * (operand)
		//		int j = i + 1;
		//		while (expression.at(j) != ' ' && j <= expression.length() - 1) {
		//			j++;
		//		}
		//		int lgth = j - i + 1;
		//		/*int lgth2 = lgth;
		//		while (lgth2 < expression.length()) {
		//		lgth2++;
		//		}
		//		int afterOper = lgth2 - lgth;
		//		int operLgth = expression.length() - afterOper;*/
		//		string expression1 = expression.substr(i + 1, lgth);
		//		string newexp = "- ( " + expression1 + " )"; //written to work w/ formatNEGfront
		//		replace(*exp, expression1, newexp);
		//		ensureEnclosingParens(exp);

		//	}
		}
	if (expression.find("- (") == 2) { 
			int lgth = expression.length() - 3;
			string expression1 = expression.substr(5, lgth - 5);
			string newExp = "-1 * ( " + expression1 + " )";
			replace(*exp, expression, newExp);
			ensureEnclosingParens(exp);
		}
	else if (expression.find("-(") == 2) {
		int lgth = expression.length() - 2;
		string expression1 = expression.substr(4, lgth - 5);
		string newExp = "-1 * ( " + expression1 + " )";
		replace(*exp, expression, newExp);
		ensureEnclosingParens(exp);
	}
}
void Algorithm::formatCompress(string* exp) {
	string expression = *exp;
	for (int i = 0; i < expression.length(); i++) {
		if (isdigit(expression.at(i)) || isalpha(expression.at(i))) { //if a number or digit is found at position i
			if (expression.at(i + 1) == ')') {
				stringstream ss;
				string paren = "";
				char c = expression.at(i + 1);
				ss << c;
				ss >> paren;
				replace(*exp, paren, " )");
				ensureEnclosingParens(exp);
			}
		}
	}
}
void Algorithm::formatImpMult(string* exp) {
	string expression = *exp;
	int operLength;
	for (int i = 0; i < expression.length()-1; i++) {
		if (isdigit(expression.at(i)) || isalpha(expression.at(i))) {
			int j = i;
			while (isdigit(expression.at(j)) || isalpha(expression.at(j))) {
				j++;
			}
			operLength = j - i;
			stringstream ss;
			if (expression.at(i + operLength) == ' ' && expression.at(i + operLength + 1) == '(') {
				string spaceParen = " (";
				char c = expression.at(i);
				ss << c;
				string num = ss.str();
				ss << spaceParen;
				string target = ss.str();
				string rep = num + " * (";
				replace(*exp, target, rep);
			}
			else if (expression.at(i + operLength) == '(') {
				string paren = "(";
				char c = expression.at(i);
				ss << c;
				string num = ss.str();
				ss << paren;
				string target = ss.str();
				string rep = num + " * (";
				replace(*exp, target, rep);
			}
			ensureEnclosingParens(exp);
		}
	}
}
void Algorithm::formatNegOper(string* exp) {//if no parentheses from - to the next space or end of expression, insert them after -
	string expression = *exp;
	for (int i = 2; i < expression.length() - 1; i++) {
		if (expression.at(i) == '-' && isdigit(expression.at(i+1)) || isalpha(expression.at(i+1))) {
			//apply neg to whole operand e.g. -1 * (operand)
			int j = i+1;
			while (expression.at(j) != ' ' && j <= expression.length()-1) {
				j++;
			}
			int lgth = j - i - 1;
			/*int lgth2 = lgth;
			while (lgth2 < expression.length()) {
			lgth2++;
			}
			int afterOper = lgth2 - lgth;
			int operLgth = expression.length() - afterOper;*/
			string expression1 = expression.substr(i+1, lgth);
			string expression0 = expression.substr(i, lgth);
			string newexp = "- ( " + expression1 + " )"; //written to work w/ formatNEGfront
			replace(*exp, expression0, newexp);
			ensureEnclosingParens(exp);

		}
	}
	//if (expression.at(2) == '-' && isdigit(expression.at(3)) || isalpha(expression.at(3))) {
	//	//apply neg to whole operand e.g. -1 * (operand)
	//		int j = 3;
	//		while (expression.at(j) != ' ' && j <= expression.length()) {
	//			j++;
	//		}
	//		int lgth = j - 3;
	//		/*int lgth2 = lgth;
	//		while (lgth2 < expression.length()) {
	//			lgth2++;
	//		}
	//		int afterOper = lgth2 - lgth;
	//		int operLgth = expression.length() - afterOper;*/
	//		string expression1 = expression.substr(3, lgth);
	//		string newexp = "- ( " + expression1 + " )"; //written to work w/ formatNEGfront
	//		replace(*exp, expression1, newexp);
	//		ensureEnclosingParens(exp);
	//	
	//}
}
bool Algorithm::isSelection(string selection) {
	string selections = "AaBbCcQq";
	if (selections.find(selection) == string::npos) return false; //string::npos is returned if no matched value is found
	return true;
}
bool Algorithm::isFOIL(string* exp) {
	string expression = *exp;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int countTot = 0;
	int pos1 = 0;
	int pos2 = 0;
	int pos3 = 0;
	int upper = 0; //upper bound; second left paren
	int lower = 0; //lower bound; first right paren

	for (int i = 0; i < expression.length(); i++) {
		if (expression.at(i) == ('(')) {
			count1++;
			if (count1 == 2) {
				upper = i;
			}
		}
		if (expression.at(i) == (')')) {
			++count2;
			if (count2 == 1) {
				lower = i;
			}
		}
		if (expression.at(i) == ('*') || expression.at(i) == ('/')) {
			count3++;
		}
		if (count1 >= 2 && count2 >= 2 && expression.find('*') < upper && expression.find('*') > lower) {
			return true;
		}
		else if (count1 >= 2 && count2 >= 2 && expression.find('/') < upper && expression.find('/') > lower) {
			return true;
		}
	}
	return false;

	/*if (expression.find('(') != string::npos) {
		int pos1 = expression.find('(');
		if (expression.find('(') != pos1) {
			upper = expression.find('(');
			count++;
		}
	}
	if (expression.find(')') != string::npos) {
		int pos2 = expression.find(')');
		if (expression.find(')') != pos2) {
			lower = expression.find(')');
			count++;
		}
	}
	if (expression.find('*') != string::npos && expression.find('*') < upper && expression.find('*') > lower) {
		count++;	
	}
	if (count == 3) {
		return true;
	}
	else {
		return false;
	}*/
}
void Algorithm::formatFOIL(string* exp) {
	string expression = *exp;
	if (isFOIL(exp)) {
		string newEx = "1 * " + expression;
		replace(*exp, expression, newEx);
		ensureEnclosingParens(exp);
	}
}