/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 210 - Assignment #4
 
 // Program name: Sale Record
 
 // Date : October 24, 2017
 **************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "UnsortedList.h"

using namespace std;

//**************************************************
//Function : Save the classes which sold the most cookies into an array
//Pre: an boolean array which is used to save the win classes. It is initialized to false (no one wins)
//Post: the array where the element has the value "true" indicate the winner
//**************************************************
void compare(bool winner[], int &maximum, int key, int data) {
    //If there is a class sold the same amount to maximum, set their position to the array is true (add another winner)
    if(data == maximum && maximum > 0)
        winner[key] = true;
    //If a class sold more than maximum, then set this value to be new maximum, then remove all the previous winner and
    //   update this class as the new winner
    else if (data > maximum) {
        maximum = data;
        for(int i = 0; i < 10; i++)
            winner[i] = false;
        winner[key] = true;
    }
}

int main() {
    
    UnsortedList list[10]; //An array of the unsorted list. Each element represent a class
    
    //two strings which are used to construct the name of input and output files.
    string input = "input";
    string output = "output";
    
    //two file streams which are used to manipulate the input and output files
    ifstream in;
    ofstream out;
    
    int key, data; //store the value of class id and the number of boxes
    
    string temp1; //store the first line in the input file, which will be ignored
    
    bool winner[10]; //array to record the winners
    for(int i = 0; i < 10; i++) //Initialized to false
        winner[i] = false;
    
    int maximum = 0; //The highest number of boxes sold by a class
    
    //Go throught from input file number 1 to input file number 5
    for(int i = 1; i < 6; i++) {
       
        //Open the input file
        in.open(input + to_string(i) + ".txt");
        if(!in) //Check if file cannot be openned (for debugging purpose)
            cout << "The file can not be openned." << endl;
        
        //Open the output file
        out.open(output + to_string(i) + ".txt");
        if(!out) //Check if file cannot be openned (for debugging purpose)
            cout << "The output file cannot be open." << endl;
    
        //skip the first line
        getline(in, temp1);
        
        //Read the data from the input file to the corresponing list (each class is represented by a list)
        while(!in.eof()) {
            in >> key >> data;
            list[key - 1].InsertItem(data);
            key = data = 0; //Reset key and data (somehow the data will be duplicate at the last line of the file so this line is used to avoid it)
        }
        
        //Compute the sum and find the winner
        for(int i = 0; i < 10; i++)
            compare(winner, maximum, i, list[i].Sum());
        
        //Write out the information to the output file
        out << "Class Id \t Number of boxes sold\n"; //Title
        for(int i = 0; i < 10; i++) {
            out << i + 1 << "\t\t" ; //Write the class Id at the first column
            for(int j = 0; j < list[i].lengthIs(); j++)
                out << list[i].RetrieveItem(j) << " "; //Write the numbers of boxes at the next column
            out << "\n";
            out << "\t\tTotal : " << list[i].Sum() << "\n\n"; //Write the total sales in the next row
        }
        
        //Write out the maximum boxes is sold and the classes sold them
        out << "\n*******************************\nWinners: " << maximum << " boxes\n";
        for (int i = 0; i < 10; i++)
            if(winner[i])
                out << "Class " << i + 1 << "\n";
        
        in.close();
        out.close();
        
        //Clear the list for the next input file
        for(int i = 0; i < 10; i++)
            list[i].Clear();
        //Clear the maximum
        maximum = 0;
        //Set the winner array back to false
        for(int i = 0; i < 10; i++) 
            winner[i] = false;
    }
    
    return 0;
}
