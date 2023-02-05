
#include "Employee.h"
#include <string>
#include <iostream>

using namespace std;

Employee::Employee() {  //Default constructor
    name = "";
    phoneNumber = "";
}

//=============== setter : setName=================
void Employee::setName(string employeeName) {
    name = employeeName;
}

//=============== getter : displayName =============
void Employee::displayName() const{
    cout << name;
}

//=============== setter : setPhone ================
void Employee::setPhone(string phone) {
    if (phone.length() != 8) {
        cerr << "Phone number is in incorrect format!!" << endl;
        phoneNumber = "000-0000";
    }
    else {
        phoneNumber = phone;
    }
}

//=============== getter : displayPhone ============
void Employee::displayPhone() const {
    cout << phoneNumber;
}

//=============== operator overloaded : < ==========
//compare only name to determine which Employee object
// is bigger (alphabetically)
//==================================================
bool Employee::operator<(Employee& e) const {
    return name < e.name;
}

//=============== operator overloaded : << =========
//display the name of employees
//==================================================
ostream& operator<<(ostream& os, const Employee& e) {
    os << e.name;
    return os;
}

