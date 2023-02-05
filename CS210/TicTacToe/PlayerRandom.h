
#ifndef PlayerRandom_h
#define PlayerRandom_h

#include "Player.h"

//===============================================================
//Class Player Random -- Derived from Player. Is used to simulate
//       a player controlled by computer
//===============================================================
class PlayerRandom : public Player {
public:
    PlayerRandom(); //Constructor
    PlayerRandom(int); //Overloaded constructor
    ~PlayerRandom(); //Destructor
    
    //===========================================================
    //move(Board&) : override virtual bool -- overrided from Player
    //        to simulate the move from computer
    //===========================================================
    virtual bool move(Board&) override;
private:
    position pos; //Store computer player's position
};

#endif
