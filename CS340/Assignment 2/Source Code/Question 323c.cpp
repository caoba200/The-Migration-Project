//
//  main.cpp
//  Assignment2_323c
//
//  Created by Bao D. Cao on 2018-10-07.
//  Copyright © 2018 Bao D. Cao. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    
    string exp;
    cout << "Enter the postfix expression: ";
    getline(cin, exp);
    
    // use stack in the library
    stack<string> list;
    
    // Go through each character in the string
    for(int i = 0; i < exp.length(); i++) {
        // if it's a operand - push to the stack
        if(isalnum(exp[i])) {
            string temp(1, exp[i]);
            list.push(temp);
        }
        // if it's a operator, pop the first 2 operands from the stack, create a expression
        // with the 2 operands and 1 operator (add parenthesis) and put the result back to stack
        else{
            string temp1 = list.top();
            list.pop();
            string temp2 = list.top();
            list.pop();
            list.push("(" + temp2 + exp[i] + temp1 + ")");
        }
        
    }
    
    // Display the result - The only element on the stack
    cout << "The corresponding infix notation: " << list.top() << endl;
    
    return 0;
}
