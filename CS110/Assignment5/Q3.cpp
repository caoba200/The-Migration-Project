/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 5
 
 // Program name: Print Distinct Number
 
 // Created by Bao D. Cao on 2016-11-24.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Continuously read numbers from the input file
                    2. For each number read in, compare with those in the array
                    3. Add it to the array if it is distinct
                    4. Display the result
 // Major variables: number, distinct[100], counter, input (input file stream)
 
 **********************************************************************/

#include <iostream>
#include <fstream>

using namespace std;

// Check if the number is duplicated with one in the array
bool match(int[], int, int);

// Display the result
void display(int[], int);

int main() {
    
    int number;
    int distinct[100];
    int counter = 0;
    ifstream input;
    input.open("ass5Q3_testingInput.txt");
    
    // Step 1: Initialize the first value for the array
    input >> number;
    distinct[counter] = number;
    counter++;
    
    // Step 2: Read through the file until encounter eof
    while(input) {
        input >> number;
        if (!match(distinct, counter, number)) {
            distinct[counter] = number;
            counter++;
        }
    }
    
    // Step 3: Display the result
    display(distinct, counter);
    
    input.close();
    
    return 0;
}

/***************************************************************/
// Step 1: Compare the number with those in the distinct array
// Step 2: return true if there is one number has the same value, false in vice versa
/***************************************************************/
bool match(int distinct[], int size, int number) {
    for (int i = 0; i < size; i++)
        if (number == distinct[i])
            return true;
    return false;
}

/***************************************************************/
// Display each element in the array using for loop
/***************************************************************/
void display(int distinct[], int size) {
    cout << "The distinct numbers are: " ;
    for (int i = 0; i < size; i++)
        cout << distinct[i] << " ";
    cout << endl;
}
