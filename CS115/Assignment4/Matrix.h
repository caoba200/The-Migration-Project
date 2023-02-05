
#ifndef Matrix_h
#define Matrix_h

#include <iostream>

using namespace std;

class Matrix {
public:
    Matrix();   //Default constructor
    Matrix(int, int);   //Constructor with specified row and column
    Matrix add(Matrix &) const;
    void power(int n);
    
    //Overloaded operator as member functions
    bool operator==(Matrix&) const;
    
    //Overloaded operator as non-member functions
    friend istream& operator>>(istream &in, Matrix &m);
    friend ostream& operator<<(ostream &out, const Matrix &m);
private:
    int elements[10][10]; //Capability of the matrix
    int row;
    int col;
};

#endif
