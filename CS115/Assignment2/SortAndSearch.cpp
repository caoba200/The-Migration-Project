/*************************************************
 // Student name : Bao D. Cao
 // Student ID : 200363431
 // Email : caoba200@uregina.ca
 
 // CS 115 - Assignment #2
 
 // Program name: Binary Search and Bubble Sort (Project 4, pg. 557 & Project 12, pg.560)
 // Date : January 26, 2017
 
 **************************************************/
#include <iostream>
#include <vector>

using namespace std;

//========================= bubbleSort : void =============================
//sort the array in the ascending order
//1. let "last" be the last element of the array
//2. loop until "last" matches the first element of the array
//  2.1 loop from the beginning of the array to "last"
//      2.1.1 compare the current element to the next one
//          2.1.1.1 if the current one is bigger, swap them
//  2.2 decrease "last" by one
//=========================================================================
void bubbleSort(vector<int>&, int size);

//========================= binarySearch ==================================
//find an item in the array, then return its index. If can't not find it, return -1
//1. let "bottom" be the first element of the array
//2. let "top" be the last element of the array
//3. loop while top is still larger than bottom
//  3.1 let "middle" be the middle element of the array
//  3.2 if item = array[middle], then return middle
//  3.3 if item > array[middle], then last = middle + 1
//  3.4 if item < array[middle], then last = middle - 1
//4. if can't find the item, then return -1
//==========================================================================
int binarySearch(const vector<int>, int, int);

//======================== swap : inline void ==============================
//an inline function which swap 2 numbers
//==========================================================================
inline void swap(int &a, int &b) { a = ((a = a + b, b = a - b), a - b); }

//======================== arrayInitialization : void ======================
//ask user enter the numbers and then read them to the array
//==========================================================================
void arrayInitialization(vector<int>&, int);

//======================== print : void ====================================
//print all elements of the array
//==========================================================================
void print(const vector<int>, int);

//======================== searchInterface : void ==========================
//ask user the item to be searched and then display the result (use function
//      "binarySearch" to implement the search)
//===========================================================================
void searchInterface(const vector<int>, int);

//======================= quit : void ======================================
//ask user whether they want to stop the program and update the boolean
//  variable which is used to determine the state of the program (quit or not)
//==========================================================================
void quit(bool&);


//==================================== MAIN FUNCTION ========================
int main() {
    
    //----------------Variable Decleration---------------------
    int size;
    cout << "Enter the number of naturals: ";
    cin >> size;
    
    vector<int> array(size);
    //---------------------------------------------------------
    arrayInitialization(array, size); //Initialize the array (user input)
    
    bubbleSort(array, size);          //Sort the array in the ascending order (bubble sort)
    
    print(array, size);               //Print the sorted array
    
    bool stop = false;                //Check if user wanna stop the program (y or n)
    while (!stop) {
        searchInterface(array, size); //Ask for the item and return its index
        quit(stop);                   //Ask if user want to quit the program
    }
    
    cout << "Good bye!" << endl;
    
    return 0;
}


//========================== FUNCTION IMPLEMENTATION =============================


//========================= bubbleSort : void =============================
//sort the array in the ascending order
//1. let "last" be the last element of the array
//2. loop until "last" matches the first element of the array
//  2.1 loop from the beginning of the array to "last"
//      2.1.1 compare the current element to the next one
//          2.1.1.1 if the current one is bigger, swap them
//  2.2 decrease "last" by one
//=========================================================================
void bubbleSort(vector<int> &array, int size) {
    int last = size - 1;
    while (last > 0) { // while last doesn't match the 1st element
        for (int i = 0; i < last; i++)
            if (array[i] > array[i + 1])
                swap(array[i], array[i + 1]);
        last--; // move last up to one position (decrease its value)
    }
}

//========================= binarySearch ==================================
//find an item in the array, then return its index. If can't not find it, return -1
//1. let "bottom" be the first element of the array
//2. let "top" be the last element of the array
//3. loop while top is still larger than bottom
//  3.1 let "middle" be the middle element of the array
//  3.2 if item = array[middle], then return middle
//  3.3 if item > array[middle], then last = middle + 1
//  3.4 if item < array[middle], then last = middle - 1
//4. if can't find the item, then return -1
//==========================================================================
int binarySearch(const vector<int> array, int size, int item) {
    int bottom = 0;
    int top = size - 1;
    int middle;
    
    while (top >= bottom) { // while top element doesn't past the bottom one
        middle = (top + bottom) / 2; // set middle
        if (array[middle] == item)
            return middle; // item founded
        else if (array[middle] > item) // search for the half-left of the array
            top = middle - 1;
        else                            // search for the half-right if the array
            bottom = middle + 1;
    }
    
    return -1; // item couldn't be found
    
}

//======================== arrayInitialization : void ======================
//ask user enter the numbers and then read them to the array
//==========================================================================
void arrayInitialization(vector<int> &array, int size) {
    cout << "Enter the natural numbers to sort:" << endl;
    for (int i = 0; i < size; i++)
        cin >> array[i];
    cout << endl;
}

//======================== print : void ====================================
//print all elements of the array
//==========================================================================
void print(const vector<int> array, int size) {
    cout << "Numbers sorted in ascending order: " << endl;
    for (int i = 0; i < size; i++)
        cout << array[i] << " " ;
    
    cout << endl << endl;
}

//======================= quit : void ======================================
//ask user whether they want to stop the program and update the boolean
//  variable which is used to determine the state of the program (quit or not)
//==========================================================================
void quit(bool &stop) {
    string answer;
    cout << "Do you want to continue [Y/N]: ";
    cin >> answer;
    while(1) {
        if (answer == "YES" || answer == "yes" || answer == "y" || answer == "Y" || answer == "Yes") {
            stop = false;
            break;
        }
        else if (answer == "NO" || answer == "no" || answer == "n" || answer == "N" || answer == "No") {
            stop = true;
            break;
        }
        else { // user's answer is different than either yes or no (wrong format)
            cout << "Do you want to continue [Y/N]: ";
            cin >> answer;
        }
    }
}

//======================== searchInterface : void ==========================
//ask user the item to be searched and then display the result (use function
//      "binarySearch" to implement the search)
//===========================================================================
void searchInterface(const vector<int> array, int size) {
    int item, index;
    cout << "Enter the number to search: ";
    cin >> item;
    
    index = binarySearch(array, size, item); // find the index of the item using binarySearch function
    
    if (index != -1) // index found
        cout << "Number " << item << " is found at position " << index << endl;
    else              // index not found
        cout << "Number " << item << " does not exist!" << endl;
    cout << endl;
}
