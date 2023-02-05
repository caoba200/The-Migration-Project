/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 210 - Assignment #1
 
 // Program name: Area and Perimeter of Plane Figures - Question 1
 
 // Date : September 14, 2017
**************************************************/
#include <iostream>
#include "PlaneFigure.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"

using namespace std;


//==============================================================
//        FUNCTON PROTOTYPE
//==============================================================
//Function : startScreen() : void
//Description: this function is used as an user interface to display information and the options for the program
void startScreen();

//Function : optionHandling(int, PlaneFigure*) : void
//Description: this function is used to handle option entered by user and calculate and provide the appropriate result
//Parameter : option : int, object : PlaneFigure*
void optionHandling(int, PlaneFigure*);


//==============================================================
//Function : main() : int
//the algorithm is used in main function:
// 1. Initialize a pointer of the type PlaneFigure and assign to nullptr
// 2. Display the interface (by calling startScreen() and prompt user enter the option)
// 3. If the option is 5, go to step 9
// 4. Based on the option, the pointer is allocated the appropriate amount of memory depends on the derived type
// 5. Based on the derived type, user is promted to enter the corresponding information (sides of the figure)
// 6. Calculate perimeter and area based on the information from step 4
// 7. Display the result to user
// (step 4, 5, 6 and 7 is implemented in the function optionHandling)
// 8. Go back to step 2
// 9. Inform user and exit the program

int main() {
    
    PlaneFigure* figure = NULL;
    int option;
    
    cout << "This program is used to calculate the perimeter and area of plane figures." << endl << endl;
    
    startScreen();
    
    cin >> option;
    
    //Piece of code that is used to handle the situation when user input something which is not an integer
    while(cin.fail()) {
        cout << "ERROR!!!!!! THE INPUT YOU ENTERED IS NOT AN INTEGER. PLEASE TRY AGAIN.";
        cout << endl;
        cin.clear();
        cin.ignore(10, '\n');
        cin >> option;
    } //end of error-handling code
    
    while(option != 5) {
        
        optionHandling(option, figure);
        
        cout << endl ;
        startScreen();
        
        cin.clear();
        cin.ignore(10, '\n');
        
        cin >> option;
        
    }// End while loop
    
    cout << "You chose to exit the program!! See you next time." << endl;
    
    return 0;
}


//==============================================================================
//                    FUNCTIONS IMPLEMENTATION
//==============================================================================

//Function : startScreen() : void
//Description: this function is used as an user interface to display information and the options for the program
void startScreen() {
    
    cout << "**************************************************************************" << endl << endl;
    cout << "Choose the options that you want the progaram to do by typing the number: " << endl;
    cout << "1. Perimeter and area of Rectangle." << endl;
    cout << "2. Perimeter and area of Circle." << endl;
    cout << "3. Perimeter and area of Square." << endl;
    cout << "4. Perimeter and area of Triangle." << endl;
    cout << "5. Exit the program." << endl << endl;
    cout << "**************************************************************************" << endl << endl;
}

//Function : optionHandling(int, PlaneFigure*) : void
//Description: this function is used to handle option entered by user and calculate and provide the appropriate result
//Parameter : option : int, object : PlaneFigure*
void optionHandling(int option, PlaneFigure* object) {
    double side1, side2, side3; // 3 sides of the figure object
    
    switch(option) {
        case 1:{ // the figure is rectangle -> only require 2 sides represent for width and height
            cout << "Enter width of the rectangle: ";
            cin >> side1;
            cout << "Enter height of the rectangle: ";
            cin >> side2;
            
            object = new Rectangle(side1, side2); // allocate memory for rectangle object
            
            //Display perimeter and area of the rectangle
            cout << "The perimeter of the rectangle is: " << object->perimeter() << " cm" << endl;
            cout << "The area of the rectangle is: " << object->area() << " cm" << endl;
            
            delete object; //free the memory pointed by the pointer object
            
            break;
        }
            
        case 2: { //the figure is circle -> only require 1 side represent for radius
            cout << "Enter the radius of the circle: ";
            cin >> side1;
            
            object = new Circle(side1); // allocate memory for circle object
            
            //Display perimeter and area of the circle
            cout << "The perimeter of the circle is: " << object->perimeter() << " cm" << endl;
            cout << "The area of the circle is: " << object->area() << " cm" << endl;
            
            delete object;
            
            break;
        }
            
        case 3: { //the figure is square -> only require 1 side
            cout << "Enter side of the square: ";
            cin >> side1;
            
            object = new Square(side1); //allocate memory for square object
            
            //Display perimater and area of the square
            cout << "The perimeter of the square is: " << object->perimeter() << " cm" << endl;
            cout << "The area of the square is: " << object->area() << " cm" << endl;
            
            delete object;
            
            break;
        }
            
        case 4: { //the figure is triangle -> require 3 sides
            cout << "Enter side1 of the triangle: ";
            cin >> side1;
            cout << "Enter side2 of the triangle: ";
            cin >> side2;
            cout << "Enter side3 of the triangle: ";
            cin >> side3;
            
            object = new Triangle(side1, side2, side3); //allocate memory for triangle object
            
            //display the perimater and area of the triangle
            cout << "The perimeter of the triangle is: " << object->perimeter() << " cm" << endl;
            cout << "The area of the triangle is: " << object->area() << " cm" << endl;
            
            delete object;
            
            break;
        }
        default: {
            cout << "Sorry!! The option is invalid, please choose again." << endl;
        }
    }
}

