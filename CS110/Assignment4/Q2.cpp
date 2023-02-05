/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 4
 
 // Program name: Distance from Regina
 
 // Created by Bao D. Cao on 2016-11-10.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Calculate the distance base on the formula
 //                 2. Use while loop to ask user whether she wants to do the computation
 
 // Major variables: a constant number P, longtitude, latitude, Regina_lat, Regina_long, distance
 
 **********************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>

using namespace std;

int main() {
    
    const double PI = 3.141592; // Define the constant Pi
    
    double longtitude, latitude; // longtitude and latitude
    double Regina_lat = 50.4547; // Regina's latitude
    double Regina_long = 104.6067; // Regina's longtitude
    double distance; // distance between 2 point
    char comma; // a character which the seperator (comma) will be read in
    char answer;
    
    
    cout << fixed << showpoint << setprecision(11);
    
    // Convert Regina's GPS coordinate to radian
    Regina_lat = Regina_lat * PI / 180.0;
    Regina_long = Regina_long * PI / 180.0;
    
    while(1) {
        
        // Step 1: Prompt user enter the latitude and longtitude of 2 locations
        
        cout << "Enter location (latitude and longtitude) in degrees: " << endl;
        cin >> latitude >> comma >> longtitude;
        
        // Step 2: Convert the GPS coordinate to radian
        
        latitude = latitude * PI / 180.0;
        longtitude = longtitude * PI / 180.0;
        
        // Step 3: Calculate the distance between 2 locations:
        
        distance = 6378.1 * acos(sin(Regina_lat) * sin(latitude) + cos(Regina_lat) * cos(latitude) * cos(Regina_long - longtitude));
        
        // Step 4: Display the result:
        
        cout << "The distance between Regina and the city you picked is: " << distance << " km" << endl;
        
        // Step 5: Ask user whether she wants to continue the computation
        
        cout << ".............................................................................." << endl;
        cout << "Do you want to compute the distance between Regina and another city? (Y/N): ";
        cin >> answer;
        
        bool quit;
        while(1) {
            if (answer == 'Y' || answer == 'y'){
                quit = false;
                break;
            }
            else if(answer == 'N' || answer == 'n') {
                quit = true;
                break;
            }
            else {
                cout << "The answer is invalid!! Please try again: ";
                cin >> answer;
            }
        }
        
        if (quit) {
            cout << "The program is terminated!!" << endl;
            break;
        }
    }
    
    return 0;
}
