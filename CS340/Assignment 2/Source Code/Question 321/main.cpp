
#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

// Function : checkPascal
// Check if a expression written in Pascal is balanced
// Algorithm: read the expression one by one character. If it's an openning operator, push it on to the
//     stack. If it a closing operator, check the top of the stack, if top is corresponding openning,
//     pop the stack, otherwise, display error.
void checkPascal(string exp) {
    stack list;
    int i = 0;
    // read the expression one by one character
    while(i < exp.length()) {
        // openning operator "begin" : push to the stack
        if (exp.substr(i,5) == "begin") {
            list.push(exp.substr(i,5));
            i += 5;
        }
        // other openning operators, push to the stack
        else if(exp.at(i) == '(' || exp.at(i) == '[' || exp.at(i) == '{') {
            string s(1, exp.at(i));
            list.push(s);
            i++;
        }
        // closing operator "end" : check the stack to see if its top is begin then pop it, otherwise
        //   display error
        else if(i < exp.length() - 2 && exp.substr(i, 3) == "end") {
            // check if the stack is empty
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "begin") {
                    list.pop();
                }
            
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator." << endl;
                    return;
                }
            }
            i += 3;
        }
        // closing operator ")" : use the same method as above
        else if (exp.at(i) == ')') {
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "(") {
                    list.pop();
                }
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator." << endl;
                    return;
                }
            }
            i++;
        }
        // closing operator "]" : use the same method as above
        else if (exp.at(i) == ']') {
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "[") {
                    list.pop();
                }
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator." << endl;
                    return;
                }
            }
            i++;
        }
        // closing operator "}" : use the same method as above
        else if (exp.at(i) == '}') {
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "{") {
                    list.pop();
                }
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator." << endl;
                    return;
                }
            }
            i++;
        }
        else {
            i++;
        }
    }
    
    // After go through the expression, if there is anything in the stack, display error
    if (!list.checkEmpty()) {
        cout << "Unbalanced: The number of openning operators is largers than closing operators." << endl;
    }
    else {
        cout << "The expression is balanced." << endl;
    }
}

// Function : checkCpp
// Check if a expression written in C++ is balanced
// The algorithm used in this function is identical to checkPascal, except the pair "begin/end" is
//      replaced by "/**/"
void checkCpp(string exp) {
    stack list;
    int i = 0;
    while(i < exp.length()) {
        if (exp.substr(i,2) == "/*") {
            list.push(exp.substr(i,2));
            i += 2;
        }
        else if(exp.at(i) == '(' || exp.at(i) == '[' || exp.at(i) == '{') {
            string s(1, exp.at(i));
            list.push(s);
            i++;
        }
        else if(i < exp.length() - 1 && exp.substr(i, 2) == "*/") {
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "/*") {
                    list.pop();
                }
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator."  << endl;
                    return;
                }
            }
            i += 2;
        }
        else if (exp.at(i) == ')') {
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "(") {
                    list.pop();
                }
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator." << endl;
                    return;
                }
            }
            i++;
        }
        else if (exp.at(i) == ']') {
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "[") {
                    list.pop();
                }
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator." << endl;
                    return;
                }
            }
            i++;
        }
        else if (exp.at(i) == '}') {
            if (list.checkEmpty()) {
                cout << "Unbalanced: The number of closing operators is larger than openning operators." << endl;
                return;
            }
            else {
                string top = list.top();
                if(top == "{") {
                    list.pop();
                }
                else {
                    cout << "Unbalanced: There is a closing operator that doesn't match with its corresponding openning operator." << endl;
                    return;
                }
            }
            i++;
        }
        else
            i++;
    }
    
    if (!list.checkEmpty()) {
        cout << "Unbalanced: The number of openning operators is larger than closing operators." << endl;
    }
    else {
        cout << "The expression is balanced." << endl;
    }
}

//*************************************000000******************************************

int main() {
    
    int i;
    string exp;
    
    cout << "Enter 1 if you want to check Pascal, 2 if you want to check C++: ";
    cin >> i;
    
    cin.ignore(10, '\n');
    
    cout << "Enter the expression: ";
    getline(cin, exp);
    
    switch(i) {
        case 1:
            checkPascal(exp);
            break;
        case 2:
            checkCpp(exp);
            break;
        default:
            cout << "Language selection is invalid. Only choose 1 or 2." << endl;
    }
    
    return 0;
}
