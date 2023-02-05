/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: Computing great circle distance
 
 // Created by Bao D. Cao on 2016-10-26.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: use the formula d = radius * arcos(sin(x1) * sin(x2) + cos(x1) * cos(x2) * cos(y1 - y2))
 
 // Major variables: a constant number PI, lat1, long1, lat2, long2, distance
 
 **********************************************************************/


#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>

using namespace std;

int main() {
    
    // Answer to part a: Find the GPS coordinates for the following cities from the Internet
    
    /*************************************
    *                                    *
    * - Saskatoon : (52.1332, 106.6700)  *
    * - Calgary : (51.0486, 114.0708)    *
    * - Vancouver: (49.2827, 123.1207)   *
    * - Toronto: (43.6532, 79.3832)      *
    * - Ottawa: (45.4215, 75.6972)       *
    * - Montreal: (45.5017, 73.5673)     *
    *                                    *
    **************************************/
    
    // Program for part b:
    
    const double PI = 3.14159265359; // Define the constant Pi
    
    double long1, lat1; // longtitude and latitude of location 1
    double long2, lat2; // longtitude and latitude of location 2
    double distance; // distance between 2 point
    char comma; // a character which the seperator (comma) will be read in
    
    // Step 1: Prompt user enter the latitude and longtitude of 2 locations
    
    cout << "Enter location 1 (latitude and longtitude) in degrees: " << endl;
    cin >> lat1 >> comma >> long1;
    
    cout << "Enter location 2 (latitude and longtitude) in degrees: " << endl;
    cin >> lat2 >> comma >> long2;
    
    // Step 2: convert these values to radian
    
    lat1 = lat1 * PI / 180.0;
    long1 = long1 * PI / 180.0;
    
    lat2 = lat2 * PI / 180.0;
    long2 = long2 * PI / 180.0;
    
    // Calculate the distance between 2 locations:
    
    distance = 6378.1 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(long1 - long2));
    
    // Display the result:
    
    cout << fixed << showpoint << setprecision(11);
    cout << "The distance between the 2 locations is: " << distance << " km" << endl;

    
    return 0;
}
