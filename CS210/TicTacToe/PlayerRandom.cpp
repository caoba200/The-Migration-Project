
#include "PlayerRandom.h"
#include <cstdlib>
#include <ctime>

//Constructor -- set position to undefined
PlayerRandom::PlayerRandom() {
    pos.row = -1;
    pos.col = -1;
}

//Overloaded constructor -- set position to undefined and set
//      the symbol based on its parameter
PlayerRandom::PlayerRandom(int symbol) {
    setSymbol(symbol);
    pos.row = -1;
    pos.col = -1;
}

//Destructor
PlayerRandom::~PlayerRandom(){
    
}

//===========================================================
//move(Board&) : override virtual bool -- overrided from Player
//        to simulate the move from computer
//===========================================================
bool PlayerRandom::move(Board& board) {
    //Create a random position
    srand((unsigned)time(0));
    pos.row = rand() % 3;
    pos.col = rand() % 3;
    
    //Check if that position is available, if not, re-random
    while(!board.update(pos, getSymbol())) {
        pos.row = rand() % 3;
        pos.col = rand() % 3;
    }
    //Show the board
    board.display();
    return true;
}
