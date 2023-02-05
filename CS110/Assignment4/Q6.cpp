/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 4
 
 // Program name: Vowels and Consonants
 
 // Created by Bao D. Cao on 2016-11-10.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: Read the input file line by line. In each line use switch-case to determine vowels and
 //                     consonants
 // Major variables: line, vowels, consonants, input
 
 **********************************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    
    string line;
    int vowels = 0; // Vowel counter
    int consonants = 0; // Consonant counter
    
    // Step 1: create an object for the input file
    ifstream input;
    input.open("ass4_Q6_Input.txt");
    
    // Step 2: Read the input file and check for vowels and consonants
    while(input){ // Read until encounter EOF
        getline(input, line); // Read one line a time and assign to "line"
        
        for(int i = 0; i < line.length(); i++){
            if (isalpha(line[i])) // Check if each element is alpha
                switch(line[i]){
                    case 'A':
                    case 'a':
                    case 'E':
                    case 'e':
                    case 'I':
                    case 'i':
                    case 'O':
                    case 'o':
                    case 'U':
                    case 'u':
                        vowels++;
                        break;
                    default:
                        consonants++;
                        break;
            }
        }
    }
    
    // Step 3: Display the result
    cout << "The number of vowels is " << vowels << endl;
    cout << "The number of consonants is " << consonants << endl;
    
    input.close(); // Close the input file
    
    return 0;
}
