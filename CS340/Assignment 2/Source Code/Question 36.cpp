
#include <iostream>
#include <vector>

using namespace std;

// Function: return the position of the person who holds the potato after M passes
int movePotato(vector<int> &people, int currPosition, int moves) {
    // Increase the current position by 1 (next spot), check if that spot has a person (1),
    // then decrease the number of passes, stop the loop when number of passes reaches 0
    while(moves != 0) {
        currPosition++;
        // If current position goes out of range, set it to 0 (circular array)
        if(currPosition == people.size())
            currPosition = 0;
        moves--;
    }
    
    return currPosition;
}

// Function: Resize the vector (remove the empty cell, then shift the data and reduce the size by 1)
void resizeVector(vector<int> &people, int pos) {
    // Shift the data
    for(int i = pos; i < people.size() - 1; i++)
        people[i] = people[i + 1];
    // Reduce the vector size by 1
    people.resize(people.size() - 1);
}

int main() {
    
    int N,M;
    cout << "Enter the number of people N: ";
    cin >> N;
    cout << "Enter the number of passes M: ";
    cin >> M;
    
    vector<int> people(N);
    
    // Initialize the circle (1 indicates that each spot has a person)
    for(int i = 0; i < N; i++)
        people[i] = i + 1;
    
    // The position of the person who is holding the hot potato (initialzed at the first person)
    int currentPosition = 0;
    
    // The game will not stop as long as there is more than 1 people are still in the circle
    while(N != 1) {
        // Get the person who holds the potato after M passes
        int luckyGuy = movePotato(people, currentPosition, M);
        // remove that luckyGuy (including geting rid of the empty cell - the size of vector will reduce)
        resizeVector(people, luckyGuy);
        //reduce the number of participants
        N--;
        
        // The next person who will hold the potato
        currentPosition = luckyGuy;
    }
    
    // The last person remaining is also the only element in the vector (all empty cells are deleted)
    cout << "The winner of this game is the person at the spot number " << people[0] << endl;
    
    return 0;
}

