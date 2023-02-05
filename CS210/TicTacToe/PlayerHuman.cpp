#include <iostream>
#include "PlayerHuman.h"

using namespace std;

//Constructor -- set position to undefined
PlayerHuman::PlayerHuman() {
    pos.row = -1;
    pos.col = -1;
}

//Overloaded constructor -- set position to undefined and set
//    the symbol based on its parameter.
PlayerHuman::PlayerHuman(int symbol) {
    setSymbol(symbol);
    pos.row = -1;
    pos.col = -1;
}

//Destructor
PlayerHuman::~PlayerHuman(){
    
}

//============================================================
// inputHandling() : void -- a private function member which is
//       used to handle input's format from user.
//============================================================
void PlayerHuman::inputHandling() {
    int row, col;
    //=============== Ask user enter position ===================
    cout << "Enter row: ";
    cin >> row;
    
    //Check if user enter the right format (an integer from 0 to 2)
    while(cin.fail() || row < 0 || row > 2) {
        cout << "Error Format !!! Please enter only integer from 0 to 2." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter row: ";
        cin >> row;
    }
    
    cout << "Enter column: ";
    cin >> col;
    
    //Check if user enter the right format (an integer from 0 to 2)
    while(cin.fail() || col < 0 || col > 2) {
        cout << "Error Format !!! Please enter only integer from 0 to 2." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter column: ";
        cin >> col;
    }
    //=============== End of asking user enter position ===============
    //Handle the data user just entered
    pos.row = row;
    pos.col = col;
}

//===========================================================
// move(Board&) : override virtual bool -- override from Player
//       to simulate the move from user
//===========================================================
bool PlayerHuman::move(Board& board) {
    //Handle the inputs from uesr
    inputHandling();
    
    //update the board, if the position if filled, ask user again
    while(!board.update(pos, getSymbol())) {
        cout << "The position you chose is filled. Please choose a different position.";
        cout << endl;
        inputHandling();
    }
    //Display the board
    board.display();
    return true;
}
