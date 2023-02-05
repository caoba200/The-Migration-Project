/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 5
 
 // Program name: Check Substring
 
 // Created by Bao D. Cao on 2016-11-24.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Prompt user enter 2 strings
                    2. Call the function indexOf to find the index of the 1st character of the substring
 // Major variables: s1 and s2
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

// Return the index of the first letter if the 1st string is a substring of the 2nd string
int indexOf(const string&, const string&);

int main() {
    
    string s1, s2;
    
    // Step 1: Prompt user enter the first string and the second string
    cout << "Enter the first string: ";
    getline(cin, s1);
    
    cout << "Enter the second string: ";
    getline(cin, s2);

    // Step 2: Find the index and display the result
    cout << "indexOf(\"" << s1 << "\", " << "\"" << s2 << "\")" << " is " << indexOf(s1, s2) << endl;
    
    return 0;
}

/**************************************************************************/
// Step 1: Run through every letter of the 2nd string to find the match position of it with the 1st letter of
//          the 1st string
// Step 2: From that position, check if the 1st stirng equal s2.substr(i, s1.length()), i is the match position
//         if it matches, break the loop.
// Return the index of the first letter if the 1st string is a substring of the 2nd string
/**************************************************************************/
int indexOf(const string& s1, const string& s2) {
    bool match = false;
    int i;
    for(i = 0; i < s2.length(); i++){
        if (s1[0] == s2[i]){
            if(s1 == s2.substr(i, s1.length())){
                match = true;
                break;
            }
        }
    }
    return match ? i : -1;
}
