#ifndef Board_h
#define Board_h

const int ROW = 3; //Maximum of row
const int COL = 3; //Maximum of column

//=============================================================================
//position : struct -- is used to store the location based on row and col
//=============================================================================
struct position {
    int row;
    int col;
};

//=============================================================================
//Class Board : Defines a 3x3 grid board
//Attributes: playBoard : int[3][3], numberOfMove : int
//Function members : constructor, destructor, display() : void,
//    update(position, int) : bool, empty() : bool, available(position) : bool,
//    win(int&): bool, result() : int
//=============================================================================
class Board {
public:
    Board(); //Default constructor
    ~Board(); //Destructor
    
    //=============================================
    //display() : void -- display the board to user
    //=============================================
    void display();
    
    //======================================================================
    //update(position, int) : bool -- update the board by putting player's
    //      symbol (second parameter) to the specific position on the board
    //      (first parameter)
    //======================================================================
    bool update(position, int);
    
    //======================================================================
    //empty() : bool -- check if the board is empty (nothing is placed on it)
    //======================================================================
    bool empty();
    
    //======================================================================
    //available(position) : bool -- check if the position (1st parameter)
    //       is occupied (a symbol has been placed)
    //======================================================================
    bool available(position);
    
    //======================================================================
    //win(int&) : bool -- determine if someone wins and save the winner to
    //         the parameter (return true). Otherwise return false
    //======================================================================
    bool win(int&);
    
    //======================================================================
    //result() : int -- return the value based on the current game state :
    //       return 0 -- the game is not over ---> continue to play
    //       return 1 or 2 -- the game is over and one player wins
    //       return 3 -- the game is over and no one wins - tie game
    //======================================================================
    int result();
    
    //======================================================================
    //clear() : void -- used to clear the board at a specific position
    //======================================================================
    void clear(position);
    
    //======================================================================
    //getPos() : position -- return the current position which is stored after
    //           the board get updated
    //======================================================================
    position getPos() {
        return currPos;
    }
    
    //======================================================================
    //getValue(position) : int -- return the value in a particular position
    //======================================================================
    int getValue(position pos) {
        return playBoard[pos.row][pos.col];
    }
    
    //======================================================================
    //decreaseNumberOfMove() : void -- decrease the number of move, used when
    //             player chooses undo his move
    //======================================================================
    void decreaseNumberOfMove() {
        numberOfMove--;
    }
private:
    //======================================================================
    //playBoard : int[3][3] -- store the board's state, when initialize, the
    //     board is empty and all the value is set to 0, if the value of an
    //     element is 1 --> symbol "X" is placed at the corresponding position
    //     on the board, if the value is 2 --> symbol "O" is placed.
    //======================================================================
    int playBoard[ROW][COL];
    
    //======================================================================
    //numberOfMove : int -- save the number of moves --> make it easy to
    //     figure out if the board is full (instead of using nested loop)
    //======================================================================
    int numberOfMove;
    
    position currPos; //save the current after the board get update
};

#endif
