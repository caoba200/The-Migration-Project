#ifndef PlaneFigure_h
#define PlaneFigure_h

//==========================================
//Class: PlaneFigure (base class)
//Provide an interface to calculate perimeter and area of a figure
//==========================================
class PlaneFigure {
public:
    PlaneFigure(); //Default constructor
    virtual ~PlaneFigure(); //abstract destructor
    //pure vitual function: perimeter()
    //derived classes will override this function to calculate perimater
    virtual double perimeter() = 0;
    
    //pure virtual function: area()
    //derived classes will override this function to calculate perimeter
    virtual double area() = 0;
};

#endif
