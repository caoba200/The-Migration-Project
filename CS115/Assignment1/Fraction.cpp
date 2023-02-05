/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #1
 
 // Program name: Fraction Problem (Project 10, pg. 382-383)
 // Date : January 12, 2017 (Modified: Monday January 23, 2017)
 
**************************************************/

#include <iostream>
#include <string>

using namespace std;

//----------------------- Function : readFracProblem -------------------------
//Prompt user input the problem
//Read the information and store them to the coresponding parameters
//----------------------------------------------------------------------------
void readFracProblem(int&, int&, int&, int&, char&, bool&);

//---------------------- Function : getFrac ----------------------------------
//Get the numerator and the denominator of a fraction
//----------------------------------------------------------------------------
void getFrac(int&, int&, bool&);

//---------------------- Function : calculate --------------------------------
//Calculate 2 fractions base on their operator
//----------------------------------------------------------------------------
void calculate(int, int, int, int, char);

//---------------------- Function : addFrac -----------------------------------
//Calculate the sum of 2 fractions n1 / d1 + n2 / d2
//sum = (n1 * d2 + n2 * d1) / (d1 * d2)
//-----------------------------------------------------------------------------
void addFrac(int, int, int, int);

//---------------------- Function : subFrac -----------------------------------
//Calculate the subtraction of 2 fraction n1/d1 and n2/d2
//result = (n1 * d2 - n2 * d1) / (d1 * d2)
//-----------------------------------------------------------------------------
void subFrac(int, int, int, int);

//--------------------- Function : mulFrac ------------------------------------
//Calculate the multiplication of 2 fraction
//result = n1 * n2 / d1 * d2
//-----------------------------------------------------------------------------
void mulFrac(int, int, int, int);

//--------------------- Function : divFrac -----------------------------------
//Calculate the division of 2 fraction
//result = n1 * d2 / n2 * d1
//----------------------------------------------------------------------------
void divFrac(int, int, int, int);

//-------------------- Function : quit ---------------------------------------
//Check if user want to stop the program
//----------------------------------------------------------------------------
void quit(bool&);

int main() {
    
    // Variable Declaration
    int num1, denom1, num2, denom2; // Numerator and denominator of 2 fractions
    char op;  // Operand
    
    bool stop = false; //Check if user still want to continue the program
    bool format = true; //Check if user enter the right format
    
    while(!stop) {
        readFracProblem(num1, denom1, num2, denom2, op, format); // Ask user enter the fraction problem
        if (format) // if user entered the right format, compute the problem
            calculate(num1, denom1, num2, denom2, op);
        else
            cout << "Error: the format is wrong" << endl;
        format = true; // Reset the format checking variable
        quit(stop);
    }
    
    return 0;
}

//============ FUNCTION IMPLEMENTATION ======================================

//----------------------- Function : readFracProblem -------------------------
//Prompt user input the problem
//Read the information and store them to the coresponding parameters
//----------------------------------------------------------------------------
void readFracProblem (int &n1, int &d1, int &n2, int &d2, char &op, bool &format) {
    cout << "Enter a common fraction problem: ";
    getFrac(n1, d1, format);  // Get the 1st fraction
    cin >> op;        // Get the operator
    getFrac(n2, d2, format);  // Get the second fraction
}

//---------------------- Function : getFrac ----------------------------------
//Get the numerator and the denominator of a fraction
//The format variable is used to check if user entered the wrong slash
//----------------------------------------------------------------------------
void getFrac(int &n, int &d, bool &format) {
    char slash; // The slash between the numerator and the denominator
    cin >> n >> slash >> d;
    if (slash != '/')
        format = false;
}

//---------------------- Function : calculate --------------------------------
//Calculate 2 fractions base on their operator
//----------------------------------------------------------------------------
void calculate(int n1, int d1, int n2, int d2, char op) {
    if (d1 == 0 || d2 == 0) // The fraction is undefined if the dominator is 0
        cout << "Cannot solve this problem!" << endl;
    else
        switch(op) {
            case '+' :
                addFrac(n1, d1, n2, d2);
                break;
            case '-' :
                subFrac(n1, d1, n2, d2);
                break;
            case '*' :
                mulFrac(n1, d1, n2, d2);
                break;
            case '/' :
                divFrac(n1, d1, n2, d2);
                break;
            default:
                cout << "Invalid operator!" << endl;
        }
}

//---------------------- Function : addFrac -----------------------------------
//Calculate the sum of 2 fractions n1 / d1 + n2 / d2
//sum = (n1 * d2 + n2 * d1) / (d1 * d2)
//-----------------------------------------------------------------------------
void addFrac(int n1, int d1, int n2, int d2) {
    int n = n1 * d2 + n2 * d1;  // the numerator of the sum
    int d = d1 * d2; // the dominator of the sum
    
    // Display the result
    cout << "The result of the addition is " << n << "/" << d << endl;
}

//---------------------- Function : subFrac -----------------------------------
//Calculate the subtraction of 2 fraction n1/d1 and n2/d2
//result = (n1 * d2 - n2 * d1) / (d1 * d2)
//-----------------------------------------------------------------------------
void subFrac(int n1, int d1, int n2, int d2) {
    int n = n1 * d2 - n2 * d1;
    int d = d1 * d2;
    cout << "The result of the subtraction is " << n << "/" << d << endl;
}

//--------------------- Function : mulFrac ------------------------------------
//Calculate the multiplication of 2 fraction
//result = n1 * n2 / d1 * d2
//-----------------------------------------------------------------------------
void mulFrac(int n1, int d1, int n2, int d2) {
    cout << "The result of the multiplication is " << n1 * n2 << "/" << d1 * d2 << endl;
}

//--------------------- Function : divFrac -----------------------------------
//Calculate the division of 2 fraction
//result = n1 * d2 / n2 * d1
//----------------------------------------------------------------------------
void divFrac(int n1, int d1, int n2, int d2) {
    cout << "The result of the multiplication is " << n1 * d2 << "/" << n2 * d1 << endl;
}

//-------------------- Function : quit ---------------------------------------
//Check if user want to stop the program
//----------------------------------------------------------------------------
void quit(bool &flags) {
    string answer;
    cout << "Continue: Yes/No? ";
    cin >> answer;
    bool stop = false; // Control the question loop - won't stop if user's answer is neither true or false
    while(!stop) {
        if (answer == "Yes" || answer == "yes" || answer == "y" || answer == "Y" || answer == "YES") {
            stop = true;
            flags = false;
        }
        else if (answer == "No" || answer == "no" || answer == "n" || answer == "N" || answer == "NO"){
            stop = true;
            flags = true;
        }
        else {
            cout << "Continue: Yes/No? ";
            cin >> answer;
        }
    }
    
}
