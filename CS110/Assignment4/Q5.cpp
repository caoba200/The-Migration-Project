/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 4
 
 // Program name: Check Password
 
 // Created by Bao D. Cao on 2016-11-10.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Prompt user enter password
                    2. Check length
 //                 3. Check digit + check character + check number of digit >= 2
 // Major variables: password
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    string password;
    // Step 1: Prompt user enter the password
    cout << "Enter a password: ";
    getline(cin, password);
    
    bool valid = true;
    
    // Step 2: Check password's length
    if (password.length() < 8) {
        cout << "invalid password." << endl;
        return 0;
    }
    int digit = 0;
    // Step 3: Check each element of the string to find out it's alphanumeric or not.
    for (int i = 0; i < password.length(); i++){
        if (!isalnum(password[i])){
            valid = false;
            break;
        }
        if (isdigit(password[i]))
            digit++;
    }
    // Check if the number of digit is less than 2
    if (digit < 2)
        valid = false;
    // Step 4: Display the result
    if (valid)
        cout << "valid password" << endl;
    else
        cout << "invalid password" << endl;
    
    return 0;
}
