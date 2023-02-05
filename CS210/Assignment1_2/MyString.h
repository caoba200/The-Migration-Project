//=======================================
//Class MyString
//Used to define and implement string class
//Attributes: pData : char*, length : int
//Function members:constructors, destructor, operator=(MyString const&) : MyString, operator+(MyString const& s) : MyString
//=======================================

#ifndef MyString_h
#define MyString_h

class MyString {
private:
    char* pData; //pointer to simple C-style string
    int length; //length of the string
    
    //Function findLength(char*) : int -- return the length of the cString s
    int findLength(char* s);
    
public:
    
    //======================================================
    //         CONSTRUCTORS
    //======================================================
    //Default constructor -- create empty string (assign pData to NULL)
    MyString();
    
    //Overloaded constructor -- create a string whose data is a copy of cString
    MyString(char* cString);
    
    //Override default copy constructor -- create a string whose data is a copy of the object s
    MyString(MyString const& s);
    
    //======================================================
    //        DESTRUCTOR
    //======================================================
    ~MyString(); //destructor -- free space allocated by constructor
    
    //======================================================
    //       OPERATOR OVERLOADING FUNCTIONs
    //======================================================
    //operator overloading = -- change the data of the object to a copy of the object s
    MyString operator=(MyString const& s);
    
    //operator overloading + -- return an object whose data is the concatenation of the 2 objects
    MyString operator+(MyString const& s);
    
    //======================================================
    //       OBSERVERS
    //======================================================
    //Function Put() : void -- Display the string
    void Put();
    
    //Function getLength() : int -- return the length of the string
    int getLength();
    
    //======================================================
    //       MODIFIERS
    //======================================================
    //Function Reverse() : void -- reverse the string
    void Reverse();
    
    //Function Clear() : void -- set a MyString object back null
    void Clear();
    
};

#endif
