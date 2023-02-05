/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 210 - Assignment #5
 
 // Program name: Scheduling Simulator
 
 // Date : November 16, 2017
 **************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "Queue.h"
#include "Queue.cpp"
#include "Rooms.h"

using namespace std;

//*******************************************************
// struct Patient : Save a patient's information such as
//  name, age, specialtyCode and emergency conditon
//*******************************************************
struct Patient {
    string name;
    int age;
    string specialtyCode;
    bool emergency;
    Patient() {};  // Default Empty constructor
    
    // Constructor with data passed by user
    Patient(string n, int a, string code, bool status) : name(n), age(a), specialtyCode(code), emergency(status) {}
    // Friend function for overloading purpose
    friend ofstream& operator<<(ofstream& os, Patient patient);
};

//******************************************************
// Function : overload operator << to write information to
//   the output file
//******************************************************
ofstream& operator<<(ofstream& os, Patient patient) {
    os << patient.name;
    return os;
}
//***************************************************************************************************

//                  FUNCTION PROTOTYPE

//***************************************************************************************************

//*****************************************************
// Function : Prompt user enter D or P and handle the
//   input for wrong format by reject it and ask user
//   again
//*****************************************************
char inputHandle();

//*****************************************************
// Function : Prompt user enter I or O and handle the
//   input for wrong format by reject it and ask user
//   again
//*****************************************************
char inputHandle2();

//*****************************************************
// Function : ask for doctor's information and assign
//   him to his room (if applicable)
// Pre : Object rooms has been initialized
// Post: New doctor has been inserted to the corresponding position
//*****************************************************
void doctorCheckIn(Rooms&, Queue<Patient>[],ofstream &file);

//*****************************************************
// Function : check the doctor out and open the room
//    available for someone else
// Pre : Object rooms has been initialized
// Post: doctor is removed from the room
//*****************************************************
void doctorCheckOut(Rooms&, Queue<Patient>[], ofstream &file);

//*************************************************************
// Function : ask for patient's information and assign him to
//   the appropriate room's waiting list
// Pre : waiting list and rooms has been initialize
// Post: patient is assigned to a waiting list in an appropriate
//   room (if there is doctor available), otherwise, appologize
//*************************************************************
void patientCheckIn(Queue<Patient>[], Rooms&, ofstream &file);

//*************************************************************
// Function : Remove patient from the waiting list (after he saw his doctor)
// Pre : waiting list has been initialize
// Post: patient is dequeued from the waiting list
//*************************************************************
void patientCheckOut(Rooms&, Queue<Patient>[], ofstream &file);

//*****************************************************
// Function : find the shortest queue among waiting lists
// Pre : waiting lists have been initialized
// Post: the room which has the shortest waiting list
//******************************************************
int shortestQueue(int[], Queue<Patient>[], int);

//*******************************************************
// Function : Find the room whose doctor matches patient's need
// Pre : rooms has been initialized, waiting lists has been initialized
// Post: the room which matches patient's requirement
//*******************************************************
int searchDoctor(string, Rooms&, Queue<Patient>[]);

//*******************************************************
// Function : append the second queue to the first queue,
//      then empty out the second queue
// Pre : 2 queues have been initialize
// Post: queue 2 is appended to queue 1, and then queue 2 is emptied out
//*******************************************************
void appendQueue(Queue<Patient> &q1, Queue<Patient> &q2);

//*******************************************************
// Function : Display all the rooms with its waiting list and doctor
// Pre : room and waiting list have been initialized
// Post: information is written on the output file
//*******************************************************
void showStructure(Rooms &room, Queue<Patient>[], ofstream&);

//***************************************************************************************************

//                  MAIN FUNCTION

//***************************************************************************************************

int main() {
    
    // Array of 100 rooms (array of 100 doctors)
    Rooms rooms; //Initilize all room available
    
    // The waiting list for each room (array of queue of patient)
    Queue<Patient> waitingList[100];
    
    //output file stream which will be used to record the output
    ofstream output;
    output.open("logFile.txt");
    
    // Prompt user enter Doctor or Patient
    char subject = inputHandle();
    while(subject != 'Q') { // The program will stop if user enters Q
        // Prompt user enter check in or check out
        char action = inputHandle2();
        
        if(subject == 'D') {
            if(action == 'I')
                doctorCheckIn(rooms, waitingList, output);
            else
                doctorCheckOut(rooms, waitingList, output);
        }
        else {
            if(action == 'I')
                patientCheckIn(waitingList, rooms, output);
            else
                patientCheckOut(rooms, waitingList, output);
        }
        
        subject = inputHandle();
    }
    
    cout << "****************************************" << endl;
    cout << "You chose to quit the program. All the data will be deleted." << endl;
    
    output.close();
    
    return 0;
}



