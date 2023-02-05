//Class Circle implementation

#include "Circle.h"

#define PI 3.1415926536;

//Default constructor: set radius to default value (0)
Circle::Circle() : radius(0) {
    
}

//Overloaded constructor: set diameter to value of the parameter
Circle::Circle(double d) {
    setRadius(d);
}

//Function member: setDiameter(double): void
//Used to set up the value of attribute diameter
void Circle::setRadius(double d) {
    if (d < 0)
        radius = 0;
    else
        radius = d;
}

//Function member: perimeter(): double
//Used to calculate the perimeter of the circle object
double Circle::perimeter() {
    return radius * 2 * PI;
}

//Function member: area(): double
//Used to calculate the area of the circle object
double Circle::area(){
    return radius * radius * PI;
}
