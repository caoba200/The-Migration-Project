
#ifndef Stack_h
#define Stack_h

class Stack {
public:
    Stack(); // Default constructor
    ~Stack(); // Destructor (empty)
    
    bool push(char item);
    
    bool pop();
    
    char top();

    bool isEmpty() const;
private:
    char data[10]; // arary of char with maximum of 10 items
    int length;    // stack's length
};

#endif
