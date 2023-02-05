
#include "Player.h"

//Constructor
Player::Player() {
    symbol = 0; //the symbol is undefined (not X nor O)
}

//Destructor
Player::~Player() {
    
}

//============================================================
// setSymbol(int) : void -- set up the symbol which will be used
//        by player (1 ==> X, 2 ==> O)
//============================================================
void Player::setSymbol(int s){
    //assign 1 indicates X, 2 indicates O
    symbol = (s == 1 ? s : 2);
}

//============================================================
// getSymbol() : int -- return the symbol used by player
//============================================================
int Player::getSymbol(){
    return symbol;
}
