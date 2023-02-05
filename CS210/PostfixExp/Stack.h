
#ifndef Stack_h
#define Stack_h

class Stack {
public:
    Stack(); // Default constructor
    ~Stack(); // Destructor (empty)
    
    //********************************************
    // Function : push an item into the stack.
    //   return true if push successfully, return
    //   false if the stack is full.
    //********************************************
    bool push(char item);
    
    //********************************************
    // Function : pop an item out of the stack.
    //   return true if pop successfully, return
    //   false if the stack is empty
    //********************************************
    bool pop();
    
    //*******************************************
    // Function : return the top of the stack
    //*******************************************
    char top();
    
    //*******************************************
    // Function : Check if the stack is empty
    //*******************************************
    bool isEmpty() const;
private:
    char data[10]; // arary of char with maximum of 10 items
    int length;    // stack's length
};

#endif
