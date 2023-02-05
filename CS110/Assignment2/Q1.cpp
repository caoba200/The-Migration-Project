/*********************************************************************
                                                                     
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: Find future dates
 
 // Created by Bao D. Cao on 2016-10-11.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: use the formula future_day = (today + num) % 7
 
 // Major variables: today, num, future_day, day, day2
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    int today;      // today's day of the week
    int num;        // number of days after today
    int future_day; // future day of the week in integer format
    string day = "";// future day of the week in string format
    string day2 = ""; // today's day in string format
    
    // Step 1: Prompt user enter today's day of the week (Sunday is 0, Monday is 1,...)
    cout << "Enter today's day: ";
    cin >> today;
    
    // Prompt user enter number of days after today for a future day.
    cout << "Enter the number of days elapsed since today: ";
    cin >> num;
    
    // Assign the integer values to the corresponding days (today)
    switch(today) {
        case 0:
            day2 = "Sunday";
            break;
        case 1:
            day2 = "Monday";
            break;
        case 2:
            day2 = "Tuesday";
            break;
        case 3:
            day2 = "Wednesday";
            break;
        case 4:
            day2 = "Thursday";
            break;
        case 5:
            day2 = "Friday";
            break;
        case 6:
            day2 = "Saturday";
        default:
            break;
 
    }
    
    // Step 2: Calculate the future day in integer format
    if (today >= 0 && today <= 6){  // check if the value is valid
        future_day = (today + num) % 7;
        // Assign the integer values to the corresponding days: 0 is Sunday, etc.
        switch(future_day) {
            case 0:
                day = "Sunday";
                break;
            case 1:
                day = "Monday";
                break;
            case 2:
                day = "Tuesday";
                break;
            case 3:
                day = "Wednesday";
                break;
            case 4:
                day = "Thursday";
                break;
            case 5:
                day = "Friday";
                break;
            case 6:
                day = "Saturday";
            default:
                break;
        }
        
        // Step 3: Display the result
        cout << "Today is " << day2 << " and the future day is " << day << endl;
    }
    else {  // Check the situation when user enter a value outside [0,6]
        cout << "Error: The input value is invalid!!!" << endl;
    }
    
    return 0;
}
