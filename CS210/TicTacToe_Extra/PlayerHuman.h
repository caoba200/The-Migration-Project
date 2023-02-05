
#ifndef PlayerHuman_h
#define PlayerHuman_h

#include "Player.h"

//==============================================================
//Class PlayerHuman -- derived from Player. Is used to simulate
//         a player which is controlled by user
//==============================================================
class PlayerHuman : public Player {
public:
    PlayerHuman(); //constructor
    PlayerHuman(int); //overloaded constructor
    ~PlayerHuman(); //destructor
    
    //===========================================================
    // move(Board&) : override virtual bool -- override from Player
    //       to simulate the move from user
    //===========================================================
    virtual bool move(Board&) override;
    
    //===========================================================
    //undo() : bool -- used to determine if player wants to undo
    //         his last move
    //===========================================================
    bool undo();
    
    
private:
    position pos; //store player's position
    
    //============================================================
    // inputHandling() : void -- a private function member which is
    //       used to handle input's format from user.
    //============================================================
    void inputHandling();
};

#endif 
