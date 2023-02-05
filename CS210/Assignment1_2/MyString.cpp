//=====================================================
//   Class MyString Implementation
//=====================================================
#include "MyString.h"
#include <iostream>

//=====================================================
//   CONSTRUCTORS
//=====================================================

//Default constructor -- create an empty string
//set pData to NULL and length to 0
MyString::MyString() {
    pData = NULL;
    length = 0;
}

//Overloaded constructor -- create a string whose data is a copy of cString
MyString::MyString(char* cString) {
    //allocate memory for pData base on the length of cString
    //add a spot for the terminated character '\0'
    pData = new char[findLength(cString) + 1];
    length = 0;
    int index = 0;
    
    //while the end of the cString is not encountered
    while(*cString != '\0') {
        //assign the value pointed by cString to the corresponding position in pData
        pData[index] = *cString;
        cString++; //move cString forward
        index++; //move the index of pData forward;
        length++; //add 1 to the length of the object
    }
    
    pData[index] = '\0'; // assign the value in the last position in pData to null character
}

//Override default copy constructor -- create a string whose data is a copy of the object s
MyString::MyString(MyString const& s) {
    length = s.length; // assign the length of s to length
    //allocate memory for pData base on the length of s (add a spot for null character)
    pData = new char[s.length + 1];
    //assign each character in s to the corresponding position in pData
    for(int i = 0; i < s.length; i++)
        pData[i] = s.pData[i];
    
    pData[length] = '\0'; // assign the last character in pData to null character
}

//==========================================================
//      DESTRUCTOR
//==========================================================
//Destructor -- free space allocated by constructor and set pData to NULL
MyString::~MyString() {

    if(pData != NULL) {
        delete[] pData;
    }
    pData = NULL;
}

//==========================================================
//     OPERATOR OVERLOADING FUNCTIONS
//==========================================================
//operator overloading = -- if pData is NULL, allocate new memory and copy the value of
// s to it, otherwise, change the data of pData to the data of s (create a copy)
MyString MyString::operator=(MyString const& s) {
    
    //if pData is not NULL, free the memory occupied by it and set pData to NULL
    if(pData != NULL) {
        delete [] pData;
        pData = NULL;
    }
    
    
    pData = s.pData;
    length = s.length; //change the length to the length of s
    
//    //assign each character in s to the corresponding position in pData
//    for(int i = 0; i < s.length; i++) {
//        pData[i] = s.pData[i];
//    }
//    //assign the last character in pData to null character
//    pData[length] = '\0';
    
    return *this;
}

//operator overloading + -- return an object whose data is the concatenation fo the 2 objects
MyString MyString::operator+(MyString const& s) {
    MyString result;
    //allocate new memory for the object based on the length of the 2 objects
    //add 1 for null character
    result.pData = new char[length + s.length + 1];
    //set up the length of result
    result.length = length + s.length;
    
    //assign each character in the left operand to the corresponding position in result
    for(int i = 0; i < length; i++) {
        result.pData[i] = pData[i];
    }
    
    //assign each character in the right operand to the corresponding position in result
    int index = 0;
    for(int i = length; i < length + s.length; i++) {
        result.pData[i] = s.pData[index];
        index++;
    }
    
    //assign the last character in result to null character
    result.pData[length + s.length] = '\0';
    
    return result;
}

//Private member function findLength(char*) : int -- return the length of the cString used as the parameter of the function
int MyString::findLength(char* s) {
    int count = 0;
    while(*s != '\0') {
        count++;
        s++;
    }
    return count;
}

//===========================================================
//     OBSERVERS
//===========================================================
//Function Put() : void -- Display the string
void MyString::Put() {
    std::cout << pData << std::endl;
}

//Function getLength() : int -- return the length of the string
int MyString::getLength() {
    return length;
}

//============================================================
//    MODIFIER
//============================================================
//Function Reverse() : void -- reverse the string
void MyString::Reverse(){
    //find the middle position
    int middle = length / 2;
    //swap the elements in the first half of the string to the corresponding second half
    for (int i = 0; i < middle; i++) {
        char temp = pData[i];
        pData[i] = pData[length - 1 - i];
        pData[length - 1 - i] = temp;
    }
}

//Function Reverse() : void -- set a MyString object back to null
void MyString::Clear() {
    pData = NULL;
    length = 0;
}
