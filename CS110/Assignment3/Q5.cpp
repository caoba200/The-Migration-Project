/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: String computation
 
 // Created by Bao D. Cao on 2016-10-26.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 
 // Main algorithm: Use string functions to check the validation of an input.
 
 // Major variables: SID, valid
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    string SID; // Student ID number
    bool valid = true; // Check if the input is valid, false when the input is invalid
    
    // Step 1: Prompt user enter a U of R student ID
    
    cout << "Enter a SID: " ;
    getline(cin, SID);
    
    // Step 2: Check if the input is valid
    
    if(SID.length() != 11)                      // Check length
        valid = false;
    // Check if each letter is a digit (except at SID[3] and SID[7] where the letter is '-')
    else {
        for (int i = 0; i < SID.length(); i++){
            if (i != 3 && i != 7){
                if (!isdigit(SID[i])){
                    valid = false;
                    break;
                }
            }
            // Check if SID[3] and SID[7] is '-' or not
            else
                if (SID[i] != '-'){
                    valid = false;
                    break;
                }
        }
    }
    
    // Step 3: Display the result
    
    if (valid)
        cout << SID << " is a valid U of R SID." << endl;
    else
        cout << SID << " is an invalid U of R SID." << endl;
    
    return 0;
}
