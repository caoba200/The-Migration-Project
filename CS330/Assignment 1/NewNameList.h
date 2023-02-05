/*
	NewNameList: A structure which is used to store new names and its corresponding commands
	NewNameList is implemented in a similar way to HistoryTable (using queue, similar node structure)
*/

#ifndef NEW_NAME_LIST_H
#define NEW_NAME_LIST_H
	
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//************************************************
// Alias : the unit structure of linked list
//************************************************
struct Alias{
	string newName;     // stores new name
	string command[8]; // stores the corresponding command and its argument
	int tokenCounter;   // stores the command's token counter
	Alias* next;         // points to the next element
};

//***************************************************************
// NewNameList : A simple linked list which store new names list
//***************************************************************
class NewNameList{
public:
	//************************************************************
	// Constructor : Initialize the list
	// Pre : uninitialize list
	// Post: list is initialized with head point to NULL, size is set
	//       to the argument and counter is 0
	//*************************************************************
	NewNameList(int newSize) {
		head = 0;
		size = newSize;
		counter = 0;
	}

	//**************************************************************
	// Destructor : Free memory occupied by the list
	//**************************************************************
	~NewNameList(){
		clear();
	}

	//***************************************************************
	// Function : clear new name list
	// Pre : list has been initialized
	// Post: every element is deleted, list become empty
	//***************************************************************
	void clear() {
		if(size != 0) {
			Alias* temp = head; // pointer to the first element of the list
			while(head != 0) {
				head = head->next;
				delete temp;
				temp = head;
			} // delete each element consecutively
			delete temp; // delete the last element

			head = 0; // assign head to NULL
			counter = 0;
		}
	}

	//***************************************************************
	// Function : insert new entry onto the list
	// Pre : the list has been initialized
	// Post: new entry is inserted onto the list
	//***************************************************************
	bool insert(string newCommand[], int newCounter){
		// return false if there is no more space
		if (counter == size)
			return false;
		// return false if the size is 0
		else if (size == 0) 
			return false;
		else {
			Alias* newAlias = new Alias();
			newAlias->tokenCounter = newCounter - 2;
			// The first element in newCommand is "setnewname", the second is the subtituted name
			newAlias->newName = newCommand[1];
			// Store the rest of the array (the original command) into newAlias's command array
			for(int i = 2; i < newCounter; i++)
				newAlias->command[i - 2] = newCommand[i];
			// Check if the command is in the newnamelist
			Alias* temp = checkDuplicate(newAlias->command, newAlias->tokenCounter);
			// if found, just change the new name and free the memory pointed by newAlias
			if(temp != 0) {
				temp->newName = newCommand[1];
				delete newAlias;
			}
			// if not found, at newAlias into the top of the list and increase the counter
			else {
				newAlias->next = head;
				head = newAlias;
				counter++;
			}
		}
		return true;
	}

	//*****************************************************************
	// Function : retrieve the command based on its subtituted name
	// Pre: list has been initialized
	// Post: return the address of found element, if not found, return 0
	//*****************************************************************
	Alias* retrieve(string name) {
		// Pointer to the result (initialized to 0)
		Alias* result = 0;
		Alias* temp = head;
		// go through each element in the list
		while(temp != 0) {
			// if found the subtituted name, return the result
			// the complex expression is just a trick to avoid self-recursion
			// which happen when user substitutes a non-existed command with the same name 
			if (temp->newName == name && (temp->newName != temp->command[0] || temp->tokenCounter != 1)) {
				result = copy(temp);
				return result;
			}
			temp = temp->next;
		}
		return result;
	}

	//******************************************************************
	// Function : change list size
	//******************************************************************
	void setSize(int newSize) {
		size = newSize;
	}

	//*******************************************************************
	// Function : display the list
	// Pre : list has been initialized
	// Post: each element in the list is displayed
	//*******************************************************************
	void display() {
		Alias *temp = head;
		while (temp != 0) {
			// display the subtituted name first
			cout << temp->newName << " ";
			// display the content of the original command
			for(int i = 0; i < temp->tokenCounter; i++)
				cout << temp->command[i] << " ";
			cout << endl;
			temp = temp->next;
		}
	}

	//*********************************************************************
	// Function : remove an element based on the subtituted name
	// Pre : list has been initialized
	// Post: return true if an element is removed, otherwise return false
	//*********************************************************************
	bool remove(string name) {
		Alias *temp = head;
		// special case: remove the first element
		if (temp->newName == name) {
			head = head->next;
			delete temp;
			counter--;
			return true;
		}
		// locate the position
		while (temp->next != 0) {
			// if the name is found, remove that element
			if (temp->next->newName == name) {
				Alias *temp1 = temp->next;
				temp->next = temp1->next;
				temp1->next = 0;
				delete temp1;
				counter--;
				return true;
			}
			else
				temp = temp->next;
		}
		return false;
	}


