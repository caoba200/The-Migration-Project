/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 5
 
 // Program name: Longest Common Prefix
 
 // Created by Bao D. Cao on 2016-11-24.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Prompt user enter 2 string
                    2. Call prefix function
 
 // Major variables: s1, s2, s3
 
 **********************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

/*********************************************************************/
// Function name: prefix
// Arguments: s1, s2, commonPrefix
// Algorithm:
        // 1. Compare the first letter of 2 strings --> if not equal --> no common prefix
        // 2. Initialize index(position when 2 corresponding letters of 2 stirngs are not matched)
        // 3. Run through every letter of 2 strings to find index
        // 4. Assign letters from 0 to index to commonPrefix
        // 5. Display the result
/*********************************************************************/

void prefix( const char s1[], const char s2[], char commonPrefix[]) {
    if (s1[0] != s2[0])
        cout << s1 << " and " << s2 << " have no common prefix." << endl;
    else {
        int index = 0;
        unsigned long shorter = strlen(s1) < strlen(s2) ? strlen(s1) : strlen(s2); // Length of the shorter string
        // Find the position where s1 != s2
        for (; index < shorter; index++) {
            if (s1[index] != s2[index])
                break;
        }
        for (int i = 0; i < index; i++) {
            commonPrefix[i] = s1[i];
        }
        
        cout << "The common prefix is " << commonPrefix << endl;
    }
}

int main() {
    
    char s1[50];
    char s2[50];
    char s3[50];
    
    // Step 1: Prompt user enter 2 string
    cout << "Enter s1: ";
    cin.getline(s1, 50);
    
    cout << "Enter s2: ";
    cin.getline(s2, 50);
    
    // Step 2: Call the function prefix to find the longest common prefix
    prefix(s1, s2, s3);

    return 0;
}
