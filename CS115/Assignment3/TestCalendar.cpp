/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #3
 
 // Program name: Calendar
 // Date : February 9, 2017
 // Filename : TestCalendar.cpp
 **************************************************/

#include <iostream>
#include "Calendar.h"
#include <string>

using namespace std;

//==================================== DRIVER =========================================

int main() {
    
    //========================== Variable decleration =================================
    string date;
    int month, day, year;
    
    //========================== 1st Object initialization ============================
    dateInput(date);
    
    inputHandle(date, month, day, year);
    
    Calendar date1(month, day, year);
    
    dateHandle(date1, date, month, day, year);
    
    //========================== Output area =======================================
    cout << "The string version of the date is: " << date1.toString() << endl;
    
    date1.nextDate();
    
    cout << "The next day in string version is: " << date1.toString() << endl;
    
    //========================== 2nd Object initialization ============================
    dateInput2(date);
    
    inputHandle(date, month, day, year);
    
    Calendar date2(month, day, year);
    
    dateHandle(date2, date, month, day, year);
    
    //========================== Display the comparation ===============================
    compare(date1.compareDate(date2));
    
    return 0;
}
