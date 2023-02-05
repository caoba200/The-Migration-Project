//=======================================
//Derived class: Circle
//Derived from PlaneFigure
//Used to calculate perimeter and area of a circle
//Attributes: radius: double - represent the radius of a circle object
//Function members:constructors, destructor, setDiameter(double): void, perimeter(): double, area(): double
//=======================================
#ifndef Circle_h
#define Circle_h

#include "PlaneFigure.h"
class Circle : public PlaneFigure {
public:
    Circle(); //Default constructor
    Circle(double); //Overloaded constructor
  
    //Function member: setDiameter(double): void
    //Used to set up the value of attribute diameter
    //assign raduis to 0 if the value is less than 0
    void setRadius(double);
    
    //Function member: perimeter(): double
    //Used to calculate the perimeter of the circle object
    virtual double perimeter() override;
    
    //Used to calcuate the area of the circle object
    virtual double area() override;
private:
    double radius;
};

#endif
