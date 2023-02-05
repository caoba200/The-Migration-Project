/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 210 - Assignment #4
 
 // Program name: Sale Record
 
 // Date : October 24, 2017
 **************************************************/
#include <iostream>

using namespace std;

void HanoiTower(int disk, int source, int destination, int temporary, int &step) {
    //If there is one disk, just move it from the source to the destination
    if(disk == 1) {
        cout << source << "---------->" << destination << endl;
        step++; //Increase the number of moves
    }
    else {
        //Move the first n - 1 disk from source to temporary
        HanoiTower(disk - 1, source, temporary, destination, step);
        //Move the last disk from source to the destination
        HanoiTower(1, source, destination, temporary, step);
        //Move the previous n - 1 disk (from temporary) back to destination
        HanoiTower(disk - 1, temporary, destination, source, step);
    }
}

int main() {
    int disk;
    cout << "Enter the number of Disk: ";
    cin >> disk;
    int source = 1; //Peg 1 is the peg where the disks originally stay
    int destination = 3; //Peg 2 is the peg where disks are supposed to be moved to
    int temporary = 2; //Peg 2 is a temporary peg which is used to hold the upper disks while we need to move the lower disks
    int step = 0; //Number of moves
    
    //We assume we want to move disks from peg 1 to peg 3, peg 2 is used as a temporary peg
    HanoiTower(disk, source, destination, temporary, step);
    cout << "Number of moves: " << step << " steps" << endl;
    return 0;
}
