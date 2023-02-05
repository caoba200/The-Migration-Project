
//  Calendar.cpp

#include "Calendar.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


//=================================================================
//=========================== CLASS IMPLEMENTATION ================
//=================================================================



//Array initialization
const string Calendar::months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int Calendar::days[]  = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Calendar::Calendar() : month(1), day(1), year(1900) {
    correctedDay = true;
    correctedMonth = true;
    correctedYear = true;
}

Calendar::Calendar(int m, int d, int y) {
    correctedYear = setYear(y);
    correctedMonth = setMonth(m);
    correctedDay = setDay(d);
}

//============== Calendar::toString : string ===============
//Convert the date in the object to string format
//==========================================================
string Calendar::toString() const {
    //Can not use to_string because CC on hercules doesn't support C++11 (WHY?????????????)
    stringstream ss;
    ss << year;
    return months[month - 1] + " " + dayToString() + ", " + ss.str();
}

//===================== Calendar::dayToString : string ==========
//return the day in string form plus their postfix (st, nd, rt, th)
//===============================================================
string Calendar::dayToString() const{
    stringstream ss;
    ss << day;
    string result = ss.str();
    switch(day % 10) {
        case 1:
            result += "st";
            break;
        case 2:
            result += "nd";
            break;
        case 3:
            result += "rd";
            break;
        default:
            result += "th";
    }
    
    return result;
}

//============== Calendar::nextDate : Date =================
//update the date in the object to the next corresponding date
//==========================================================
void Calendar::nextDate() {
    if (endOfYear()) { //Increase year if this is the last day of year
        month = 1; //reset month
        day = 1;   //reset day
        year++;
    }
    else if (endOfMonth()) { //Increase month if this is the last day of month
        month++;    //reset month
        day = 1;
    }
    else
        day++; //increase day
}

//============== Calendar::compareDate : int ===============
//compare the date with another one in a different object
//return 0 : 2 dates are equal
//return 1 : the obj of interest's date is smaller
//return -1: the obj of interest's date is bigger
//==========================================================
int Calendar::compareDate(const Calendar &c) const {
    if (year > c.year)
        return -1;
    if (year < c.year)
        return 1;
    if (month > c.month)
        return -1;
    if (month < c.month)
        return 1;
    if (day > c.day)
        return -1;
    if (day < c.day)
        return 1;
    return 0; // 2 dates are equal
}

//===================== Calendar::leapYear : bool ===============
//return true if year is leap year
//===============================================================
bool Calendar::leapYear() const {
    return (year % 400 == 0|| (year % 4 == 0 && year % 100 != 0));
}

//===================== Calendar::endOfYear : bool ==============
//return true if the date is December 31
//===============================================================
bool Calendar::endOfYear() const {
    return day == 31 && month == 12;
}

//===================== Calendar::endOfMonth : bool =============
//return true if day is the last day of month
//===============================================================
bool Calendar::endOfMonth() const {
    if (month == 2 && leapYear())
        return day == 29;
    return day == days[month - 1];
}

//===================== Modifier : setMonth : bool =============
//return true if the month is correct
//otherwise, set month to default and return false
//==============================================================
bool Calendar::setMonth(int m) {
    if (m > 0 && m < 13) {
        month = m;
        return true;
    }
    else {
        month = 1;
        return false;
    }
}

//===================== Modifier : setYear : bool ==============
//return true if the year is correct
//otherwise, set year to default and return false
//==============================================================
bool Calendar::setYear(int y) {
    if (y >= 1000 && y < 10000){ // Year is in the range from 1000 to 9999
        year = y;
        return true;
    }
    else {
        year = 1900;
        return false;
    }
}

//===================== Modifier : setDay : bool ===============
//return true if the the day is correct
//otherwise, set day to default and return false
//==============================================================
bool Calendar::setDay(int d) {
    if (leapYear() && month == 2) {
        if (d > 0 && d < 30) {
            day = d;
            return true;
        }
        else {
            day = 1;
            return false;
        }
    }
    //If d in the range from 0 to the max of its month (using the array days)
    if (d > 0 && d <= days[month - 1]) {
        day = d;
        return true;
    }
    else {
        day = 1;
        return false;
    }
}

//===================================================================
//============================ DRIVER FUNCTIONS =====================
//===================================================================



//================== dateFormat : bool =============
//Check if the format of user input is correct
//Return true if the format of date is correct
//==================================================
bool dateFormat(string date) {
    if (date.length() != 10) //the length is not 10
        return false;
    if (date[2] != '-' || date[5] != '-') //the dash letter is not in position 2 and 5
        return false;
    for (int i = 0; i < date.length(); i++) { // each character except dash is a digit
        if (i != 2 && i != 5)
            if (!isdigit(date[i]))
                return false;
    }
    
    return true;
}

//==================== dateInput : void ===============
//ask user enter his desire date
//check the format
//put the entered string into date
//=====================================================
void dateInput(string &date) {
    cout << "Enter the first date using the format mm-dd-yyyy: ";
    cin >> date;
    //Ask again if the format is incorrect
    while (!dateFormat(date)) {
        cout << "Incorrect format!" << endl;
        cout << "Enter the first date using the format mm-dd-yyyy: ";
        cin >> date;
    }
}

//=================== dateInput2 : void ===============
//the same to dateInput
//=====================================================
void dateInput2(string &date) {
    cout << "Enter the second date using the format mm-dd-yyyy: ";
    cin >> date;
    
    while (!dateFormat(date)) {
        cout << "Incorrect format!" << endl;
        cout << "Enter the second date using the format mm-dd-yyyy: ";
        cin >> date;
    }
}

//=================== inputHandle : void ================
//seperate the input string and put them in corresponding parametters
//  by using stringstream
//======================================================
void inputHandle(string date, int &month, int &day, int &year) {
    stringstream ss(date);
    char temp, temp1;
    
    ss >> month >> temp >> day >> temp1 >> year;
    
}

//=================== errorHandle : void ===============
//determine the error of the date in c and show the message
//======================================================
void errorHandle(const Calendar c) {
    if (!c.correctedMonth)
        cout << "Incorrect month!" << endl;
    else if (!c.correctedDay)
        cout << "Incorrect day!" << endl;
    else if (!c.correctedYear)
        cout << "Incorrect year!" << endl;
}

//=================== createDate : void ================
//set month, day and year of the object c
//======================================================
void createDate(Calendar &c, int m, int d, int y) {
    c.correctedMonth = c.setMonth(m);
    c.correctedYear = c.setYear(y);
    c.correctedDay = c.setDay(d);
}

//================== compare : void ====================
//show the message compare 2 dates based on the parameter
//======================================================
void compare(int flag) {
    switch(flag) {
        case -1:
            cout << "The first date comes after the second one." << endl;
            break;
        case 0:
            cout << "Two dates are equal." << endl;
            break;
        case 1:
            cout << "The first date comes before the second one." << endl;
            break;
    }
}

//========================= dateHandle : void ======================
//ask user input his desired date unless the date is correct
//===================================================================
void dateHandle(Calendar &c, string date, int month, int day, int year) {
    while(!c.correctedDay || !c.correctedYear || !c.correctedMonth) {
        errorHandle(c); //Display the error
        dateInput(date);//ask for input again
        inputHandle(date, month, day, year); //analyze the input string
        createDate(c, month, day, year);    //put data into the object
    }
}
