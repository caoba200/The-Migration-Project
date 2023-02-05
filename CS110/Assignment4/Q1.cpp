/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 4
 
 // Program name: Table of sin(x) and cos(x)
 
 // Created by Bao D. Cao on 2016-11-10.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: use mathematical functions to calculate sin x and cos x
 //                 use loop structure to display the result
 
 // Major variables: a constant number PI
 
 **********************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    
    const double PI = 3.14159; // Define the constant Pi
    
    // Step 1: Set up the number of decimal places which will be shown
    
    cout << fixed << showpoint;
    
    // Step 2 : Display the first line
    cout << setw(12) << "a" << setw(12) << "sin(a)" << setw(12) << "cos(a)" << endl;
    
    // Step 3 : Calculate the value of sin x and cos x and display the result
    // The value of angles must be translate to radian in other to compute sin x and cos x
    // x (degree) = x * PI / 180 (radian)
    for (int i = 0; i <= 90; i += 5){
        cout << setw(12) << setprecision(1) << i << setw(12) << setprecision(4) << sin(i * PI / 180.0) << setw(12) << cos(i * PI / 180.0) << endl;
    }
    
    return 0;
}
