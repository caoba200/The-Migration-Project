
#ifndef TicTacToe_h
#define TicTacToe_h

static const int ROW = 3;
static const int COL = 3;

class TicTacToe {
public:
    TicTacToe();
    void display() const; //Display the table for user
    void update(int row, int col, int move); //Update the table based on the move of user
    bool empty(int, int) const; //Check if the position is empty
    
    bool endGame() const; //Check if the game is end (win or draw)
    int numOfMove; //number of moves
    
    bool outOfRange(int, int); //Check if the position is out of range
    
private:
    
    int table[ROW][COL];
};

#endif


//==========Non-member Functions===========

//================= Function : gamePlay =====================
//game interface
//return the number of the winner (0 if it is a draw game)
//==========================================================
int gamePlay(int, TicTacToe&);

//================== Function : swapPlayer ===============
//change from player 1 to player 2 or vice versa
//========================================================
void swapPlayer(int&);

//================== Function: message ==================
//announce user the winner or the game is draw
//=======================================================
void message(int);
