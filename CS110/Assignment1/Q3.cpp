//
//  Q3 - Assignment #1 - CS 110
//
//  Created by Bao D. Cao on 2016-09-18.
//  Copyright © 2016 Bao D. Cao. All rights reserved.
//

#include <iostream>

using namespace std;

/* Question 3: Enter an integer between 0 and 100 and adds all digits in the integer (Programming exercise 2.6)*/

int main() {
    
    // Step 1: Declare a variable represent to the number user enter
    int num;
    
    // Step 2: Ask user enter an integer between 0 and 1000
    cout << "Enter an integer between 0 and 1000: " ;
    cin >> num;
    
    // Step 3: Separate digits in the integer
    int first = num % 10; // Take the first digit and store it to the variable name first.
    int second = num % 100 / 10; // Take the second digit and store it to the variable name second. second will equal 0 if num is an 1 digit integer.
    int third = num % 1000 / 100; // Take the third digit and store it to the variable name third. third will equal 0 if num has less than 3 digits.
    int last = num / 1000; // Take the last digit and store it to the variable name last. last will = 0 if num < 1000
    
    // Step 4: Caculate the sum of all digits and store it to sum
    int sum = first + second + third + last;
    
    // Step 5: Display the result.
    cout << "The number you have chosen is: " << num << endl;
    cout << "The sum of all digits is: " << sum << endl;
    
    return 0;
}
