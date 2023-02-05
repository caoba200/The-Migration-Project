/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #4
 
 // Program name: Matrix
 // Date : March 2, 2017
 **************************************************/

#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    
    int row, col;
    
    cout << "Enter the number of rows: ";
    cin >> row;
    
    cout << "Enter the number of columns: ";
    cin >> col;
    
    cout << endl;
    
    //Initialize two matrices with row and col
    Matrix m1(row, col);
    Matrix m2(row, col);
    
    //Input the date for two matrices
    cout << "Enter the elements of matrix 1 row by row: " << endl;
    cin >> m1;
    cout << endl;
    
    cout << "Enter the elements of matrix 2 row by row: " << endl;
    cin >> m2;
    cout << endl;
    
    //Compare two matrices
    cout << "matrix 1 == matrix 2?" << endl;
    cout << ((m1 == m2) ? "Yes" : "No") << endl;
    cout << endl;
    
    //Add two matrices
    cout << "matrix 1 + matrix 2: " << endl;
    cout << m1.add(m2) << endl;
    
    //Power the first matrix
    int n;
    cout << "matrix 1 power n. Enter n: ";
    cin >> n;
    m1.power(n);
    cout << m1 << endl;
    
    return 0;
}