//*********************************************************************************************************

//           FUNCTION IMPLEMENTATION

//*********************************************************************************************************

//*****************************************************
// Function : Prompt user enter D or P and handle the
//   input for wrong format by reject it and ask user
//   again
//*****************************************************
char inputHandle() {
    char input;
    cout << "Type D for Doctor or P for Patient: ";
    cin >> input;
    
    while(input != 'D' && input != 'P' && input != 'Q') {
        cout << "Error!! Wrong format. Please only type D or P" << endl << endl;
        cout << "Type D for Doctor or P for Patient: ";
        cin >> input;
    }
    return input;
}

//*****************************************************
// Function : Prompt user enter I or O and handle the
//   input for wrong format by reject it and ask user
//   again
//*****************************************************
char inputHandle2() {
    char input;
    cout << "Type I for check in or O for check out: ";
    cin >> input;
    while(input != 'I' && input != 'O') {
        cout << "Error!! Wrong format. Please only type I or O" << endl << endl;
        cout << "Type I for check in or O for check out: ";
        cin >> input;
    }
    return input;
}

//*****************************************************
// Function : ask for doctor's information and assign
//   him to his room (if applicable)
// Pre : Object rooms has been initialize
// Post: New doctor has been inserted to the corresponding position
//*****************************************************
void doctorCheckIn(Rooms &rooms, Queue<Patient> list[], ofstream &file) {
    string name, code;
    int room;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter room number: ";
    cin >> room;
    while(room < 1 || room > 100) {
        cout << "Error!! Enter the room from 1 to 100" << endl;
        cout << "Enter room number: ";
        cin >> room;
    }
    cout << "Enter Specialty Code: ";
    cin >> code;
    
    Doctor newDoctor(name, room, code); // create a new doctor with these information
    
    if (rooms.insert(newDoctor, room)) { //assign the doctor to the room
        
        cout << "The room is available and ready to use." << endl << endl;
        
        // Write down the info to the file
        file << "Doctor " << newDoctor.name << " is checked in and is assigned to room " << newDoctor.roomNumber << "\n";
        file << "The current status of the clinic: \n";
        showStructure(rooms, list, file);
    }
    else // reject if the room is not available
        cout << "Error!! The selected room is in used right now!! Please try again later." << endl << endl;
}

//*****************************************************
// Function : check the doctor out and open the room
//    available for someone else
// Pre : Object rooms has been initialize
// Post: doctor is removed from the room
//*****************************************************
void doctorCheckOut(Rooms &rooms, Queue<Patient> waitingList[], ofstream &file) {
    string name;
    cout << "Enter name: ";
    cin >> name;
    
    // search for the room that the doctor was assigned
    for (int i = 0; i < 100; i++) {
        if (rooms.getName(i) == name) {
            // Empty out the room
            rooms.emptyRoom(i);
            
            // If there is still people in the waiting list, move them to another room
            if(!waitingList[i].isEmpty()) {
                // Find the room which has shortest waiting list
                int nextRoom = searchDoctor(rooms.getCode(i), rooms, waitingList);
                // Append the waiting list to that room
                appendQueue(waitingList[nextRoom], waitingList[i]);
            }
            cout << "You are checked out. Have a good day." << endl << endl;
            
            // Write down the info to the output file
            file << "Doctor " << rooms.getName(i) << " is checked out. The current status of the clinic is: \n";
            showStructure(rooms, waitingList, file);
            return;
        }
    }
    // If the name entered is not in the list
    cout << "Error!! The name you entered is not in the list. Please try again." << endl << endl;
}

//*************************************************************
// Function : ask for patient's information and assign him to
//   the appropriate room's waiting list
// Pre : waiting list and rooms has been initialize
// Post: patient is assigned to a waiting list in an appropriate
//   room (if there is doctor available), otherwise, appologize
//*************************************************************
void patientCheckIn(Queue<Patient> list[], Rooms &rooms, ofstream &file) {
    string name, code;
    int age;
    int status;
    
    // Ask user for information
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter Specialist Code: ";
    cin >> code;
    cout << "Type 1 if this is an emergency case, otherwise type 0: ";
    cin >> status;
    
    bool emergency = (status == 1);
    
    // Create new patient with the info
    Patient newPatient(name, age, code, emergency);
    
    int room; // The room where patient will be assigned to
    
    if(newPatient.age < 16) // assign to PED if patient's age is less than 16
        room = searchDoctor("PED", rooms, list);
    else
        room = searchDoctor(newPatient.specialtyCode, rooms, list);
    
    if(room == -1) // There is no doctor available
        cout << "Sorry !! There is no doctor available at the moment." << endl << endl;
    else {
        cout << "You can go to the room number " << room + 1 << " where doctor " << rooms.getName(room) << " has been assigned." << endl << endl;
        
        // put the new patient to the waiting list of that room
        list[room].enqueue(newPatient, newPatient.emergency);
        
        // write the info to the output file
        file << "Patient " << newPatient.name << " is assigned to room " << room + 1 << " where doctor " << rooms.getName(room) << " has been assigned.\n";
        file << "The current clinic status is \n";
        showStructure(rooms, list, file);
    }
}

