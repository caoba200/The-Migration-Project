//Class Rectangle Implementation

#include "Rectangle.h"

//Default constructor
Rectangle::Rectangle() {
    width = 0;
    height = 0;
}

//Overloaded default constructor
Rectangle::Rectangle(double w, double h) {
    setSides(w, h);
}

//Function member: setSides(double, double): void
//Set up the width and height of the rectangle object
//assign all the sides to 0 if one of them < 0
void Rectangle::setSides(double w, double h) {
    if (w < 0 || h < 0) {
        width = 0;
        height = 0;
    }
    else {
        width = w;
        height = h;
    }
}

//Function member: perimeter(): double
//Calculate perimemter of the rectangle object
double Rectangle::perimeter() {
    return width + height;
}

//Function member: area(): double
//Calculate area of the rectangle object
double Rectangle::area() {
    return width * height;
}

