/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: String computation
 
 // Created by Bao D. Cao on 2016-10-26.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 
 // Main algorithm: Use substr and string concatenation to create appropripate ID
 
 // Major variables: firstname, lastname, year, id
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    string firstname, lastname, year, id;
    
    // Step 1: Prompt user enter first name, last name and year
    
    cout << "First name entered: " ;
    getline(cin, firstname);
    
    cout << "Last name entered: " ;
    getline(cin, lastname);
    
    cout << "Year entered: " ;
    getline(cin, year);
    
    // Step 2: Construct account ID based on the information provided
    
    // Check if year is valid (year is a 4 digit integer)
    if (year.length() != 4){
        cout << "The year is invalid!!!" << endl;
        return 0; // Stop the program
    }
    if (isdigit(year[0]) && isdigit(year[1]) && isdigit(year[2]) && isdigit(year[3]))
        ;
    else {
        cout << "The year is invalid!!!" << endl;
        return 0;
    }
    
    // Check the length of name and concatenate it with id
    if (firstname.length() < 6)
        id += firstname;
    else
        id += firstname.substr(0, 5);
    
    id += ".";
    
    if (lastname.length() < 7)
        id += lastname;
    else
        id += lastname.substr(0, 6);
    
    id += year.substr(2, 2);
    
    // Step 3: Display the account ID
    
    cout << endl << id << endl;
    
    return 0;
}
