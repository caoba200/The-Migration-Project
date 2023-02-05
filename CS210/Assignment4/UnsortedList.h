
#ifndef UnsortedList_h
#define UnsortedList_h

//Maximum size allowed for the array
int const MAX_SIZE = 10;

class UnsortedList {
public:
    //****************************************
    //Constructor: Initialize the list
    //Pre: Uninitialized list
    //Post: List is initialized with all element = 0 and length = 0
    //*****************************************
    UnsortedList();
    
    //****************************************
    //Destructor: Just an empty function
    //****************************************
    ~UnsortedList();
    
    //****************************************
    //Function: Determines whether list is full
    //Pre: List has been initialized
    //Post: Function value = (list is full)
    //****************************************
    bool IsFull() const;
    
    //****************************************
    //Function: Determines the number of elements in list
    //Pre: List has been initialized
    //Post: Function value = number of elements in list
    //****************************************
    int lengthIs() const;
    
    //****************************************
    //Function: Retrieves list element whose key matches item's key(if present)
    //Pre: List has been initialzed
    //Post: If there is an element someItem whose key matches itemm's key, then return true and item is a copy of someItem
    //; otherwise, return false and item is unchanged.
    //List is unchanged
    //*****************************************
    int RetrieveItem(int key);
    
    //*****************************************
    //Function: Adds item to list
    //Pre: List has been initialized.
    //List is not full. item is not in list
    //Post: item is in list
    //******************************************
    void InsertItem(int item);
    
    //******************************************
    //Function: Calculate sum of items
    //Pre: List has been initialized and not empty
    //Post: sum of elements in the list
    //******************************************
    int Sum() const;
    
    //******************************************
    //Function: Clear the list
    //Pre: List has been initialized
    //Post: empty list with length is 0
    //******************************************
    void Clear();
private:
    int list[MAX_SIZE];
    int length;
};

#endif