	//**********************************************************************
	// Function : write content of the list into a file
	// Pre : list has been initialized
	// Post: the content is written into a file
	//**********************************************************************
	void write(ofstream &output) {
		Alias *temp = head;
		// Write each element of the list into file stream
		while(temp != 0) {
			// Write token counter and new name (separated by space)
			output << temp->tokenCounter << " " << temp->newName << " ";
			// Write each element in command tokens array
			for(int i = 0; i < temp->tokenCounter; i++)
				output << temp->command[i] << " ";
			// A trick to avoid the newline character at the end
			if(temp->next != 0)
				output << endl;
			temp = temp->next;
		}
	}

	//***********************************************************************
	// Function : read new name list from a file into the list
	// Pre : list has been initialized
	// Post: file's content is read into newname list
	//***********************************************************************
	void read(ifstream &input) {
		// Delete newnames list
		clear();
		// Add content from file stream into newnames list
		string commandLine;
		while(!input.eof()) {
			getline(input, commandLine);
			stringHandle(commandLine);
		}
	}

	//************************************************************************
	// Function : handle string input from input file stream (put it into appropriate place in newnames list)
	// Pre : list has been initialized
	// Post: input string is broken down into appropriate positions in newnames list
	//*************************************************************************
	void stringHandle(string str) {
		// string stream is used to handle the string
		stringstream ss(str);
		// if newnames list size is smaller than the number of commands in input file stream,
		// just stop adding
		if (counter == size) 
			return;
		// new alias to hold the information 
		Alias *newAlias = new Alias();
		// add command counter
		ss >> newAlias->tokenCounter;
		// add new name
		ss >> newAlias->newName;
		// add the original command and its argument
		for(int i = 0; i < newAlias->tokenCounter; i++)
			ss >> newAlias->command[i];

		// add newAlias to the top of newnames list
		newAlias->next = head;
		head = newAlias;
		counter++;
	}

	//**************************************************************************
	// Function : delete oldest elements if counter is bigger than size
	// Pre : newnames list has been initialized
	// Post: newnames list is updated
	//**************************************************************************
	void truncate() {
		// keep deleting the last element until counter is equal to size
		while (counter > size){
			Alias *temp = head;
			// move temp to the element next to the last one
			while(temp->next->next != 0) 
				temp = temp->next;
			Alias *temp1 = temp->next;
			// delete the last element
			temp->next = 0;
			delete temp1;
			// reduce counter
			counter--;
		}
	}
private:
	Alias* head;		// pointer to the first element of the list
	int size;		// new name list size
	int counter;	// current number of elements in the list

	//*******************************************************************
	//   PRIVATE FUNCTIONS : are used to help the public functions above
	//*******************************************************************

	//*******************************************************************
	// Function : check if the command is in the list.
	// Pre : the list has been initialized
	// Post: return the element that matches, otherwise, return null
	//********************************************************************
	Alias* checkDuplicate(string tokens[], int tokenCount) {
		// Pointer to the matched command (initialized to NULL)
		Alias *result = 0;
		// temporary pointer to the first element of the list
		Alias *temp = head;

		// move temp through the list
		while (temp != 0) {
			// check if the first element in temp->command matches the first element in tokens
			if(temp->command[0] == tokens[0]) {
				// if matched, check the arary length
				if (temp->tokenCounter == tokenCount) {
					// check if the rest of the array are equal (using check function below)
					if(check(temp->command, tokens, tokenCount)){
						// if 2 arrays are identical, assign the address of that element in the list to result
						// and end the loop
						result = temp;
						return result;
					}
				}
			}
			// if there is no match, move temp to the next element
			temp = temp->next;
		}
		return result;
	}

	//*********************************************************************
	// Function : check if 2 arrays are identical 
	//*********************************************************************
	bool check(string array1[], string array2[], int length) {
		for (int i = 0; i < length; i++)
			if(array1[i] != array2[i])
				return false;
		return true;	
	}

	//*****************************************************************
	// Function : copy values of an alias object to another (deep copy)
	//*****************************************************************
	Alias* copy(Alias* command2) {
		Alias *command1 = new Alias();
		command1->next = 0;
		command1->newName = command2->newName;
		command1->tokenCounter = command2->tokenCounter;
		for (int i = 0; i < command2->tokenCounter; i++) 
			command1->command[i] = command2->command[i];
		return command1;
	}
};

#endif