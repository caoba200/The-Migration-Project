#include <string>
#include <vector>

#ifndef Stack_h
#define Stack_h

using namespace std;

class stack {
private:
    // Vector is used to implement stack
    vector<string> list;
    // the number of element in the stack
    int size;
public:
    // Constructor
    stack();
    // Push a string onto the stack
    void push(string);
    // Pop the string at the top of the stack
    string pop();
    // Retrieve the top of the stack
    string top();
    // Check if the stack is empty
    bool checkEmpty();
    // Return the size of the stack
    int getSize();
    // Empty the stack (delete all elements)
    void emptyStack();
};

#endif
