/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #5
 
 // Program name: EmployeeList
 // Date : March 14, 2017
 **************************************************/
#include <iostream>
#include <string>
#include "Employee.h"
#include "IndexList.h"

using namespace std;

const int SIZE = 10; //Max size of indexList

int main() {
    
    int num; //number of employees
    string name, phone; 
    
    cout << "List of type \"Employee\"" << endl;
    cout << "Enter number of employees: ";
    cin >> num;
    cout << endl;
    
    //Initialeze the index list
    indexList<Employee, SIZE> list;
    
    //Ask user enter the information of employees
    for (int i = 0; i < num; i++) {
        Employee em; //create a new object for employee
        cout << "Enter next name: ";
        cin >> name;
        cout << "Enter next phone number: ";
        cin >> phone;
        
        //set the values for employee
        em.setName(name);
        em.setPhone(phone);
        
        //Stop the loop if the list can not be appended anymore
        bool append = list.append(em);
        if (!append)
            break;
    }
    
    //Sort the list and display the result
    cout << endl;
    list.selSort();
    cout << "Employee list sorted in ascending order: " << endl;
    list.display();
    
    return 0;
}

