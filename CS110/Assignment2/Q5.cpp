/*********************************************************************

// Student name: Bao D. Cao
 
// Student number: 200363431
 
// CS 110 - Assignment2

// Program name: Palindrome number
 
// Created by Bao D. Cao on 2016-10-11.
// Copyright © 2016 Bao D. Cao. All rights reserved.
//
// Main algorithm: use operator / and % to check whether the fist and the
//                 last digits are equal
 
// Major variables: num
 
**********************************************************************/

#include <iostream>

using namespace std;

int main() {
    
    int num; // The number entered by user
    
    // Step 1: Prompt user enter a number
    cout << "Enter a three-digit integer: ";
    cin >> num;
    
    // Step 2: Check if that number is a palidrome number
    
    // Check if that number is a three-digit number
    if (num < 100 || num > 999){
        cout << "The number is invalid for this program." << endl;
    }
    else {
        if (num / 100 == num % 10) // Check if the first digit is equal the last digit
            cout << num << " is a palidrome" << endl;
        else
            cout << num << " is not a palidrome" << endl;
    }
    
    return 0;
}
