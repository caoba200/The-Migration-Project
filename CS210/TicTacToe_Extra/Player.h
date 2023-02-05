
#ifndef Player_h
#define Player_h

#include "Board.h"

//================================================================
//Class Player - An abstract class used to provide
//     general information about a player
//Attribute: symbol : int -- store player's symbol (X or O)
//Function members: Contructor, Destructor, setSymbol(int) : void,
//     getSymbol() : int, move(Board&) : pure virtual bool
//================================================================
class Player {
public:
public:
    
    Player(); //Constructor
    virtual ~Player();  //Destructor
    
    //============================================================
    // setSymbol(int) : void -- set up the symbol which will be used
    //        by player (1 ==> X, 2 ==> O)
    //============================================================
    void setSymbol(int);
    
    //============================================================
    // getSymbol() : int -- return the symbol used by player
    //============================================================
    int getSymbol();
    
    //============================================================
    // move(Board&) : pure virtual bool -- provide virtual function
    //        (will be overrided by derived classes) which simulate
    //        player's move.
    //============================================================
    virtual bool move(Board&) = 0;
    
private:
    int symbol; //store the symbol which is used by player
};

#endif
