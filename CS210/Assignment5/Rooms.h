
#ifndef Rooms_h
#define Rooms_h

#include <string>

using namespace std;

//*******************************************************************
// struct Doctor : save doctor's information
//*******************************************************************
struct Doctor {
    string name;
    int roomNumber;
    string specialtyCode;
    bool available;     // false if doctor is assigned to a room
    Doctor() : available(true){} // default constructor
    // customed constructor
    Doctor(string n, int r, string code) : name(n), roomNumber(r), specialtyCode(code){}
    
    //**************************************************
    // Function : update doctor's info of a room (when a new doctor is assigned to a room)
    //**************************************************
    void update(string n, int number, string code) {
        name = n;
        roomNumber = number;
        specialtyCode = code;
        available = false;
    }
};

//************************************************************************
// Class Rooms : represent the clinic rooms (technically an array of Doctor)
//************************************************************************
class Rooms{
public:
    // Default constructor : all rooms are not available
    Rooms() : length(0) {}
    
    //****************************************************
    // Function : insert doctor into a room (if applicable)
    // Pre : rooms has been initialized
    // Post: true if doctor was assigned successfully, otherwise false
    //****************************************************
    bool insert(Doctor info, int roomNumber){
        if(!rooms[roomNumber - 1].available) // if the room is being occupied by someone
            return false;
        else { // update the room's info
            rooms[roomNumber - 1].update(info.name, info.roomNumber, info.specialtyCode);
            length++;   // increase the number of active doctor
            return true;
        }
    }
    
    //*******************************************************
    // Function : put the room's status back to available
    // Pre : rooms have been initialized
    // Post: the status change to available
    //*******************************************************
    void emptyRoom(int roomNumber) {
        if(length > 0) {
            rooms[roomNumber].available = true;
            length--; // decrease the number of active doctor
        }
    }
    
    //*******************************************************
    // Function : return the number of active doctor
    //*******************************************************
    int getLength() {
        return length;
    }
    
    //*******************************************************
    // Function : return the doctor's name in a room
    //*******************************************************
    string getName(int roomNumber){
        return rooms[roomNumber].name;
    }
    
    //*******************************************************
    // Function : return doctor's specialty code in a room
    //*******************************************************
    string getCode(int roomNumber){
        return rooms[roomNumber].specialtyCode;
    }
    
    //*******************************************************
    // Function : check if there is a doctor in the room
    //*******************************************************
    bool opened(int roomNumber) {
        return (!rooms[roomNumber].available);
    }
private:
    Doctor rooms[100];
    int length; // Number of active (available doctor)
};

#endif
