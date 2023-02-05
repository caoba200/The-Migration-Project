/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: Sort three number
 
 // Created by Bao D. Cao on 2016-10-11.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: swap their value to determine the desirable order
 
 // Major variables: num1, num2, num3, temp
 
 **********************************************************************/

#include <iostream>

using namespace std;

int main() {
    
    int num1, num2, num3; // three integer
    int temp; // variable used for swaping number
    
    // Step 1: Prompt user enter 3 integer numbers
    cout << "Enter three integer numbers: ";
    cin >> num1 >> num2 >> num3;
    
    // Step 2: Sort these numbers:
    // Swap num1 and num2 if num1 > num2
    if (num1 > num2) {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
    // Swap num2 and num3 if num2 > num3
    if (num2 > num3) {
        temp = num2;
        num2 = num3;
        num3 = temp;
    }
    // Swap num1 and num2 again (in case the original num3 (assigned to num2) < num1)
    if (num1 > num2) {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
    
    // Step 3: Display these number in non-decreasing order
    cout << "The integers in non-decreasing order: " << num1 << " " << num2 << " " << num3 << endl;
    
    
    return 0;
}
