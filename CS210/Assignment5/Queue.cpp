
#include "Queue.h"

template<class T>
Queue<T>::Queue() {
    length = 0;
    front = 0;
    rear = 0;
}

template<class T>
Queue<T>::~Queue() {
    clear();
}

//********************************************
// Function : delete all elements of the queue
// Pre : queue has been initialized
// Post : empty queue
//********************************************
template<class T>
void Queue<T>::clear() {
    if(length != 0) {
        Node<T> *temp = front;
        while(front != 0) {
            front = temp->next; // Move front to the next element
            delete temp;  // Delete temp
            temp = front;
        }
        rear = 0; // assign rear to null
    }
}

//********************************************
// Function : check if the queue is empty
// Pre : queue has been initialized
// Post : return true is the queue is empty
//********************************************
template<class T>
bool Queue<T>::isEmpty() const {
    return length == 0;
}

//********************************************
// Function : add an element to the queue based
//            on its priority
// Pre : queue has been initialized
// Post : an element is added to the queue based
//        on its priority
//********************************************
template<class T>
void Queue<T>::enqueue(T item, bool priority) {
    Node<T> *node = new Node<T>(item, 0);
    //if the queue is empty, add new node to the front of the list
    if(isEmpty()) {
        front = node;
        rear = node;
    }
    else {
        //add to the front of the queue if the patient is in emergency
        if(priority) {
            node->next = front;
            front = node;
        }
        //otherwise, add the node to the end of the list
        else {
            rear->next = node;
            rear = node;
        }
    }
    length++; //increase the length to one
}

//********************************************
// Function : remove the first element from the queue
// Pre : queue has been initialized
// Post : the first element is removed from the queue
//********************************************
template<class T>
void Queue<T>::dequeue(T &info) {
    Node<T> *temp = front;
    front = temp->next; //move front to the next element
    temp->next = 0;  //disconnect the first element to the queue
    length--;           //reduce the length
    info = temp->data;  //Save the data
    delete temp;      // Delete the element
}

//********************************************
//Function : return the current length of the queue
//Pre : queue has been initialized
//Post : the current length of the queue
//********************************************
template<class T>
int Queue<T>::getLength() const {
    return length;
}

//********************************************
// Function : show all the element in a queue.
//   used for debugging purposes and for writing
//   info to a file (since this function don't
//   follow the constrain of a normal queue)
// Pre : Queue has been initialize
// Post: All the element is written to the file
//********************************************
template<class T>
void Queue<T>::showStructure(ofstream& file){
    // Check if the queue is not empty
    if(!isEmpty()) {
        Node<T> *temp = front;
        // Loop through each element of the queue
        // Write down the node's info to the file
        while(temp != 0) {
            file << temp->data << " ";
            temp = temp->next;
        }
    }
}
