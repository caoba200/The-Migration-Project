/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #2
 
 // Program name: Hangman Game (Project 10, pg. 559)
 // Date : January 26, 2017
 
 **************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//========================== Hangman : struct ==========================
//word : the word which is read from the external file
//solution : is used to keep track of the solution which is entered by user
//numOfGuess : the max number of tries which is entered by user
//======================================================================
struct Hangman {
    string word;
    string solution;
    int numOfGuess;
};

//========================= initialize : void ==========================
//Read the word from the external file into game.word;
//Prompt user enter the number of tries and read it into game.numOfGuess
//Copy game.word to game.solution (to match their length)
//Replace each character in solution by '*'
//======================================================================
void initialize(ifstream &in, Hangman &game, bool &err) {
    in >> game.word;
    
    if(game.word.empty()) {
        err = true;
        return;
    }
    
    cout << "Enter the max number of tries: ";
    cin >> game.numOfGuess;
    
    game.solution = game.word;
    
    // Replace the solution by a string of '*'
    for (int i = 0; i < game.solution.length(); i++)
        game.solution[i] = '*';
}

//========================= checkDuplicate : bool ======================
//Find the character c in a string a
//THIS FUNCTION CAN BE USED IN 2 WAYS
//1. Check duplication : find c in string game.solution (true if the answer is duplicated)
//2. Check correction : find c in string game.word (true if the answer is correct)
//=======================================================================
bool checkDuplicate(string a, char c) {
    for (int i = 0; i < a.length(); i++)
        if (a[i] == c && c != '*') // '*' is counted as a wrong answer
            return true;
    return false;
}

//======================== guessing : void =============================
//the function which is run in the game life cycle
//game : the struct
//result : check the answer (0 is correct, 1 is duplicate, 2 is wrong)
//c : the character which is entered by user
//ask user for a letter and store it in c
//check the duplication of c in game.solution (if true then update result)
//check the correction of c in game.word (if false then update result)
//otherwise (the answer is right), replace the corresponding letters in game.solution with c, update result
//decrease game.numOfGuess by 1
//=======================================================================
void guessing(Hangman &game, int &result, char &c) {
    cout << "Guess a letter (you have " << game.numOfGuess << " tries left): ";
    cin >> c;
    if (checkDuplicate(game.solution, c)){   // Check the duplication
        result = 1; // Duplicated answer
        game.numOfGuess++; // Duplication will not be counted as an answer
    }
    else if (!checkDuplicate(game.word, c)) // Check the correction
        result = 2; // Wrong answer
    else {
        // Replace each corresponding character in solution by c
        for(int i = 0; i < game.word.length(); i++) {
            if (game.word[i] == c && game.solution[i] == '*')
                game.solution[i] = c;
        }
        result = 0; // Correct answer
    }
    game.numOfGuess--; //Decrease the number of guess by 1
}

//========================= displayResult : void =========================
//display the result base on the state of guessing (the variable result)
//result = 0 ---> Right answer
//result = 1 ---> Duplicate answer
//result = 2 ---> Wrong answer
//========================================================================
void displayResult(const Hangman game, int result, char c) {
    switch (result){
        case 0: // Right answer
            cout << "Right! Word so far: " << game.solution << endl;
            break;
        case 1: // Duplicated answer
            cout << "'" << c << "'" << " has already been used. Try again." << endl;
            break;
        case 2: // Wrong answer
            cout << "Wrong! Try again. Word so far is: " << game.solution << endl;
            break;
    }
}

//=========================== win : bool ==================================
//check if user win the game
//check each character in game.solution
//return false if one of them is '*' (solution hasn't solved yet)
//=========================================================================
bool win(const Hangman game) {
    for (int i = 0; i < game.solution.length(); i++)
        if (game.solution[i] == '*')
            return false;
    return true;
}

int main() {
    // ==================Variable decleration:=====================
    Hangman game;
    ifstream input; // input file stream
    input.open("input.txt");
    
    char guessCharacter; // The character user guess
    int gameState;      // State of guessing (right(0), duplicate(1), wrong(2))
    
    bool err = false; // Check if the word is read successfully from the external file
    
    // ==================Initialize the data for the game=========
    initialize(input, game, err);
    
    // Check if there is an error when read the word from the file
    if(err) {
        cerr << "Error: Could not find the word in the external file." << endl;
        input.close();
        return 1;
    }
    
    // ==================The main game life cycle=================
    while(game.numOfGuess > 0) {
        guessing(game, gameState, guessCharacter);
        if (!win(game)) // Only show the guessing result if user hasn't won yet
            displayResult(game, gameState, guessCharacter);
        else // Otherwise, end the life cycle and move to the final result
            break;
    }
    
    // =================Display the final result==================
    if(win(game))
        cout << "You win!" << endl;
    else
        cout << "You lose!" << endl << "The word is: " << game.word << endl;
    
    input.close();
    return 0;
}
