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

using namespace std;

int main() {
    
    int player; //variable that stores selection from user
    Player *player1; //pointer points to an object that represents player 1
    Player *player2; //pointer points to an object that represents player 2
    Board board;     //an object represent the board where two players perform their moves
    
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
    
    //=============== Game Life Circle =================
    cout << "************ PLAY GAME *********" << endl << endl;
    while (board.result() == 0) { //Check if the game is over (either the board is full or someone wins)
        //Process turn for player 1
        cout << "Player 1's turn: " << endl;
        player1->move(board);
        
        //Break the game life circle if the game finishes after player 1's turn (either tie or player 1 wins)
        if(board.result() != 0)
            break;
        
        cout << endl;
        
        //Process turn for player 2
        cout << "Player 2's turn: " << endl;
        player2->move(board);
        
        cout << endl;
    }
    
    //=================== DISPLAY THE RESULT ====================
    if (board.result() == 1)
        cout << "Player 1 win." << endl;
    else if (board.result() == 2)
        cout << "Player 2 win." << endl;
    else
        cout << "This is a tie game." << endl;
    
    //Free the memory pointed by 2 players
    delete player1;
    delete player2;
    
    return 0;
}
