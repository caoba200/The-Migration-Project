
#include <iostream>
#include "TicTacToe.h"

using namespace std;

//=============== Contructor ===================
TicTacToe::TicTacToe() {
    for(int i = 0; i < ROW; i++)
        for (int j = 0 ; j < COL; j++)
            table[i][j] = 0;
    numOfMove = 0;
}

//=============== Function : Display =============
//Display the table in form that user can understand
//================================================
void TicTacToe::display() const{
    for (int i = 0; i < ROW; i++)
        for(int j = 0; j < COL; j++)
            cout << table[i][j] << ((j + 1 ==  COL) ? "\n" : " "); //Break the line if meet the last element of a column
}

//=============== Function : empty ================
//Check if the position is out of range
//Check if the position is empty (the table at the position is 0)
//=================================================
bool TicTacToe::empty(int row, int col) const{
    if (row < 0 || row >= ROW)
        return false;
    if (col < 0 || col >= COL)
        return false;
    if (table[row][col] != 0)
        return false;
    return true;
}

//=============== Function : outOfRange ===========
//Check if the position is out of range
//=================================================
bool TicTacToe::outOfRange(int row, int col){
    return !(row >= 0 && row < ROW && col >= 0 && col < COL);
}

//================ Function: update ===============
//assign the move to the corresponding position of the table
//update the number of move
//=================================================
void TicTacToe::update(int row, int col, int move) {
        table[row][col] = move;
        numOfMove++;
}

//================ Function : endGame ==============
//Determine if the game finishes by
//either check if the condition of winnning is satisfy
//==================================================
bool TicTacToe::endGame() const {
    for (int i = 0; i < ROW; i++)
        //check elements in the same column
        if (table[i][0] == table[i][1] && table[i][0] == table[i][2] && table[i][0] != 0)
            return true;
    for (int i = 0; i < COL; i++)
        //check elements in the same row
        if (table[0][i] == table[1][i] && table[0][i] == table[2][i] && table[0][i] != 0)
            return true;
    //check elements in the diagonals
    if (table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[0][0] != 0)
        return true;
    if (table[2][0] == table[1][1] && table[1][1] == table[0][2] && table[2][0] != 0)
        return true;
    return false;
}

//===========================================================
//===============Non-member Functions========================
//===========================================================


//================= Function : gamePlay =====================
//game interface
//return the number of the winner (0 if it is a draw game)
//==========================================================
int gamePlay(int playing, TicTacToe &game) {
    int row, col;
    //Ask user when the game is not end
    while(!game.endGame()) {
        cout << "Player" << playing << " move: ";
        cin >> row >> col;
        
        //Catch the exception : out of range
        while(game.outOfRange(row - 1 , col - 1)) {
            cout << "Out of range!! Please try again: ";
            cin >> row >> col;
        }
        
        //Check if the position is empty
        while(!game.empty(row - 1, col - 1)) {
            cout << row << " " << col << " is used. Please choose another move: ";
            cin >> row >> col;
        }
        
        //Update and display the table
        game.update(row - 1, col - 1, playing);
        game.display();
        cout << endl;
        
        //Change turn
        if (!game.endGame())
            swapPlayer(playing);
        
        //Return draw in case out of move (handled the rare case which is the last move bring victory)
        if(!game.endGame() && game.numOfMove == ROW * COL)
            return 0;
    }
    
    //Return the winner
    return playing;
}


//================== Function : swapPlayer ===============
//change from player 1 to player 2 or vice versa
//========================================================
void swapPlayer(int &player) {
    if (player == 1)
        player = 2;
    else
        player = 1;
}

//================== Function: message ==================
//announce user the winner or the game is draw
//=======================================================
void message(int player){
    if (player == 0)
        cout << "Draw!!!!!!!!!!!!" << endl;
    else
        cout << "Player" << player << " wins!" << endl;
}
