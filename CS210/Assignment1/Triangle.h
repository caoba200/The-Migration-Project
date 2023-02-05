//=======================================
//Derived class: Square
//Derived from PlaneFigure
//Used to calculate perimeter and area of a square
//Attributes: side: double - represent the side of a square object
//Function members:constructors, destructor, setSide(double): void, perimeter(): double, area(): double
//=======================================

#ifndef Triangle_h
#define Triangle_h

#include "PlaneFigure.h"

class Triangle : public PlaneFigure {
public:
    Triangle(); //Default constructor
    Triangle(double, double, double); //Overloaded constructor
    
    //Function member: setSide(double, double, double) : void
    //Used to set up the values of the triangle object's sides
    //assign all the sides to 0 if one of them <= 0
    void setSide(double, double, double);
    
    //Function member: perimeter() : double
    //Used to calculate the perimeter of the triangle object
    virtual double perimeter() override;
    
    //Function member: area() : double
    //Used to calculate the area of the triangle object
    virtual double area() override;
    
private:
    double side1, side2, side3; //represent 3 sides of a triangle
};

#endif
