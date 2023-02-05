/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 210 - Assignment #1
 
 // Program name: Customized String Class - Question 2
 
 // Date : September 14, 2017
**************************************************/
#include <iostream>
#include "MyString.h"

using namespace std;

int main() {
    
    //Create 3 MyString objects using different constructors
    MyString str1; //default constructor
    
    char* str = "CS 210 - Assignment 1 "; //there is a space at the and of the string so the length should be 22
    MyString str2(str); //using overloaded constructor
    
    MyString str3(str2); //using overloaded copy constructor
    
    //======= TESTING CONSTRUCTOR ===================
    cout << "========== TESING CONSTRUCTORS ==========" << endl;
    cout << "Length of str1 using default constructor: " << str1.getLength() << endl << endl;
    
    cout << "String str2 using overloaded constructor: " << endl;
    str2.Put();
    cout << "Length of str2: " << str2.getLength() << endl << endl;
    
    cout << "String str3 using overloaded copy constructor: " << endl;
    str3.Put();
    cout << "Length of str3: " << str3.getLength() << endl << endl;
    
    //====== TESING OPERATOR OVERLOADING =============
    cout << "========== TESING OPERATOR OVERLOADING ==========" << endl;
    //assigning to an empty string
    str1 = str2;
    cout << "After assigning the content of str2 to an empty string str1, str1 is: " << endl;
    str1.Put();
    cout << "Length of str1: " << str1.getLength() << endl << endl;
    
    //Assign str1 back to null to avoid 2 pointers point to the same dynamic memory
    str1.Clear();
    
    //assigning to a non-empty string
    MyString str4("This is the original content of str4.");
    cout << "String str4 when initialize: " << endl;
    str4.Put();
    cout << "Length of str4: " << str4.getLength() << endl << endl;
    str4 = str2;
    cout << "After assigning the content of str2 to the non-empty string str4, str4 becomes: " << endl;
    str4.Put();
    cout << "Length of str4: " << str4.getLength() << endl << endl;
    str2.Reverse();
    cout << "Reverse str2: " << endl;
    str2.Put();
    cout << "The content of str4 (shallow copy) when reverse str2: " << endl;
    str4.Put();
    cout << endl << endl;
    
    //Clear the content of str4 to avoid 2 pointers point to the same dynamic memory
    str4.Clear();
    
    //concatenate str3 and temp
    MyString temp("Question 2.");
    str4 = str3 + temp;
    cout << "After concatenating str3 and temp and assign the result to str4, str4 becomes: " << endl;
    str4.Put();
    cout << "Length of str4: " << str4.getLength() << endl << endl;
    
    //Clear the content of str4 to avoid 2 pointers point to the same dynamic memory
    str4.Clear();
    
    //====== TESING MODIFIERS ====================
    cout << "========== TESING MODIFIER ==========" << endl;
    str3.Reverse();
    cout << "After reversing str3, str3 becomes: " << endl;
    str3.Put();
    cout << "Length of str3: " << str3.getLength() << endl << endl;
    
    return 0;
}
