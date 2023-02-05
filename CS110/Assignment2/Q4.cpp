/*********************************************************************
 
 // Student name: Bao D. Cao
 
 // Student number: 200363431
 
 // CS 110 - Assignment2
 
 // Program name: Game: scissor, rock and paper
 
 // Created by Bao D. Cao on 2016-10-11.
 // Copyright © 2016 Bao D. Cao. All rights reserved.
 //
 // Main algorithm: compare the values to determine who win, use switch 
                    structure to assign values to corresponding strings
 
 // Major variables: num, ran_num, computer, you
 
 **********************************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
    
    int num; // value entered by user
    string computer, you; // The string value translated from integer value of computer and user
    
    // Step 1: Create a random number represent to scissor, rock or paper
    srand(time(0));
    
    int ran_num = rand() % 3;
    
    // Step 2: Prompt user enter the value
    cout << "scissor (0), rock (1), paper (2): " ;
    cin >> num;
    
    // Check if the input value is valid
    if (num < 0 || num > 2){
        cout << "Error: The input is invalid!!!" << endl;
        return 1;
    }
    
    // Step 3: Translate the numbers into corresponding strings
    switch (ran_num){
        case 0:
            computer = "scissor";
            break;
        case 1:
            computer = "rock";
            break;
        case 2:
            computer = "paper";
            break;
        default:
            computer = "";
            break;
    }
    
    switch (num) {
        case 0:
            you = "scissor";
            break;
        case 1:
            you = "rock";
            break;
        case 2:
            you = "paper";
            break;
        default:
            you = "";
            break;
    }
    
    // Step 4: Calculate the result of the game
    bool flag = false; // a boolean variable indicate who win (false if computer win)
    
    if (num == ran_num) { // Draw game
        cout << "The computer is " << computer << ". You are " << you << " too. It is a draw" << endl;
        return 0;
    }
    
    // The situation when there are scissor and paper. In this case, who have
    // smaller number will win (scissor-0 beats paper-2)
    else if (num + ran_num == 2) {
        flag = num < ran_num; // flag = true -> user win, otherwise computer win
    }
    
    // In these cases, whoever have bigger number will win (rock-1 beats scissor-0
    // , paper-2 beats rock-1)
    else
        flag = num > ran_num;
    
    // Step 5: Display the result
    if (flag) {
        cout << "The computer is " << computer << ". You are " << you << ". You won" << endl;
    }
    else
        cout << "The computer is " << computer << ". You are " << you << ". You lose" << endl;
    
    
    return 0;
}
