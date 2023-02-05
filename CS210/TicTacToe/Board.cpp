#include <iostream>
#include "Board.h"

using namespace std;

//=================================================================
// Class Board Implementation
//=================================================================

//Default constructor
Board::Board() {
    //initialize each element of the board to 0 (no symbol was placed)
    for(int i = 0; i < ROW; i++)
        for(int j = 0; j < COL; j++)
            playBoard[i][j] = 0;
    numberOfMove = 0; //initialize the number of move to 0
}

//Destructor
Board::~Board() {
    
}

//=============================================
//display() : void -- display the board to user
//=============================================
void Board::display() {
    cout << "+---+---+---+" << endl;
    
    //Go through each element of the board
    for (int i = 0; i < ROW; i++) {
        cout << "|";
        for(int j = 0; j < COL; j++) {
            if(playBoard[i][j] == 1) //display "X" if the value is 1
                cout << " X |";
            else if(playBoard[i][j] == 2) //display "O" is the value is 2
                cout << " O |";
            else                  //display nothing (space) if the value is 0
                cout << "   |";
        }
        cout << endl;
        cout << "+---+---+---+" << endl;
    }
}

//======================================================================
//update(position, int) : bool -- update the board by putting player's
//      symbol (second parameter) to the specific position on the board
//      (first parameter)
//======================================================================
bool Board::update(position pos, int value) {
    if(available(pos)) { //if the position is available
        playBoard[pos.row][pos.col] = value; //update the value
        numberOfMove++; //keep track the number of moves
        return true;
    }
    
    return false;
}

//======================================================================
//empty() : bool -- check if the board is empty (nothing is placed on it)
//======================================================================
bool Board::empty() {
    //instead of go through every element, just need to check if number of move is 0
    return numberOfMove == 0;
}

//======================================================================
//available(position) : bool -- check if the position (1st parameter)
//       is occupied (a symbol has been placed)
//======================================================================
bool Board::available(position pos) {
    //check if the value of that position is 0
    return playBoard[pos.row][pos.col] == 0;
}

//======================================================================
//win(int&) : bool -- determine if someone wins and save the winner to
//         the parameter (return true). Otherwise return false
//======================================================================
bool Board::win(int& winner) {
    //Win by matching vertically
    for (int i = 0; i < ROW; i++){
        if(playBoard[i][0] == playBoard[i][1] && playBoard[i][1] == playBoard[i][2] && playBoard[i][0] != 0) {
            winner = playBoard[i][0];
            return true;
        }
    } //end of win by matching vertically
    
    //Win by matching horizontally
    for(int i = 0; i < COL; i++) {
        if(playBoard[0][i] == playBoard[1][i] && playBoard[1][i] == playBoard[2][i] && playBoard[0][i] != 0) {
            winner = playBoard[0][i];
            return true;
        }
    }  //end of win by matching horizontally
    
    //Win by matching cross lines
    if (playBoard[0][0] == playBoard[1][1] && playBoard[1][1] == playBoard[2][2] && playBoard[0][0] != 0) {
        winner = playBoard[0][0];
        return true;
    }
    
    if (playBoard[2][0] == playBoard[1][1] && playBoard[1][1] == playBoard[0][2] && playBoard[2][0] != 0) {
        winner = playBoard[2][0];
        return true;
    } //end of win by matching cross lines
    
    return false; //couldn't find the winner
}

//======================================================================
//result() : int -- return the value based on the current game state :
//       return 0 -- the game is not over ---> continue to play
//       return 1 or 2 -- the game is over and one player wins
//       return 3 -- the game is over and no one wins - tie game
//======================================================================
int Board::result() {
    int winner = 0; //The game is not over.
    if(win(winner)) {
        return winner; //There is a winner
    }
    else
        if(numberOfMove == 9) //the board is filled (the number of moves reaches maximum)
            winner = 3; //The game is over. Tie game
        
    return winner;
}
