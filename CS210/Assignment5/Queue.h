
#ifndef Queue_h
#define Queue_h

#include <fstream>

using namespace std;

//*************************************************
//  Node : a template data structure which is use *
//    to form linked list which will be used to   *
//    implement queue.                            *
//*************************************************
template<class T>
struct Node{
    T data;
    Node* next;
    Node(T item, Node* n) : data(item), next(n){}
};

//*************************************************
// Queue : a template abstract queue which will be*
//   used for this assignment.                    *
// Attributes : (Node*)front, (Node*)rear, length *
// Member functions : clear(), isEmpty(),         *
//   enqueue(T, bool), dequeue(), getLength()     *
// Note : this is actually a priority queue, which*
//   is the requirement for this assignment       *
//*************************************************
template<class T>
class Queue {
public:
    Queue(); //Constructor
    ~Queue(); //Destructor
    //********************************************
    // Function : delete all elements of the queue
    // Pre : queue has been initialized
    // Post : empty queue
    //********************************************
    void clear();
    
    //********************************************
    // Function : check if the queue is empty
    // Pre : queue has been initialized
    // Post : return true is the queue is empty
    //********************************************
    bool isEmpty() const;
    
    //********************************************
    // Function : add an element to the queue based
    //            on its priority
    // Pre : queue has been initialized
    // Post : an element is added to the queue based
    //        on its priority
    //********************************************
    void enqueue(T item, bool priority);
    
    //********************************************
    // Function : remove the first element from the queue
    // Pre : queue has been initialized
    // Post : the first element is removed from the queue
    //********************************************
    void dequeue(T &info);
    
    //********************************************
    //Function : return the current length of the queue
    //Pre : queue has been initialized
    //Post : the current length of the queue
    //********************************************
    int getLength() const;
    
    //********************************************
    // Function : show all the element in a queue.
    //   used for debugging purposes and for writing
    //   info to a file
    // Pre : Queue has been initialize
    // Post: All the element is written to the file
    //********************************************
    void showStructure(ofstream&);
private:
    Node<T> *front;
    Node<T> *rear;
    int length;
};

//template<class T>
//ofstream& operator<<(ofstream &os, Queue<T> &list);

#endif
