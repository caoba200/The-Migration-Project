
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
    
    //===========================================================
    //randomMove(Board&) : bool -- move to a random available location
    //===========================================================
    bool randomMove(Board&);
    
    //===========================================================
    //scan(int[]) : bool -- scan the board to find the potential position which
    //      can bring victory to the opponent if he moves there
    //===========================================================
    bool scan(int[]);
};

#endif
