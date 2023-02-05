
#include "Matrix.h"
#include <cmath>
#include <iomanip>

using namespace std;

//====================Default constructor==============
//Initialize the matrix with one element
//=====================================================
Matrix::Matrix() {
    row = 1;
    col = 1;
    elements[0][0] = 0;
}

//====================Constructor======================
//Initialize the matrix whose elements are 0
//=====================================================
Matrix::Matrix(int r, int c) {
    row = r;
    col = c;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            elements[i][j] = 0;
}

//==================Overloaded Operator: == ============
//Compare each element of both matrix
//Return true of each element equal to its corresponding
//======================================================
bool Matrix::operator==(Matrix &m) const {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (elements[i][j] != m.elements[i][j])
                return false;
    return true;
}

//==================Function : add ===================
//add two matrix and return the result (a new matrix)
//====================================================
Matrix Matrix::add(Matrix &m) const {
    Matrix result(row, col);
    for(int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            result.elements[i][j] = elements[i][j] + m.elements[i][j];
    return result;
}

//==================Function : power ================
void Matrix::power(int n) {
    for(int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            elements[i][j] = pow(elements[i][j], n);
}

//=====================================================
//=========Non-member functions========================
//=====================================================

//==================Overloaded Operator : >> ==========
//Put each number entered by user into the matrix
//=====================================================
istream &operator>>(istream &in, Matrix &m) {
    for (int i = 0; i < m.row; i++)
        for (int j = 0; j < m.col; j++)
            in >> m.elements[i][j];
    return in;
}

//==================Overloaded Operator : << ==========
//Put each element of the matrix into output stream
//=====================================================
ostream &operator<<(ostream &out, const Matrix &m) {
    for (int i = 0; i < m.row; i++)
        for (int j = 0; j < m.col; j++)
            if (j + 1 == m.col) //The last element of a column
                out << left << setw(3) << m.elements[i][j] << endl;
            else
                out << left << setw(3) << m.elements[i][j] << " ";
    return out;
}



