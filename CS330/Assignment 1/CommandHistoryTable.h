/*
	HistoryTable: A structure which is used to store commands user entered in (in string format)
	A queue (implemented by linked list) is used to implement the table. Therefore, the oldest command
	will show up on the top of the screen (the first element on the queue but with the reversed order number)
	and the newest command will show up at the bottom of the screen
*/
#ifndef COMMAND_HISTORY_TABLE_H
#define COMMAND_HISTORY_TABLE_H
#include <string>
#include <iostream>

using namespace std;

// The node which is used to built queue is used to store the array of tokenized command line 
// and the token counter
struct Node{
	string data[10];  // array of tokenized command line
	int tokenCounter; // token counter
	Node* next;		  // pointer to the next element of the linked list	
};

class HistoryTable {
public:
	//*************************************************
	// Function: Initialize the table - Constructor
	// Pre : uninitialized table
	// Post: initialized table with head and tail point to NULL 
	//		and size is entered by user
	//**************************************************
	HistoryTable(int newSize) {
		head = 0;
		tail = 0;
		size = newSize;
		counter = 0;
	}

	//***************************************************
	// Function: Destructor - Free the memory occupied 
	//		by the table
	//***************************************************
	~HistoryTable() {
		if (size != 0) {
			Node* temp = head;   // pointer to the first element of the list
			while(head != tail) {
				head = head->next; 
				delete temp;
				temp = head;
			} // delete each element consecutively

			delete temp; // delete the last element

			// assign head and tail to NULL
			temp = 0;
			head = 0;
			tail = 0;
		}
	}

	//****************************************************
	// Function: insert new command to the table
	// Pre : the table has been initialized
	// Post: new command is inserted into the table
	//****************************************************
	bool insert(string newCommand[], int newCounter) {
		// Nothing to insert if the size is 0
		if (size == 0)
			return false;
		// if the table is empty
		else if (head == 0) {
			Node* newNode = new Node();
			arrayCopy(newNode->data, newCommand, newCounter);
			newNode->tokenCounter = newCounter;
			newNode->next = 0;
			head = newNode;
			tail = newNode;
			counter++;
		}
		else {
			// insert to the bottom of the list if there are space on the table
			if (counter < size) {
				// create new node for the new command
				Node* newNode = new Node();
				arrayCopy(newNode->data, newCommand, newCounter);
				newNode->tokenCounter = newCounter;

				// add the node to the table
				tail->next = newNode;
				tail = newNode;
				counter++; // increase the counter
			}
			// if the table is full, delete the first element and insert new command
			// stop increasing the counter
			else { 
				// delete the oldest command
				Node* temp = head;
				head = temp->next;
				delete temp;
				temp = 0;

				// insert new command (use the same code segment from the previous if statement)
				Node* newNode = new Node();
				arrayCopy(newNode->data, newCommand, newCounter);
				newNode->tokenCounter = newCounter;

				// add the node to the table
				tail->next = newNode;
				tail = newNode;
			}
		}
		return true;
	}

	//**********************************************************
	// Function : show command history table
	// Pre : the table has been initialized
	// Post: the table is displayed on the screen
	//**********************************************************
	void showHistory() {
		if (counter != 0) {
			Node *temp = head;
			// Display each element on the table and its index number
			for (int i = counter; i > 0; i--) {
				cout << i << ": " << temp->data[0] << endl;
				if (temp->next != 0)
					temp = temp->next;
			}
		}
	}

	//*********************************************************
	// Function : change the table's size
	// Pre : table has been initialized
	// Post: the size is changed
	//*********************************************************
	void changeSize(int newSize) {
		size = newSize;
	}

	//**********************************************************
	// Function : return history table's counter (current number
	//   of commands on the table)
	//**********************************************************
	int getCounter() {
		return counter;
	}

	//**********************************************************
	// Function : find a command from history table based on its index
	// Pre : history table has been initialized
	// Post: a command is executed based on user's input
	//***********************************************************
	Node* ExecuteCommand (int index) {
		// Find the command from the table based on its index
		Node* temp = head;
		for (int i = 1; i <= index; i++) {
			temp = temp->next;
		}
		// Insert that command so it becomes the newest one
		insert(temp->data, temp->tokenCounter);

		// Return the pointer to the command that was found;
		return temp;
	}

	//**********************************************************
	// Function : delete oldest elements if counter is bigger than size
	// Pre : history table has been initialized
	// Post: history table is updated
	//**********************************************************
	void truncate() {
		// keep deleting the fist element until counter is equal to size
		while (counter > size) {
			Node *temp = head;
			head = head->next;
			delete temp;
			// reduce counter
			counter--;
		}
	}
private:
	Node *head;
	Node *tail;
	int size;
	int counter;

	//************************************************************
	// Function : copy the contain of one array to another
	// used to store the tokenized command line into node's data
	//************************************************************
	void arrayCopy(string destination[], string source[], int length) {
		for(int i = 0; i < length; i++)
			destination[i] = source[i];
	}
};

#endif