
#ifndef PositionStack_h
#define PositionStack_h

#include <vector>
#include "Board.h"

using namespace std;
//====================================================================
//Class PositionStack -- store the positions of a player, which is used
//      later to perform undo that player's move
//Attributes : *stack : vector<position>
//Member functions : constructor, destructor, empty() : bool, push(position) : bool,
//      pop(position&) : empty
//====================================================================
class PositionStack {
public:
    PositionStack(); //constructor
    ~PositionStack(); //destructor
    
    //================================================================
    //empty() : bool -- check if the stack is empty
    //================================================================
    bool empty();
    
    //================================================================
    //push(position) : bool -- push an element into the stack
    //================================================================
    bool push(position);
    
    //================================================================
    //pop(position&) : bool -- store the top element to the referrenced parameter
    //      and then pop that element out of the stack
    //================================================================
    bool pop(position&);
private:
    vector<position> *stack; //a vector of position
};

#endif
