/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 210 - Assignment #2
 
 // Program name: Tic Tac Toe
 
 // Date : September 28, 2017
**************************************************/
#include <iostream>
#include "Player.h"
#include "PlayerHuman.h"
#include "PlayerRandom.h"
#include "PositionStack.h"

using namespace std;

int main() {
    
    //=============== Declaration ============================
    int player; //variable that stores selection from user
    Player *player1; //pointer points to an object that represents player 1
    Player *player2; //pointer points to an object that represents player 2
    Board board;     //an object represent the board where two players perform their moves
    PositionStack* player1Pos = new PositionStack(); //Position stack for player 1
    PositionStack* player2Pos = new PositionStack(); //Position stack for player 2
    
    //=============== Game Title =============================
    cout << "=======================================" << endl;
    cout << "|            TIC TAC TOE              |" << endl;
    cout << "=======================================" << endl << endl;
    
    //=============== Player Selection Stage =================
    cout << "************ PLAYER SELECTION *********" << endl << endl;
    
    //Choosing the first player
    cout << "Choose the first player: " << endl;
    cout << "Enter 1 if the player is human." << endl;
    cout << "Enter 2 if the player is computer." << endl;
    cin >> player;
    //Handling user's input: show warning message if user enters something which is not a number or a number different than 1 and 2
    while(cin.fail() || (player != 1 && player != 2)) {
        cout << "Your choice is invalid !!! Please choose again." << endl;
        //clear the buffer in case something is still in there
        cin.clear();
        cin.ignore(100,'\n');
        
        cout << "Choose the first player: " << endl;
        cout << "Enter 1 if the player is human." << endl;
        cout << "Enter 2 if the player is computer." << endl;
        cin >> player;
    }
    
    //Depends on user's choice, allocate memory for corresponding player object
    if (player == 1)
        player1 = new PlayerHuman(1);
    else
        player1 = new PlayerRandom(1);
    
    cout << endl;
    
    //Choosing the second player
    cout << "Choose the second player: " << endl;
    cout << "Enter 1 if the player is human." << endl;
    cout << "Enter 2 if the player is computer." << endl;
    cin >> player;
    
    //Handling user's input: show warning message if user enters something which is not a number or a number different than 1 and 2
    while(cin.fail() || (player != 1 && player != 2)) {
        cout << "Your choice is invalid !!! Please choose again." << endl;
        cin.clear();
        cin.ignore(100,'\n');
        
        cout << "Choose the first player: " << endl;
        cout << "Enter 1 if the player is human." << endl;
        cout << "Enter 2 if the player is computer." << endl;
        cin >> player;
    }
    
    //Depends on user's choice, allocate memory for corresponding player object
    if (player == 1)
        player2 = new PlayerHuman(2);
    else
        player2 = new PlayerRandom(2);
    
    cout << endl;
    
    //============================ Game Life Circle =======================================
    cout << "************ PLAY GAME *********" << endl << endl;
    
    position temp;//store current position which is used to handle player's position stack and board
    
    while (board.result() == 0) { //Check if the game is over (either the board is full or someone wins)
        //Process turn for player 1
        cout << "Player 1's turn: " << endl;
        
        while(!player1->move(board)) { //If player 1 wants to undo his move
            //If player 1 wants to undo but the action can not be performed (nothing in the stack)
            if(player1Pos->empty() || player2Pos->empty()) {
                cout << "Can't undo your move !!. Please choose 1 to continue." << endl;
            }
            else {
                player1Pos->pop(temp); //pop player1's stack and store the position in temp
                board.clear(temp);     //clear the board at the position temp
                player2Pos->pop(temp); //pop player2's stack and store the position in temp
                board.clear(temp);     //clear the board at the position temp
                board.display();       //display the board after modifying it
            }
        }
        
        player1Pos->push(board.getPos()); //push player1's position into the stack after the move
        
        //Break the game life circle if the game finishes after player 1's turn (either tie or player 1 wins)
        if(board.result() != 0)
            break;
        
        cout << endl;
        
        //Process turn for player 2
        cout << "Player 2's turn: " << endl;
        
        while(!player2->move(board)) { //If player 2 wants to undo his move
            //If playe 2 wants to undo but the action can not be performed (nothing in the stack)
            if(player1Pos->empty() || player2Pos->empty()) {
                cout << "Can't undo your move !!. Please choose 1 to continue." << endl;
            }
            else {
                player1Pos->pop(temp); //pop player1's stack and store the positio in temp
                board.clear(temp);     //clear the board at the position temp
                player2Pos->pop(temp); //pop player2's stack and store the position in temp
                board.clear(temp);     //clear the board at the position temp
                board.display();       //display the board after modifying it
            }
        }
        
        player2Pos->push(board.getPos()); //push player2's position into the stack
        
        cout << endl;
    }
    
    //=================== DISPLAY THE RESULT ====================
    if (board.result() == 1)
        cout << "Player 1 win." << endl;
    else if (board.result() == 2)
        cout << "Player 2 win." << endl;
    else
        cout << "This is a tie game." << endl;
    
    //Free the memory 
    delete player1;
    delete player2;
    delete player1Pos;
    delete player2Pos;
    
    return 0;
}