//*************************************************************
// Function : Remove patient from the waiting list (after he saw his doctor)
// Pre : waiting list has been initialize
// Post: patient is dequeued from the waiting list
//*************************************************************
void patientCheckOut(Rooms &rooms, Queue<Patient> list[], ofstream &file) {
    string name;
    int roomNumber;
    cout << "Enter your name: ";
    cin >> name;
    
    cout << "Enter your room number: ";
    cin >> roomNumber;
    
    // save patient's information for further record
    Patient patient;
    
    list[roomNumber - 1].dequeue(patient); // dequeue the patient from the list
    
    cout << "You have been checked out. Have a good day." << endl << endl;
    
    // Write down the info to the output file
    file << "Patient " << patient.name << " is checked out. The current clinic status is \n";
    showStructure(rooms, list, file);
}

//*****************************************************
// Function : find the shortest queue among waiting lists
// Pre : waiting lists have been initialize
// Post: the room which has the shortest waiting list
//******************************************************
int shortestQueue(int matches[], Queue<Patient> list[], int length) {
    // Initialize shortest list to the value in the room number which is the first element of rooms
    int shortest = list[matches[0]].getLength();
    int result = matches[0]; // The room that has shortest waiting list
    
    // Loop through matches, to find the shortest waiting list in each room
    for(int i = 0; i < length; i++)
        if(list[matches[i]].getLength() < shortest) {
            shortest = list[matches[i]].getLength();
            result = matches[i];
        }
    
    return result;
}

//*******************************************************
// Function : Find the room whose doctor matches patient's need
// Pre : rooms has been initialized, waiting lists has been initialized
// Post: the room which matches patient's requirement
//*******************************************************
int searchDoctor(string code, Rooms &rooms, Queue<Patient> waitingList[]) {
    
    int matches[100]; // store the room where the doctors are matched
    for(int i = 0; i < 100; i++)
        matches[i] = -1; // initilize value of matches for no match
    
    int numOfMatches = 0; // Number of matches
    
    //return -1 if all rooms are empty (no doctor available)
    if(rooms.getLength() == 0)
        return -1;
    else {
        
        //If a match is found, put the room number into the array matches
        for(int i = 0; i < 100; i++)
            if (rooms.opened(i) && rooms.getCode(i) == code) {
                matches[numOfMatches] = i;
                numOfMatches++;
            }
        
        //If there is no match, start searching for a GP
        if(numOfMatches == 0)
            for(int i = 0; i < 100; i++)
                if(rooms.opened(i) && rooms.getCode(i) == "GP") {
                    matches[numOfMatches] = i;
                    numOfMatches++;
                }
        //If no GP is found, continue search for any doctor
        if(numOfMatches == 0)
            for(int i = 0; i < 100; i++)
                if(rooms.opened(i)) {
                    matches[numOfMatches] = i;
                    numOfMatches++;
                }
    }
    
    return shortestQueue(matches, waitingList, numOfMatches);
}

//*******************************************************
// Function : append the second queue to the first queue,
//      then empty out the second queue
// Pre : 2 queues have been initialize
// Post: queue 2 is appended to queue 1, and then queue 2 is emptied out
//*******************************************************
void appendQueue(Queue<Patient> &q1, Queue<Patient> &q2) {
    Patient temp; //Temporary variable used to keep the info dequeued from q2
    // Loop until q2 is empty
    while(q2.getLength() != 0) {
        // Dequeue q2
        q2.dequeue(temp);
        // enqueue patient to q1
        q1.enqueue(temp, temp.emergency);
    }
}

//*******************************************************
// Function : Display all the rooms with its waiting list and doctor
// Pre : room and waiting list have been initialized
// Post: information is written on the output file
//*******************************************************
void showStructure(Rooms &room, Queue<Patient> list[], ofstream &file){
    // Write out the first line to the file (labels: Room, Doctor, Patient List)
    file << "Room\tDoctor\t\t\tPatient List" << "\n";
    // Search among 100 rooms
    for(int i = 0; i < 100; i++) {
        // If a room is open
        if(room.opened(i)) {
            // 1. Write out the room number and doctor of that room
            file << i + 1 << "\t\t" << room.getName(i) << "\t\t\t\t";
            // 2. Use member function showStructure from the queue to write out the list of patients
            list[i].showStructure(file);
            file << "\n\n";
        }
    }
}

