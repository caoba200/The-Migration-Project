
#include "Stack.h"

Stack::Stack() {
    length = 0;
}

Stack::~Stack(){
    
}

bool Stack::push(char item) {
    if(length == 10)
        return false;
    data[length] = item;
    length++;
    return true;
}

bool Stack::pop() {
    //return false if the stack is empty
    if(length == 0)
        return false;
    length--;
    return true;
}

char Stack::top(){
    return data[length - 1];
}

bool Stack::isEmpty() const {
    return length == 0;
}
