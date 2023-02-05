
#ifndef IndexList_h
#define IndexList_h

#include <iostream>
#include "Employee.h"

using namespace std;

template <class T, int maxSize>
class indexList {
public:
    indexList();
    bool append(const T&); //append an element to the index list
    void selSort(); //selection sort
    void display() const; // display the list
    //friend ostream& operator<< (ostream& os, const indexList<T, maxSize>& list);
private:
    T elements[maxSize]; //Capability
    int size;  //real size
};

#endif
