/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #4
 
 // Program name: TicTacToe
 // Date : March 2, 2017
 **************************************************/

#include <iostream>
#include "TicTacToe.h"

using namespace std;

int main() {
    
    TicTacToe table;
    
    //Display the initialized table
    table.display();
    cout << endl;
    
    //Game Interface
    int playing = 1;
    int result = gamePlay(playing, table);
    
    message(result);
    
    return 0;
}
