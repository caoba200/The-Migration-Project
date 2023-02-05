
#ifndef Employee_h
#define Employee_h

#include <iostream>
#include <string>

using namespace std;

class Employee {
public:
    Employee();
    void setName(string); //setter
    void displayName() const;
    void setPhone(string); //setter
    void displayPhone() const;
    
    //=============== operator overloaded : < ==========
    //compare only name to determine which Employee object
    // is bigger (alphabetically)
    //==================================================
    bool operator<(Employee&) const;
    
    //=============== operator overloaded : << =========
    //display the name of employees
    //==================================================
    friend ostream& operator<<(ostream&, const Employee&);
private:
    string name;
    string phoneNumber;
};

#endif
