//Class Square implementation

#include "Square.h"

//Default constructor
//Used to set the value of side to 0
Square::Square() : side(0) {
    
}

//Overload constructor
//Used to set the value of side to a customized value (function's parameter)
Square::Square(double s) {
    setSide(s);
}

//Function member: setSide(double) : void
//Used to set up the value of the side
//assign the side to 0 if the value is < 0;
void Square::setSide(double s) {
    if (s < 0)
        side = 0;
    else
        side = s;
}

//Function member: perimeter() : double
//Used to calculate the perimeter of the square object
double Square::perimeter() {
    return side * 4;
}

//Function member: area() : double
//Used to calculate the area of the square object
double Square::area() {
    return side * side;
}

