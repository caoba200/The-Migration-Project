//Class Triangle implementation

#include "Triangle.h"
#include <cmath>

//Default constructor
//Used to set 3 sides to the value of 0
Triangle::Triangle() : side1(0), side2(0), side3(0) {
    
}

//Overloaded constructor
//Used to set 3 sides to the values specified by function's parameters
Triangle::Triangle(double s1, double s2, double s3) {
    setSide(s1, s2, s3);
}

//Function member: setSide(double, double, double) : void
//Used to set up the values of the triangle object's sides
//assign all the size to 0 if one of them <= 0
void Triangle::setSide(double s1, double s2, double s3) {
    if(s1 <= 0 || s2 <=0 || s3 <= 0) {
        side1 = 0;
        side2 = 0;
        side3 = 0;
    }
    else {
        side1 = s1;
        side2 = s2;
        side3 = s3;
    }
}

//Function member: perimeter() : double
//Used to calculate the perimeter of the triangle object
double Triangle::perimeter() {
    return side1 + side2 + side3;
}

//Function member: area() : double
//Used to calculate the area of the triangle object
double Triangle::area() {
    double s = (side1 + side2 + side3) / 2;
    return sqrt(s * (s - side1) * (s - side2) * (s - side3));
}
