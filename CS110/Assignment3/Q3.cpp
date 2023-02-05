/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: Hex to binary
 
 // Created by Bao D. Cao on 2016-10-26.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: convert hex digit to decimal number and then convert this number to binary
 
 // Major variables: hex, decimal, result
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    char hex; // Hex digit
    int decimal; // A decimal number which will be converted from hex digit
    string result = ""; // The binary number converted from hex
    
    // Step 1: Prompt user enter a hex digit.
    
    cout << "Enter a hex digit: " ;
    cin >> hex;
    
    // Step 2: Check value of hex and convert to corresponding decimal number
    
    // Check if 0 <= hex <= 9 OR A <= hex <= F
    if ((hex > 47 && hex < 58) || (hex > 64 && hex < 71)) {
        if (hex < 58)
            decimal = hex - 48;
        else
            decimal = hex - 55;
    }
    else {
        cout << "Invalid: This digit is not a hex!!!" << endl;
        return 0;
    }
    
    // Step 3: Convert decimal number to binary number

    for (int i = 0; i < 4; i++){
        result += decimal % 2 == 0 ? "0" : "1" ;
        decimal /= 2;
    }
    
    // Reverse the order of the result string (because the binary value is the revesed order of repeated modulo to 2)
    reverse(result.begin(), result.end());
    
    // Step 4: Display the result
    cout << "The binary value is " << result << endl;
    
    return 0;
}
