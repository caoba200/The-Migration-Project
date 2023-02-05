
#include "UnsortedList.h"

//****************************************
//Constructor: Initialize the list
//Pre: Uninitialized list
//Post: List is initialized with all element = 0 and length = 0
//*****************************************
UnsortedList::UnsortedList() {
    length = 0;
}

//****************************************
//Destructor: Just an empty function
//****************************************
UnsortedList::~UnsortedList(){
    
}

//****************************************
//Function: Determines whether list is full
//Pre: List has been initialized
//Post: Function value = (list is full)
//****************************************
bool UnsortedList::IsFull() const {
    return length == MAX_SIZE;
}

//****************************************
//Function: Determines the number of elements in list
//Pre: List has been initialized
//Post: Function value = number of elements in list
//****************************************
int UnsortedList::lengthIs() const {
    return length;
}

//****************************************
//Function: Retrieves list element whose key matches item's key(if present)
//Pre: List has been initialzed
//Post: If there is an element someItem whose key matches itemm's key, then return true and item is a copy of someItem
//; otherwise, return false and item is unchanged.
//List is unchanged
//*****************************************
int UnsortedList::RetrieveItem(int key){
    //the key is not in the range of list's index
    if (key < 0 || key >= MAX_SIZE )
        return -1; // not found
    //retrieve the value in the corresponding index
    return list[key];
}

//*****************************************
//Function: Adds item to list
//Pre: List has been initialized.
//List is not full. item is not in list
//Post: item is in list
//******************************************
void UnsortedList::InsertItem(int item) {
    //Insert item to the end of the list
    if(!IsFull() && item != 0) {
        list[length] = item;
        length++; //increase length
    }
}

//******************************************
//Function: Calculate sum of items
//Pre: List has been initialized and not empty
//Post: sum of elements in the list
//******************************************
int UnsortedList::Sum() const{
    //return 0 if the list is empty
    if (length == 0)
        return 0;
    //initialize the sum of element
    int result = 0;
    //accumulate the sum
    for(int i = 0; i < length; i++)
        result += list[i];
    return result;
}

//******************************************
//Function: Clear the list
//Pre: List has been initialized
//Post: empty list with length is 0
//******************************************
void UnsortedList::Clear(){
    length = 0;
}
