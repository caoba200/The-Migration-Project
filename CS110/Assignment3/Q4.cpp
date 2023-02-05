/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: String comparisions
 
 // Created by Bao D. Cao on 2016-10-26.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 
 // Main algorithm: Compare the names to find out the alphabetical order
 
 // Major variables: city1, city2, city3, first, last, middle
 
 **********************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main() {
    
    string city1, city2, city3; // Name of 3 cities
    string first, last, middle; // Cities have name in the first order, last order and middle order
    
    // Step 1: Prompt user enter the name of 3 cities:
    
    cout << "Enter the first city: ";
    getline(cin, city1);
    
    cout << "Enter the second city: ";
    getline(cin, city2);
    
    cout << "Enter the third city: ";
    getline(cin, city3);
    
    // Step 2: Compare these cities and assign them to first, middle and last
    
    if (city1 <= city2 && city1 <= city3){
        first += city1;
        if (city2 <= city3){
            middle += city2;
            last += city3;
        }
        else{
            middle += city3;
            last += city2;
        }
    }
    else if (city2 <= city1 && city2 <= city3){
        first += city2;
        if (city1 <= city3){
            middle += city1;
            last += city3;
        }
        else{
            middle += city3;
            last += city1;
        }
    }
    else{
        first += city3;
        if (city1 <= city2){
            middle += city1;
            last += city2;
        }
        else{
            middle += city2;
            last += city1;
        }
    }

    // Step 3: Display the result
    
    cout << "The three cities in alphabetical order are: " << first << ", " << middle << ", " << last << ", " << endl;
    
    
    return 0;
}
