//
//  main.cpp
//  NonFloatingPointCalculator
//
//  Created by Derek Hua on 3/24/15.
//  Copyright (c) 2015 Derek Hua. All rights reserved.
//

#include <iostream>
#include "Calculator.h"
#include <algorithm>

char selection = 'Z';
string selections = "AaBbCcQq";
string selection1 = "";
string expression = "";
string answer = "";
double doubleAns = 0;
vector <string> answers;
vector <string> expressions;
vector <string> modifiedAnswers;
vector <string> modifiedAnswers2;
vector <string> modifiedExpressions;

int main() {
    
    do {
        //********************
        //**** print menu ****
        //********************
        cout << "\t\t\t\tMENU" << endl;
        cout << "###################################################################" << endl;
        cout << "|A| Enter A NEW EXPRESSION:" << endl;
        cout << "|B| HELP" << endl;
        cout << "|C| Review Previous Expressions and Answers" << endl;
        cout << "|Q| Quit" << endl;
        cout << "###################################################################\n" << endl;
        //======================================================================================================
       
        //********************
        //** get selection ***
        //********************
        cout << "Enter Your Selection:" << endl;
        if (selection != 'Z' && selection != 'C') { //exclude very first run-through (because it has nothing to clear)
            cin.sync();
        }
        getline(cin, selection1);
        while (selections.find(selection1) == string::npos) {
            cout << "Please re-enter your selection:" << endl;
            getline(cin, selection1);
        }
        
        //********************
        //* verify selection *
        //********************
        if (selection1.length() == 1) {
            selection = toupper(selection1[0]);
        } else { //error message
            cout << "Single character not found; selection length is actually: " << selection1.length() << endl;
        }
        
        //********************
        //* handle selection *
        //********************
        Algorithm *al = new Algorithm();
        switch (selection) {
            case 'A':
                cout << "Enter the Expression (or type B to go back to Menu, Q to quit program):" << endl;
                
                getline(cin, expression);
                
                if (expression == "B" || expression == "b") { //go back to menu
                    cout << endl;
                    break;
                }
                if (expression == "Q" || expression == "q") { //quit program
                    selection = 'Q';
                    cout << endl;
                    cout << "*****************************************" << endl;
                    cout << "** You Have Chosen to Quit the Program **" << endl;
                    cout << "*****************************************\n" << endl;
                }
                else{
                    try {
                        expressions.push_back(expression);
                        expression = al->formatExpression(expression);
                        cout << expression << endl; //for debugging multiple log use
                        al->shuntingYard(expression);
                        answer = al->reversePolish(expression);
                        answers.push_back(answer);
                        /*if (al->wantDouble()) {
                         doubleAns = al->toDouble(answer);
                         stringstream s;
                         s << doubleAns;
                         answer = s.str();
                         }*/
                        cout << "The answer is: " << answer << endl;
                        if (al->wantDouble()) {
                            doubleAns = al->toDouble(answer);
                            stringstream s;
                            s << doubleAns;
                            answer = s.str();
                        }
                        cout << endl;
                    }
                    catch (exception& e) {
                        cout << e.what() << '\n';
                        answers.push_back("NO");
                        cout << endl;
                    }
                }
                break;
            case 'B':
                cout << endl;
                cout << "\t\t\t\tHELP" << endl;
                cout << "###################################################################" << endl;
                cout << "\t\tENTER EXPRESSIONS WITH CARE!" << endl;
                cout << "\tAMBIGUOUS CASES WILL LIKELY RETURN ERRORS, NOT ANSWERS." << endl;
                cout << endl;
                cout << "ADDITION =  \t\tx + y \t\t(x plus y)" << endl;
                cout << "SUBTRACTION = \t\tx - y \t\t(x minus y)" << endl;
                cout << "MULTIPLICATION = \tx * y \t\t(x times y)" << endl;
                cout << "DIVISION = \t\tx / y \t\t(x divided by y)" << endl;
                cout << "EXPONENTIALS = \t\tx^y or x ^ y \t(x to the power of y)" << endl;
                cout << "LOGARITHMS = \t\tlog_b:x \t(log base b of x)" << endl;
                cout << "NTH ROOT = \t\tnrt:x \t\t(the nth root of x)" << endl;
                cout << "SQUARE ROOT = \t\tsqrt:x \t\t(the square root of x)" << endl;
                cout << "FACTORIAL = \t\tx! \t\t(x factorial)" << endl;
                cout << endl;
                cout << "USE LAST/MOST RECENT ANSWER = \tans_1" << endl;
                cout << "SECOND MOST RECENT ANSWER = \tans_2 \t.... etc." << endl;
                cout << endl;
                cout << endl;
                cout << "TO MAKE SURE YOUR INPUT IS READ CORRECTLY:\nPUT A SPACE AFTER EVERY OPERATOR AND COMPLETE OPERAND" << endl;
                cout << "\t\t\t\t\tE.G. ( -1 + 12 ) ^ 2" << endl;
                cout << endl;
                cout << "EXAMPLE OF AN ALTERNATE (USUALLY) VALID INPUT: \t(-1 + 12)^2" << endl;
                cout << endl;
                cout << "FOR NEGATIVE FUNCTIONS, TYPE \"- ( log_2:4 )\" INSTEAD OF \"-log_2:4\"" << endl;
                cout << endl;
                cout << "IMPLICIT MULTIPLICATION ON LEFT SIDE OF PARENTHESES PAIR IS SUPPORTED" << endl;
                cout << endl;
                break;
                
            case 'C':
                cout << endl;
                if (answers.empty()) {//&& expressions.empty()) { //no previous data to print
                    cout << "There are no previous expressions or answers to display yet." << endl;
                    cout << endl;
                    break;
                }
                else { //print the desired info
                    cout << "Since program launch: " << endl;
                    int j = 0;
                    for (int i = 0; i < expressions.size(); i++) {
                        //if answers at same location says "NO", do not print on list
                        if (answers.at(i) != "NO") {
                            modifiedExpressions.push_back(expressions.at(i));
                            modifiedAnswers.push_back(answers.at(i));
                            j++;
                        }
                    }
                    if (modifiedAnswers.empty()) { //every expression thus far has triggered on exception
                        cout << "No (valid) previous expressions or answers have been recorded." << endl;
                        cout << endl;
                        break;
                    }
                    cout << endl;
                    int k = 1;
                    for (int i = modifiedExpressions.size() - 1; i >= 0; i--) {
                        cout << "Expression " << k << " is: " << modifiedExpressions.at(i) << endl;
                        cout << "Answer " << k << " is: " << modifiedAnswers.at(i) << endl;
                        k++;
                        cout << endl;
                    }
                    cout << "The list is exhausted." << endl;
                    cout << endl;
                    //make temp vectors empty again
                    modifiedAnswers.clear();
                    modifiedExpressions.clear();
                }
                break;
            case 'Q':
                cout << endl;
                cout << "*************************************" << endl;
                cout << "You Have Chosen to Quit the Program" << endl;
                cout << "*************************************\n" << endl;
                break;
            default:
                cout << "Unknown case: " << selection << endl;
        }// end switch

    } while (selection != 'Q');
    
    ////al should deconstruct at about this point
    ////system("pause");
    return 0;
}
void Algorithm::formatANS(string* exp) {
    if (ansFound(exp)) {
        if (!answers.empty() && isAcceptableAns() && ((expression.find("exp_") != expression.find("exp")) || expression.find("exp_") == string::npos)) {
            replaceAll(*exp, "ans", ensureEnclosingParens(acceptableAns()));
        }
        else {
//            throw exception("Error: previous answer for \"ans\" substitution doesn't exist");
        }
    }
}
string Algorithm::acceptableAns() {
    int i = 0;
    do {
        i++;
        if (answers.at(answers.size() - i) != "NO") {
            return answers.at(answers.size() - i);
        }
    } while ( i <= answers.size());
//    throw exception("Error: there are no valid previous answers to use");
    return "nope";
}
bool Algorithm::isAcceptableAns() {
    for (int i = 0; i < answers.size(); i++) {
        if (answers.at(i).find("NO") == string::npos) {
            return true;
        }
    }
    return false;
}
void Algorithm::formatANSfromN(string* exp) {
    
    
    string expression = *exp;
    string number = "";
    int n = 0;
    if (ansFoundNth(exp)) {
        
        //if position + 1 of above = location of digit (e.g. "ans_7" ) then plug in answer at location 7 in array if it is valid
        if (isdigit(expression.at((expression.find("ans_") + 4)))) {
            int i = expression.find("ans_") + 4;
            while (isdigit(expression.at(i))) {
                number += expression.at(i);
                i++;
            }
        }
        if (answers.empty()) {//&& expressions.empty()) { //no previous data to print
//            throw exception("There are no previous expressions or answers to display yet.");
        }
        else { //print the desired info								
            
            int j = 0;
            for (int i = 0; i < expressions.size()-1; i++) {
                //if answers at same location says "NO", do not print on list
                if (answers.at(i) != "NO") {
                    //modifiedExpressions.push_back(expressions.at(i));
                    modifiedAnswers2.push_back(answers.at(i));
                    j++;
                }
            }
            if (modifiedAnswers2.empty()) { //every expression thus far has triggered on exception
//                throw exception("No (valid) previous expressions or answers have been recorded.");
            }
            stringstream nume(number);			//convert string of numerator and denominator to double
            nume >> n;
            if (n > modifiedAnswers2.size()) {
//                throw exception("Error: answer location does not yet exist");
            }
            
            else {
                string toBeReplaced = "ans_" + number;
                replaceAll(*exp, toBeReplaced, modifiedAnswers2.at(modifiedAnswers2.size() - (n)));
                ensureEnclosingParens(exp);
                number = "";
                modifiedAnswers2.clear();
            }
            
        }
        
        
    }// end while
    //make temp vectors empty again
    
    //modifiedExpressions.clear();
}
void Algorithm::formatANSfromNMult(string* exp) {
    string expression = *exp;
    while (ansFoundNth(exp)) {
        
        formatANSfromN(exp);
        
    }
}