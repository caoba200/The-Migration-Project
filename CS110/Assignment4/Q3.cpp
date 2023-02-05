/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 4
 
 // Program name: While-loop control by a sentinal value
 
 // Created by Bao D. Cao on 2016-11-10.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Use while-loop to read the information as long as it != 0
 //                 2. For each number has been read, update max, min, total, negative, possitive and count
 
 // Major variables: positive, negative, total, maximum, minimum, count, number
 
 **********************************************************************/

#include <iostream>

using namespace std;

int main() {
    
    int positive = 0;
    int negative = 0;
    int total = 0;
    int maximum = 0;
    int minimum = 0;
    int count = 0;
    int number;
    
    // Step 1: Read the first number
    cout << "Enter an integer, the input ends if it is 0: ";
    
    cin >> number;
    maximum = number;
    minimum = number;
    
    // Step 2: Update and read the next number until encounter 0
    while (number != 0) {
        // Update maximum and minimum
        maximum = number > maximum ? number : maximum;
        minimum = number < minimum ? number : minimum;
        // Update the number of positives and negatives
        if (number > 0)
            positive++;
        else
            negative++;
        // Add up the new number to the total
        total += number;
        count++; // Update the counter which will be use for calculating average
        // Read the next number
        cin >> number;
    }
    
    // Step 3: Show the result
    if (count == 0) {
        cout << "No number are entered except 0" << endl;
    }
    else{
        cout << "The number of positives: " << positive << endl;
        cout << "The number of negatives: " << negative << endl;
        cout << "The biggest number: " << maximum << endl;
        cout << "The smallest number: " << minimum << endl;
        cout << "The total is " << total << endl;
        cout << "The average is " << (double)total / (double)count << endl;
    }

    
    return 0;
}
