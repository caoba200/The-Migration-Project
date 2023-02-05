
#include "PositionStack.h"

//constructor
PositionStack::PositionStack() {
    stack = new vector<position>;
}

//destructor
PositionStack::~PositionStack(){
    delete stack;
    stack = NULL;
}

//================================================================
//empty() : bool -- check if the stack is empty
//================================================================
bool PositionStack::empty() {
    //use the vector method empty to check the emptiness
    return stack->empty();
}

//================================================================
//push(position) : bool -- push an element into the stack
//================================================================
bool PositionStack::push(position pos) {
    //use the vector method push_back to perform pushing
    stack->push_back(pos);
    return true;
}

//================================================================
//pop(position&) : bool -- store the top element to the referrenced parameter
//      and then pop that element out of the stack
//================================================================
bool PositionStack::pop(position& pos) {
    //return false if the stack is empty
    if(stack->empty())
        return false;
    else {
        pos = stack->back(); //save the top element
        stack->pop_back(); //pop the top element
    }
    
    return true;
}
