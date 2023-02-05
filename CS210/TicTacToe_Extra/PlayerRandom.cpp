
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
//randomMove(Board&) : bool -- move to a random available location
//===========================================================
bool PlayerRandom::randomMove(Board& board) {
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

//===========================================================
//move(Board&) : override virtual bool -- overrided from Player
//        to simulate the move from computer
//===========================================================

bool PlayerRandom::move(Board& board) {
    //If the board is empty, create a random mvoe
    if(board.empty())
        randomMove(board);
    else {
        int win[3]; //temporary array that store a row, col, or cross line of the board
        position temp; //temporary array that store the position
        int emptyPoint = 0; //store the index
        
        //Scan horizontally
        for(int i = 0; i < 3; i++) {
            //store each row to win
            for(int j = 0; j < 3; j++) {
                temp.row = i;
                temp.col = j;
                win[j] = board.getValue(temp);
                //mark the position where there is no symbol
                if(win[j] == 0)
                    emptyPoint = j;
            }
            //if the opponent can win in the next move on this row
            if(scan(win)) {
                temp.row = i;
                temp.col = emptyPoint;
                //set the symbol at the empty position to block the chance of the opponent to win
                board.update(temp, getSymbol());
                board.display(); //display the board
                return true; //stop the move
            }
        }
        
        //Scan vertically
        for(int i = 0; i < 3; i++) {
            //store each column to win
            for(int j = 0; j < 3; j++) {
                temp.row = j;
                temp.col = i;
                win[j] = board.getValue(temp);
                //mark the position where there is no symbol
                if(win[j] == 0)
                    emptyPoint = j;
            }
            //if the opponent can win from this column
            if(scan(win)) {
                temp.row = emptyPoint;
                temp.col = i;
                //set the position to the empty position to block the chance to win
                board.update(temp, getSymbol());
                board.display();
                return true; //stop the move
            }
        }
        
        //Scan diagonally
        //store the first diagonal line to win
        for(int i = 0; i < 3; i++) {
            temp.row = i;
            temp.col = i;
            win[i] = board.getValue(temp);
            //save the empty location
            if(win[i] == 0)
                emptyPoint = i;
            //if the opponent can win
            if(scan(win)) {
                temp.row = emptyPoint;
                temp.col = emptyPoint;
                //set the symbol to the empty location to block the chance to win
                board.update(temp, getSymbol());
                board.display();
                return true; //stop the move
            }
        }
        
        //scan the second diagonal line
        for(int i = 0; i < 3; i++) {
            temp.row = i;
            temp.col = 2 - i;
            win[i] = board.getValue(temp);
            //save the empty location
            if(win[i] == 0)
                emptyPoint = i;
            //if the opponent can win
            if(scan(win)) {
                temp.row = emptyPoint;
                temp.col = 2 - emptyPoint;
                //set the symbol to the empty locatition to block it
                board.update(temp, getSymbol());
                board.display();
                return true; //stop the move
            }
        }
        //if the opponent can not win in the next move, create a random move
        randomMove(board);
    }
    return true;
}

//===========================================================
//scan(int[]) : bool -- scan the board to find the potential position which
//      can bring victory to the opponent if he moves there
//===========================================================
bool PlayerRandom::scan(int array[]) {
    int count = 0;
    int count2 = 0;
    for(int i = 0; i < 3; i++) {
        //count the opponent's symbol
        if (array[i] != 0 && array[i] != this->getSymbol())
            count++;
        //count the empty location
        if (array[i] == 0)
            count2++;
    }
    //if there are 2 opponent's symbol and one empty location, this is a threat
    return count == 2 && count2 == 1;
}
