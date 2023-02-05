
#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

int main() {
    
    string expression;  // Input string
    string result = ""; // The string that contains the postfix expression
    
    Stack stack;        // Stack initialization with length = 0 (default constructor)
    
    cout << "Enter the expression: ";
    getline(cin, expression);
    
    // Loop through every character of the input string
    for(int i = 0; i < expression.length(); i++) {
        // If the current character is number or character, add it to the result
        if (isalnum(expression[i]))
            result += expression[i];
        
        // If the current character is '(' , push it onto the stack
        else if(expression[i] == '(')
            stack.push(expression[i]);
        
        // If the current character is ')'
        else if(expression[i] == ')') {
            //  1. Pop and write all operators until meet '('
            while(stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            //  2. Pop '('
            stack.pop();
        }
        // If the current character is * or /
        else if(expression[i] == '*' || expression[i] == '/') {
            // 1. Pop and write all operators until [meet the first '(', '+' or '-'] or [stack is empty]
            while(!stack.isEmpty() && stack.top() != '(' && stack.top() != '+' && stack.top() != '-') {
                result += stack.top();
                stack.pop();
            }
            // 2. Push that character(* or /) onto the stack
            stack.push(expression[i]);
        }
        
        // If the current character is + or -
        else if(expression[i] == '+' || expression[i] == '-') {
            // 1. Pop and write all operators until [meet the first '('] or [stack is empty]
            while(!stack.isEmpty() && stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            // 2. Push that character (+ or -) onto the stack
            stack.push(expression[i]);
        }
        else if(expression[i] == '^') {
            
            // Push that character(^) onto the stack
            stack.push(expression[i]);
        }
    }
    
    // End of expression, pop and write all operators
    while(!stack.isEmpty()) {
        result += stack.top();
        stack.pop();
    }
    
    // Display the result
    cout << "The postfixt expression is : " << result << endl;
    
    return 0;
}
