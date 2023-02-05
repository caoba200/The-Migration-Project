/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment 4
 
 // Program name: Print Calendar
 
 // Created by Bao D. Cao on 2016-11-10.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: 1. Prompt user enter year and the fist day
 //                 2. Create a output file for the calendar.
 //                 3. Create the calendar: for each month create the title and a table of corresponding days.
 //                                     Write them to the file.
 
 // Major variables: year, day
 
 **********************************************************************/


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*----------------Function name: get_month()----------------------------------------
  Return type: string
  Description: convert the number represent for month to the corresponding month
  Parameters: int month
  Algorithm: use switch - case structure to determine the month -----------------*/
string get_month(int);

/*-----------------Function name: days_of_month(int, int)------------------------------------
  Return type: integer
  Description: determine the number of days in a month (ie: Jan has 31 days, April has 30 days...)
  Parameters: int month, int year
  Algorithm: use switch - case structure to determine the days of a month --------*/
//------------------------------------------------------------------------------------------
int days_of_month(int, int);

/*------------------Function name: get_title(string, int, ofstream&)--------------------------------
  Return type: void
  Description: Create the title for the month and write it to the file
  Parameters: string month, int year, ofstream& output_file
  Algorithm:  setw(31) << "month year" << endl ----> output_file;
              "     -------------------------" << endl ----> output_file;
              "setw Sun setw Mon setw Tue setw Wed setw Thurs setw Fri setw Sat" ------> output_file;
 ---------------------------------------------------------------------------------------------------*/
void get_title(string, int, ofstream&);

/*------------------Function name: get_table(int, int, ofstream&)--------------------------------
 Return type: void
 Description: Create the table of the days of the month
 Parameters: int& day(Mon, Tue...), int days_of_month, ofstream& output_file
 Algorithm:  print "space" from Sunday to "day" (ie. day is Wed so print " " from Sunday to Wednesday):
                    for (i from 0 to day) : "      " -------> output_file;
             print the number from 1 to days_of_month under the corresponding day, if encounter Saturday
                    go to new line
                    for (i from 1 to days_of_month): 
                        if day is Saturday
                            i << endl -----------> output_file;
                        else
                            i -------------------> output_file;
                        update day: day = (day + 1) % 7
 ---------------------------------------------------------------------------------------------------*/
void get_table(int&, int, ofstream&);


/*--------------------------Main function----------------------------------------------------
           decleare variable year and day;
           prompt user enter year and day;
           create an output stream file: ofstream opfile;
           opfile.open(name of the file.txt);
           for (i from 0 to 11): get_title; get_table;
           opfile.close();
 -------------------------------------------------------------------------------------------*/
int main() {
    
    int year, day;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter the first day of the year " << year << " : ";
    cin >> day;
    ofstream outputfile;
    string name = "Q4 - Calendar of " + to_string(year) + ".txt";
    outputfile.open(name);
    
    for (int i = 0; i < 12; i++) {
        get_title(get_month(i), year, outputfile);
        get_table(day, days_of_month(i, year), outputfile);
    }
    
    outputfile.close();
    return 0;
}

/*----------------Function name: get_month()----------------------------------------
 Return type: string
 Description: convert the number represent for month to the corresponding month
 Parameters: int month
 Algorithm: use switch - case structure to determine the month -----------------*/
//-----------------------------------------------------------------------------------
string get_month(int m) {
    string month;
    switch(m) {
        case 0: month = "January";
            break;
        case 1: month = "February";
            break;
        case 2: month = "March";
            break;
        case 3: month = "April";
            break;
        case 4: month = "May";
            break;
        case 5: month = "June";
            break;
        case 6: month = "July";
            break;
        case 7: month = "August";
            break;
        case 8: month = "September";
            break;
        case 9: month = "October";
            break;
        case 10: month = "November";
            break;
        default: month = "December";
            break;
    }
    return month;
}

/*-----------------Function name: days_of_month(int, int)------------------------------------
 Return type: integer
 Description: determine the number of days in a month (ie: Jan has 31 days, April has 30 days...)
 Parameters: int month, int year
 Algorithm: use switch - case structure to determine the days of a month --------*/
//------------------------------------------------------------------------------------------

int days_of_month(int month, int year) {
    bool leap_year = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    int day;
    switch(month){
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            day = 31;
            break;
        case 1:
            day = leap_year ? 29 : 28;
            break;
        default:
            day = 30;
            break;
    }
    return day;
}

/*------------------Function name: get_title(string, int, ofstream&)--------------------------------
 Return type: void
 Description: Create the title for the month and write it to the file
 Parameters: string month, int year, ofstream& output_file
 Algorithm:  setw(31) << "month year" << endl ----> output_file;
             "     -------------------------" << endl ----> output_file;
             "setw Sun setw Mon setw Tue setw Wed setw Thurs setw Fri setw Sat" ------> output_file;
 ---------------------------------------------------------------------------------------------------*/
void get_title(string month, int year, ofstream& op) {
    op << setw(31) << month << " " << year << endl;
    op << "     " << "---------------------------------------------------" << endl;
    op << setw(8) << "Sun" << setw(8) << "Mon" << setw(8) << "Tue" << setw(8) << "Wed" << setw(8) << "Thu" << setw(8) << "Fri" << setw(8) << "Sat" << endl;
}

/*------------------Function name: get_table(int, int, ofstream&)--------------------------------
 Return type: void
 Description: Create the table of the days of the month
 Parameters: int& day(Mon, Tue...), int days_of_month, ofstream& output_file
 Algorithm:  print "space" from Sunday to "day" (ie. day is Wed so print " " from Sunday to Wednesday):
                        for (i from 0 to day) : "      " -------> output_file;
             print the number from 1 to days_of_month under the corresponding day, if encounter Saturday
                        go to new line
             for (i from 1 to days_of_month):
                if day is Saturday
                    i << endl -----------> output_file;
                else
                    i -------------------> output_file;
                update day: day = (day + 1) % 7
 ---------------------------------------------------------------------------------------------------*/

void get_table(int& day, int lastday, ofstream& op) {
    for (int j = 0; j < day; j++){
        op << "        ";
    }
    
    for (int k = 1; k <= lastday; k++){
        if (day == 6)
            op << setw(8) << k << endl;
        else
            op << setw(8) << k;
        day = (day + 1) % 7;
    }
    
    op << endl << endl;

}
