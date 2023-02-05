//=======================================
//Derived class: Square
//Derived from PlaneFigure
//Used to calculate perimeter and area of a square
//Attributes: side: double - represent the side of a square object
//Function members:constructors, destructor, setSide(double): void, perimeter(): double, area(): double
//=======================================

#ifndef Square_h
#define Square_h

#include "PlaneFigure.h"

class Square : public PlaneFigure {
public:
    Square(); //Default constructor
    Square(double); //Overloaded constructor
    
    //Function member: setSide(double) : void
    //Used to set up the value of the side
    //assign the side to 0 if the value is < 0
    void setSide(double);
    
    //Function member: perimeter() : double
    //Used to calculate the perimeter of the square object
    virtual double perimeter() override;
    
    //Function member: area() : double
    //Used to calculate the area of the square object
    virtual double area() override;
    
private:
    double side;
};

#endif /* Square_hpp */
