
#include "IndexList.h"
#include <iostream>

using namespace std;

//========= Default constructor =============
template <class T, int maxSize>
indexList<T, maxSize>::indexList() {
    size = 0;
}

//========== Append =========================
//append the item to the end of the index list
//show error if the index list is full
//===========================================
template <class T, int maxSize>
bool indexList<T, maxSize>::append(const T& item) {
    if (size < maxSize) {
        elements[size] = item;
        size++;
        return true;
    }
    else {
        cerr << "Array is filled - can't append!" << endl;
        return false;
    }
}

//========== Selection sort =================
//sort elements in ascending order
//===========================================
template <class T, int maxSize>
void indexList<T, maxSize>:: selSort() {
    T temp; //Temporary object used for swapping

    for(int i = 0; i < size - 1; i++){
        int minIndex = i; //index of the smallest element
        
        //Find the index of the smallest element
        for(int j = i + 1; j < size; j++)
            if (elements[j] < elements[minIndex])
                minIndex = j;
        
        //Swap the current index with the smallest index
        if (minIndex != i) {
            temp = elements[i];
            elements[i] = elements[minIndex];
            elements[minIndex] = temp;
        }
    }
}

//========== Display ============================
//Display each elements of index list in a row
//===============================================
template <class T, int maxSize>
void indexList<T, maxSize>::display() const {
    for (int i = 0; i < size; i++)
        cout << elements[i] << endl;
}


//========== Operator Overloaded << =============
/*template <class T, int maxSize>
ostream& operator<< (ostream& os, const indexList<T, maxSize>& list) {
    for (int i = 0; i < list.size; i++)
        os << list.elements[i] << endl;
    return os;
}*/

template class indexList <Employee, 10>;
