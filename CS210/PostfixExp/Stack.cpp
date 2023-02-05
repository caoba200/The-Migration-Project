
#include "Stack.h"

Stack::Stack() {
    length = 0;
}

Stack::~Stack(){
    
}

//********************************************
// Function : push an item into the stack.
//   return true if push successfully, return
//   false if the stack is full.
//********************************************
bool Stack::push(char item) {
    if(length == 10)
        return false;
    data[length] = item;
    length++;
    return true;
}

//********************************************
// Function : pop an item out of the stack.
//   return true if pop successfully, return
//   false if the stack is empty
//********************************************
bool Stack::pop() {
    //return false if the stack is empty
    if(length == 0)
        return false;
    length--;
    return true;
}

//*******************************************
// Function : return the top of the stack
//*******************************************
char Stack::top(){
    return data[length - 1];
}

//*******************************************
// Function : check if the stack is empty
//*******************************************
bool Stack::isEmpty() const {
    return length == 0;
}
