
#include "Stack.h"

// Constructor: The vector will have one element (empty string at list[0]) with size = 0
stack::stack() {
    list.resize(0);
    size = 0;
}

// Push a string onto the top of the stack
void stack::push(string data){
    // Increase the size of the vector
    list.resize(size + 1);
    // Add the input string to the end of the vector
    list.push_back(data);
    size++; // Increase size
}

// Remove the string at the top of the stack
string stack::pop(){
    string result = list[size]; // Get the last element of the vector (top of the stack)
    list.resize(size); // Reduce the size of the vector by 1 (remove the last element)
    size--; // Reduce size
    return result; // Return the removed element
}

bool stack::checkEmpty(){
    return size == 0;
}

int stack::getSize(){
    return size;
}

void stack::emptyStack(){
    list.resize(0);
    size = 0;
}

string stack::top(){
    return list[size];
}
