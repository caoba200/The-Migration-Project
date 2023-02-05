//
//  Q2 - Assignment #1 - CS 110
//
//  Created by Bao D. Cao on 2016-09-18.
//  Copyright © 2016 Bao D. Cao. All rights reserved.
//

#include <iostream>

using namespace std;

/* Question 2: Enter the subtotal and gratuity rate. Compute and display 
 the gratuity and total. (Programming exercise 2.5)*/

int main() {
    
    /* Step 1: Declare two variables subtotal and rate. Use "float" type because the test cases for this question
     will not be too large, and float type has smaller size than double */
    float subtotal; // Subtotal
    float rate;     // Gratuity rate
    
    // Step 2: ask user to enter subtotal and gratuity rate
    
    cout << "Enter the subtotal and gratuity rate: ";
    cin >> subtotal >> rate;
    
    // Step 3: Caculate the gratuity
    float gratuity = subtotal * rate / 100; // The gratuity rate user enter needs to be change to percentage by the formula: rate(percentage) = rate / 100
    
    //Step 4: Display result (total = gratiuty + subtotal)
    cout << "The gratuity is $" << gratuity << " and total is $" << gratuity + subtotal << endl;
    
    return 0;
}
