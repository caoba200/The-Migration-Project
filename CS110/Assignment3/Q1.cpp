/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: Table of sin(x) and cos(x)
 
 // Created by Bao D. Cao on 2016-10-26.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: use mathematical functions to calculate sin x and cos x
 
 // Major variables: a constant number PI
 
 **********************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    
    const double PI = 3.14159265359; // Define the constant Pi
    
    // Step 1: Set up the number of decimal places which will be shown
    
    cout << fixed << showpoint << setprecision(4); // Set 4 decimal digits for the result
    
    // Step 2 : Display the first line
    cout << setw(12) << "a" << setw(12) << "sin(a)" << setw(12) << "cos(a)" << endl;
    
    // Step 3 : Calculate the value of sin x and cos x and display the result
    // The value of angles must be translate to radian in other to compute sin x and cos x
    // x (degree) = x * PI / 180 (radian)
    
    cout << setw(12) << "0.0" << setw(12) << sin(0.0 * PI / 180.0) << setw(12) << cos(0.0 * PI / 180.0) << endl;
    
    cout << setw(12) << "30.0" << setw(12) << sin(30.0 * PI / 180.0) << setw(12) << cos(30.0 * PI / 180.0) << endl;
    
    cout << setw(12) << "45.0" << setw(12) << sin(45.0 * PI / 180.0) << setw(12) << cos(45.0 * PI / 180.0) << endl;
    
    cout << setw(12) << "60.0" << setw(12) << sin(60.0 * PI / 180.0) << setw(12) << cos(60.0 * PI / 180.0) << endl;
    
    // Because Pi is an appropximate value, cos (Pi / 2) will not equal 0 but a very big negative number close to 0
    // therefore the result need to be multiplied with -1 to terminate the negative sign.
    
    cout << setw(12) << "90.0" << setw(12) << sin(90.0 * PI / 180.0) << setw(12) << cos(90.0 * PI / 180.0) * (-1) << endl;
    
    
    return 0;
}
