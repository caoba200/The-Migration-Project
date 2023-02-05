//=======================================
//Derived class: Rectangle
//Derived from PlaneFigure
//Used to calculate perimeter and area of a rectangle
//Attributes: height, width: double - represent heigt and width of a rectangle
//Function members:constructors, destructor, setSide(double, double): void, perimeter(): double, area(): double
//=======================================

#ifndef Rectangle_h
#define Rectangle_h

#include "PlaneFigure.h"
class Rectangle: public PlaneFigure {
public:
    Rectangle(); //Default constructor
    Rectangle(double, double); //Overloaded constructor
    
    
    //Function member: setSides(double, double): void
    //Set up the width and height of the rectangle object
    //assign all the sides to 0 if one of them < 0
    void setSides(double, double);
    
    //Function member: perimeter(): double
    //Calculate perimemter of the rectangle object
    virtual double perimeter() override;
    
    //Function member: area(): double
    //Calculate area of the rectangle object
    virtual double area() override;

private:
    double width, height;
};

#endif /* Rectangle_hpp */
