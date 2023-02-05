/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #3
 
 // Program name: Calendar
 // Date : February 9, 2017
 // Filename : Calendar.h
**************************************************/

#ifndef Calendar_h
#define Calendar_h

#include <string>

using namespace std;

//============== CLASS CALENDAR =============
class Calendar {
    
public:
    
    Calendar(); //Constructor
    Calendar(int m, int d, int y); //Constructor with parameters
    
    //============== Calendar::toString : string ===============
    //Convert the date in the object to string format
    //==========================================================
    string toString() const;
    
    //============== Calendar::nextDate : Date =================
    //update the date in the object to the next corresponding date
    //==========================================================
    void nextDate();
    
    //============== Calendar::compareDate : int ===============
    //compare the date with another one in a different object
    //return 0 : 2 dates are equal
    //return 1 : the obj of interest's date is smaller
    //return -1: the obj of interest's date is bigger
    //==========================================================
    int compareDate(const Calendar &c) const;
    
    bool correctedDay; //an attribute that indicates if the day is correct
    bool correctedMonth; //an attribute that indicates if the month is correct
    bool correctedYear; //an attribute that indicates if the year is correct
    
    //===================== Modifier : setDay : bool ===============
    //return true if the the day is correct
    //otherwise, set day to default and return false
    //==============================================================
    bool setDay(int d);
    
    //===================== Modifier : setMonth : bool =============
    //return true if the month is correct
    //otherwise, set month to default and return false
    //==============================================================
    bool setMonth(int m);
    
    //===================== Modifier : setYear : bool ==============
    //return true if the year is correct
    //otherwise, set year to default and return false
    //==============================================================
    bool setYear(int y);

private:
    int month;
    int day;
    int year;
    //An array of months contain the month in their string form
    static const string months[12];
    //An array of days that contain the maximum day of the corresponding month (assume Feb has 28 days)
    static const int days[12];
    
    //===================== Calendar::dayToString : string ==========
    //return the day in string form plus their postfix (st, nd, rt, th)
    //===============================================================
    string dayToString() const;
    
    //===================== Calendar::leapYear : bool ===============
    //return true if year is leap year
    //===============================================================
    bool leapYear() const;
    
    //===================== Calendar::endOfYear : bool ==============
    //return true if the date is December 31
    //===============================================================
    bool endOfYear() const;
    
    //===================== Calendar::endOfMonth : bool =============
    //return true if day is the last day of month
    //===============================================================
    bool endOfMonth() const;
};

//=========== DRIVER'S FUNCTIONS ==============


//==================== dateInput : void ===============
//ask user enter his desire date
//check the format
//put the entered string into date
//=====================================================
void dateInput(string &date);

//================== dateFormat : bool =============
//Check if the format of user input is correct
//Return true if the format of date is correct
//==================================================
bool dateFormat(string date);

//=================== dateInput2 : void ===============
//the same to dateInput
//=====================================================
void dateInput2(string &date);

//=================== inputHandle : void ================
//seperate the input string and put them in corresponding parametters
//  by using stringstream
//======================================================
void inputHandle(string date, int &month, int &day, int &year);

//=================== errorHandle : void ===============
//determine the error of the date in c and show the message
//======================================================
void errorHandle(const Calendar c);

//=================== createDate : void ================
//set month, day and year of the object c
//======================================================
void createDate(Calendar &c, int m, int d, int y);

//================== compare : void ====================
//show the message compare 2 dates based on the parameter
//======================================================
void compare(int flag);

//========================= dateHandle : void ======================
//ask user input his desired date unless the date is correct
//===================================================================
void dateHandle(Calendar &c, string date, int month, int day, int year);


#endif
