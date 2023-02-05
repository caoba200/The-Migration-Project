/*************************************************
// Student name : Bao D. Cao
// Student ID : 200363431
// Email : caoba200@uregina.ca

// CS 115 - Assignment #1
 
// Program name: Simple Calculator (Project 9, pg. 382)
// Date : January 12, 2017 (Update: January 21, 2017 : 14:00)
 
**************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


//-------- Function : scan_data(char&, float&, bool&) -------------------
//read the operator from user and store it to the first parameter
//read the operand from user and store it to the second parameter
//the 3rd parameter will be set to true if user enter q for the 1st parameter
//-------------------------------------------------------------------------
void scan_data(char&, float&, bool&, bool&);

//-------- Function : do_next_op(char, float, float&) -------------------
//do the calculation base on the operator (1st para) and the operand (2nd para)
//update the value to the 3rd para(parameter)
//handle the errors from the input (0 division or wrong operator)
//-----------------------------------------------------------------------
void do_next_op(char, float, float&);
int main() {
    
    // Variable declaration
    float op1 = 0; // The left operand
    float op2; // The right operand
    char op; // The operator
    
    bool stop = false; // Check if user want to stop the program by typing q
    bool scan_success = true; //Check if user enter valid format
    
    // Output manipulation
    cout << fixed << showpoint << setprecision(1);
    
    // Run the calculator continuously until user type q to quit it
    while (!stop) {
        scan_data(op, op2, stop, scan_success);
        
        //Only calculate if user dont type 'q'
        if (!stop) {
            if (scan_success) // User entered the right format
                do_next_op(op, op2, op1);
            else {
                cout << "Error: wrong format has been entered" << endl;
                cout << "result so far is " << op1 << endl;
            }
            scan_success = true; // Reset the scan_success for the next loop;
        }
        // Otherwise, show the final result and the program will stop
        else
            cout << "final result is " << op1 << endl;
    }
    
    return 0;
}

//-------- Function : scan_data(char&, float&, bool&) -------------------
//read the operator from user and store it to the first parameter
//read the operand from user and store it to the second parameter
//check if user entered the wrong format (ie: @@ 2 or + AA2 which cause error)
//the 3rd parameter will be set to true if user enter q for the 1st parameter
//-------------------------------------------------------------------------
void scan_data(char& op, float& op2, bool& stop, bool& success) {
    cin >> op;
    cin >> op2;
    if (cin.fail()) { //check if cin >> op2 is wrong because user entered the wrong format
        success = false;
        cin.clear();  //The next 2 statements are used to clean the buffer.
        cin.ignore(100, '\n');
    }
    
    stop = op == 'q' ? true : false;
}

//-------- Function : do_next_op(char, float, float&) -------------------
//do the calculation base on the operator (1st para) and the operand (2nd para)
//update the value to the 3rd para(parameter)
//handle the errors from the input (0 division or wrong operator)
//-----------------------------------------------------------------------
void do_next_op(char op, float op2, float &op1) {
    switch(op) {
        case '+':
            op1 += op2;
            break;
        case '-':
            op1 -= op2;
            break;
        case '*' :
            op1 *= op2;
            break;
        case '/' :
            if (op2 == 0)
                cout << "Error: division by zero" << endl;
            else
                op1 /= op2;
            break;
        case '^' :
            op1 = pow(op1, op2);
            break;
        default :
            cout << "Error: invalid operator" << endl;
    }
    
    cout << "result so far is " << op1 << endl;
}
