/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: Find the number of days in a month
 
 // Created by Bao D. Cao on 2016-10-11.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: use if-else structure to determine which month has 31
                    , 30, and check for leap yar for February, assign the
                    number to corresponding strings by switch structure
 
 // Major variables: month, year, days_of_month, _month
 
 **********************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main() {
    
    int month, year; // month and year
    int days_of_month; // number of days in a month
    string _month;    // month in string format
    
    // Step 1: Prompt user enter the month and year
    cout << "Enter the month: " ;
    cin >> month;
    
    cout << "Enter the year: ";
    cin >> year;
    
    // Step 2: Check if the month is invalid
    if (month < 1 || month > 12){
        cout << "The month is invalid" << endl;
        return 1;
    }
    
    // Step 3: Check if the year is invalid: Only consider the year > 0
    if (year < 0) {
        cout << "The year is invalid" << endl;
        return 2;
    }
    
    // Step 4: Check the month and assign the corresponding day.
    switch (month){
        case 1:
            _month = "January";
            days_of_month = 31;
            break;
        case 3:
            _month = "March";
            days_of_month = 31;
            break;
        case 5:
            _month = "May";
            days_of_month = 31;
            break;
        case 7:
            _month = "July";
            days_of_month = 31;
            break;
        case 8:
            _month = "August";
            days_of_month = 31;
            break;
        case 10:
            _month = "October";
            days_of_month = 31;
            break;
        case 12:
            _month = "December";
            days_of_month = 31;
            break;
        case 4:
            _month = "April";
            days_of_month = 30;
            break;
        case 6:
            _month = "June";
            days_of_month = 30;
            break;
        case 9:
            _month = "September";
            days_of_month = 30;
            break;
        case 11:
            _month = "November";
            days_of_month = 30;
            break;
        case 2: {
            _month = "February";
            // Consider the case year is a leap year: Februaray will have 29 days
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
                days_of_month = 29;
            }
            else
                days_of_month = 28;
            break;
        }
        default:
            break;
    }
    
    // Step 5: Display the result
    cout << _month << " " << year << " had " << days_of_month << " days." << endl;
    
    return 0;
}
