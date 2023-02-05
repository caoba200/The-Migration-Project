//
// HALshell.cpp
//
// Copyright (c) 2018 Robert J. Hilderman.
// All Rights Reserved.
//

#include "HALshell.h"
#include <fcntl.h>

// The "Shell"

void HALshell ()
{
    string tokens [MAX_COMMAND_LINE_ARGUMENTS];
    int tokenCount;
    do
    {
        tokenCount = GetCommand (tokens);
        ProcessCommand (tokens, tokenCount);
    } while (1);

    return;
}

int GetCommand (string tokens [])
{
    string commandLine;
    bool commandEntered;
    int tokenCount;


    //**************************************************************
    // ADD VARIABLE FOR THE ASSIGNMENT
    //**************************************************************
    // Command counter (initial value is 1)
    static int commandCounter = 1;
    // The current shell name
    string shellname;
    // The current terminator
    string terminator;
    // Command History size
    int commandHistorySize;
    // File input stream
    ifstream inFile;
    // New name size
    int newnamesize;
    //*************************************************************


    //*************************************************************
    // NEW INITIALIZATIONS FOR THE ASSIGNMENT
    //*************************************************************

    // Open and load shell name into the variable shellname ----------------------------------
    inFile.open("shellname"); 

    // Error handling for file opening
    if(!inFile) {
    	cout << "HALshell: shellname cannot be openned" << endl;
    	// default shellname 
    	shellname = "HALshell";
    }
    else
    	getline(inFile, shellname);

    inFile.close();

    // Open and load terminator into the variable terminator --------------------------------
    inFile.open("terminator");

    // Error handling for file opening
    if(!inFile) {
    	cout << "HALshell: terminator cannot be openned" << endl;
    	// default terminator
    	terminator = ">";
    }
    else
    	getline(inFile, terminator);

    inFile.close();

    // Open and load command history size ----------------------------------------------------
    inFile.open("historysize");
    if(!inFile) {
        cout << "HALshell: historysize cannot be openned" << endl;
        // default value for command history size
        commandHistorySize = 10;
    }
    else
        inFile >> commandHistorySize;
    inFile.close();

    // Update the size based on the historysize file
    historyTable.changeSize(commandHistorySize);

    // Update new name list size ------------------------------------------------------------
    inFile.open("newnamessize");
    if(!inFile) {
        cout << "HALshell: newnamessize cannot be openned" << endl;
        newnamesize = 10;
    }
    else
        inFile >> newnamesize;
    inFile.close();
    newnameList.setSize(newnamesize);

    //**************************************************************

    do
    {
        BlockSignals ("HALshell");
        cout << shellname << "[" << commandCounter << "]" << terminator << " ";
        while (1)
        {
            getline (cin, commandLine);
            commandEntered = CheckForCommand ();
            if (commandEntered)
            {
                break;
            }
        }
        UnblockSignals ("HALshell");
    } while (commandLine.length () == 0);

    tokenCount = TokenizeCommandLine (tokens, commandLine);

    //Increase command counter only if there is something entered in
    if(tokenCount > 0)
    	commandCounter++;

    // Save the new command onto the table (except the one used to access history)
    if(tokens[0] != "!")
        historyTable.insert(tokens, tokenCount);

    return tokenCount;
}

int TokenizeCommandLine (string tokens [], string commandLine)
{
    char *token [MAX_COMMAND_LINE_ARGUMENTS];
    char *workCommandLine = new char [commandLine.length () + 1];
    int i;
    int tokenCount;

    for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i ++)
    {
        tokens [i] = "";
    }
    strcpy (workCommandLine, commandLine.c_str ());
    i = 0;
    if ((token [i] = strtok (workCommandLine, " ")) != NULL)
    {
        i ++;
        while ((token [i] = strtok (NULL, " ")) != NULL)
        {
            i ++;
        }
    }
    tokenCount = i;

    for (i = 0; i < tokenCount; i ++)
    {
        tokens [i] = token [i];
    }

    delete [] workCommandLine;

    return tokenCount;
}

void ProcessCommand (string tokens [], int tokenCount)
{
    if (tokens [0] == "." || tokens [0] == "..")
    {
        BadCommand ();
        return;
    }
    
    if (tokens [0] == "about")
    {
        About (tokenCount);
        return;
    }
    else if (tokens [0] == "result")
    {
        Result (tokenCount);
        return;
    }
    else if (tokens [0] == "shutdown" || tokens [0] == "restart")
    {
        ShutdownAndRestart (tokens, tokenCount);
        // if no error, then never returns
        return;
    }

    //*******************************************
    //         Assignment 1
    //*******************************************

    // New command for changing the shell name
    else if (tokens [0] == "setshellname") {
    	SetShellName(tokens, tokenCount);
    	return;
    }
    // New command for changing the terminator
    else if (tokens [0] == "setterminator") {
    	SetTerminator(tokens, tokenCount);
    	return;
    }
    // New command for setting history size
    else if (tokens [0] == "sethistorysize") {
    	SetHistorySize(tokens, tokenCount);
    	return;
    }
    // New command for showing history size
    else if (tokens [0] == "showhistorysize") {
    	ShowHistorySize(tokenCount);
    	return;
    }
    // New command for showing history table
    else if (tokens [0] == "showhistory") {
        ShowHistory(tokenCount);
        return;
    }
    // New command for asscessing history
    else if (tokens [0] == "!") {
        AccessHistory(tokens, tokenCount);
        return;
    }
    // New command for setting newnamesize
    else if (tokens[0] == "setnewnamessize") {
    	SetNewNameSize(tokens, tokenCount);
    	return;
    }
    // New command for showing newnamesize
    else if (tokens[0] == "shownewnamessize") {
    	ShowNewNameSize(tokenCount);
    	return;
    }
    // New command for setting new name
    else if (tokens [0] == "setnewname") {
        SetNewName(tokens, tokenCount);
        return;
    }
    // New command for showing new name
    else if (tokens [0] == "shownewnames") {
        ShowNewName(tokenCount);
        return;
    }
    // New command for removing a name
    else if (tokens [0] == "removenewname") {
        RemoveNewName(tokens, tokenCount);
        return;
    }
    // New command for writting new name to a file
    else if (tokens [0] == "writenewnames") {
    	WriteNewName(tokens, tokenCount);
    	return;
    }
    // New command for reading new name from a file
    else if (tokens [0] == "readnewnames") {
    	ReadNewName(tokens, tokenCount);
    	return;
    }
    // New command for restoring defaults
    else if (tokens [0] == "restoredefaults") {
    	RestoreDefaults(tokens, tokenCount);
    	return;
    }
    // Handle substitute commands (from newnames list)
    Alias* newName = newnameList.retrieve(tokens[0]);
    if(newName != 0) {
        NewNameSubstitution(newName, tokens, tokenCount);
        return;
    }

    SendCommandLineToHALos (tokens, tokenCount);
    Wait ();
    GetMessageFromHALos ();
    PrintReturnStatus ();

    return;
}

void PrintReturnStatus ()
{
    if (returnMessage.length () > 0 && returnMessage != "ok" && returnMessage.substr (0, 15) != "creation time =")
    {
        cout << "HALshell: ";
        if (returnPid != "")
        {
            cout << "PID = [" << returnPid << "] ";
        }
        if (returnValue != "")
        {
            cout << "RETURN_VALUE = [" << returnValue << "] ";
        }
        if (returnMessage != "")
        {
            cout << "MESSAGE = [" << returnMessage << "]";
        }
        cout << endl;
        returnPid = "";
    }

    return;
}

// The "Communication Media"

void GetMessageFromHALos ()
{
    ifstream halOsMessageFile;

    halOsMessageFile.open ("HALosToHALshell");
    if (!halOsMessageFile)
    {
        cout << "HALshell: connection to HALos failed" << endl;
        exit (1);
    }

    getline (halOsMessageFile, returnPid);
    getline (halOsMessageFile, returnValue);
    getline (halOsMessageFile, returnMessage);

    if (!halOsMessageFile)
    {
        cout << "HALshell: message not received from HALos" << endl;
        return;
    }

    halOsMessageFile.close ();

    return;
}

void SendCommandLineToHALos (string tokens [], int tokenCount)
{
    ofstream commandLineFile;
    int i;
    union sigval dummyValue;

    commandLineFile.open ("HALshellToHALos");
    if (!commandLineFile)
    {
        cout << "HALshell: unable to initialize command line buffer" << endl;
        exit (1);
    }

    for (i = 0; i < tokenCount; i ++)
    {
        commandLineFile << tokens [i] << endl;
    }
    commandLineFile.close ();
    if (sigqueue (HALosPid, SIGRTMIN, dummyValue) == -1)
    {
        cout << "HALshell: command line signal not sent to HALos" << endl;
        exit (1);
    }

    return;
}

// "Built-in" Commands

void About (int tokenCount)
{
    if (tokenCount > 1)
    {
        cout << "HALshell: about does not require any arguments" << endl;
        return;
    }

    cout << endl;
    cout << "*********************************************" << endl;
    cout << "*               HALos v5.3.6                *" << endl;
    cout << "*                                           *" << endl;
    cout << "*  Copyright (c) 2018 Robert J. Hilderman.  *" << endl;
    cout << "*           All Rights Reserved.            *" << endl;
    cout << "*********************************************" << endl;
    cout << endl;

    return;
}

void BadCommand ()
{
    cout << "HALshell: MESSAGE = [command not executable]" << endl;

    return;
}

void Result (int tokenCount)
{
    if (tokenCount > 1)
    {
        cout << "HALshell: result does not require any arguments" << endl;
        return;
    }

    if (returnPid != "")
    {
        cout << "HALshell: ";
        cout << "PID = [" << returnPid << "] ";
        if (returnValue != "")
        {
            cout << "RETURN_VALUE = [" << returnValue << "] ";
        }
        if (returnMessage != "")
        {
            cout << "MESSAGE = [" << returnMessage << "]";
        }
        cout << endl;
        returnPid = "";
    }
    else if (returnPid == "") {
        //Lock mechanism
        int lock;
        struct flock key;
        // file declaration
        ifstream inFile;
        string return_pid;
        string return_value;
        string return_message;
        //Lock mechanism (cont)
        key.l_type = F_WRLCK;
        key.l_whence = SEEK_SET;
        key.l_start = 0;
        key.l_len = 0;
        key.l_pid = getpid();
        lock = open("HALreturnStatusLock", O_WRONLY);
        fcntl (lock, F_SETLKW, &key);

        // File open and read
        inFile.open("HALosForHALshell");
        if (!inFile) {
            cout << "HALos: could not open file" << endl;
            return;
        }
        // There may be more than one background process 
        while (inFile) {
            getline(inFile, return_pid);
            getline(inFile, return_value);
            getline(inFile, return_message);
            if(return_pid != "") {
                cout << "HALshell: ";
                cout << "PID = [" << return_pid << "] ";
                cout << "RETURN_VALUE = [" << return_value << "]";
                cout << "MESSAGE = [" << return_message << "]";
                cout << endl;
            }
        }

        inFile.close();

        // Lock mechanism
        key.l_type = F_UNLCK;
        fcntl (lock, F_SETLK, &key);
        close(lock);
    }

    return;
}

void ShutdownAndRestart (string tokens [], int tokenCount)
{
    if (tokenCount > 1)
    {
        cout << "HALshell: " << tokens [0] << " does not require any arguments" << endl;
        return;
    }

    cout << endl;
    cout << "HALshell: terminating ..." << endl;
    system ("HALshellCleanup");
    usleep (SLEEP_DELAY);
    SendCommandLineToHALos (tokens, tokenCount);

    exit (0);
}

// Miscellaneous Functions and Procedures

bool IsInteger (string value)
{
    int i;

    if (value.length () == 0)
    {
        return false;
    }

    for (i = 0; i < value.length (); i ++)
    {
        if (i == 0 && value [i] == '-')
        {
            continue;
        }
        else if (!isdigit (value [i]))
        {
            return false;
        }
    }

    return true;
}

string itos (int i)
{
    stringstream s;

    s << i;

    return s.str ();
}


//*************************************************************
// Customed Functions implementation (for the assignment 1)
//*************************************************************

//******************************************************************
// Function : Change shell name
// Pre : shell name is determined by a file named shellname
// Post: the content of shellname is changed to the new argument entered in
//******************************************************************
void SetShellName(string tokens[], int tokenCount) {
	// Error handling when user enter more or less than one argument
	if (tokenCount != 2) {
		cout << "HALshell: the number of arguments for setshellname is incorrect" << endl;
		return;
	}

	// Open the file shellname, clear the old content and write new content
	ofstream out;
	out.open("shellname", std::ofstream::out | std::ofstream::trunc);

	// Error handling for file opening
	if(!out) {
		cout << "HALshell: shellname cannot be openned" << endl;
		return;
	}
	out << tokens [1];
	out.close();
	return;
}

//******************************************************************
// Function : Change the terminator
// Pre : the terminator is determined by a file named terminator
// Post: the content of terminator is changed to the new argument entered in
//******************************************************************
void SetTerminator(string tokens[], int tokenCount) {
	// Error handling when user enter more or less than one argument
	if (tokenCount != 2) {
		cout << "HALshell: the number of arguments for setterminator is incorrect" << endl;
		return;
	}

	// Open the file terminator, clear its content and write new content
	ofstream out;
	out.open("terminator", std::ofstream::out | std::ofstream::trunc);

	// Error handling for file opening
	if(!out) {
		cout << "HALshell: terminator cannot be openned" << endl;
		return;
	}

	out << tokens [1];
	out.close();
	return;
}

//****************************************************************
// Function : Change the history size
// Pre : history size is determined by a file named historysize
// Post: the content of historysize is changed to new size which was entered in
//****************************************************************
void SetHistorySize(string tokens[], int tokenCount) {
	// Error handling when user enter more or less than one argument
	if (tokenCount != 2) {
		cout << "HALshell: the number of arguments for sethistorysize is incorrect" << endl;
		return;
	}
	// Error handling when user enter something which is not an integer
	char *temp; // char pointer to the character after the number (will be used in strtol)
	// User strtol to set up temp
	strtol(tokens[1].c_str(), &temp, 10);
	// Return message if the argument is not an integer (temp points to something other than 0)
	if (*temp != 0) {
		cout << "HALshell: the argument format is incorrect (must be an integer)" << endl;
		return;
	}

	// Open the file and write new content over its old one
	ofstream out;
	out.open("historysize", std::ofstream::out | std::ofstream::trunc);

	// Error handling for file opening 
	if(!out) {
		cout << "HALshell: historysize cannot be openned" << endl;
		return;
	}

	out << tokens[1];
	out.close();
	// Convert size to integer
	stringstream ss(tokens[1]);
	int newSize;
	ss >> newSize;
	// Update history size
	historyTable.changeSize(newSize);
	// truncate history if the size is smaller than the current items on the table
	historyTable.truncate();
	return;
}

//*************************************************************
// Function : Show the history size
// Pre : history size is determined by the file historysize
// Post: display the message showing history size on the screen
//*************************************************************
void ShowHistorySize(int tokenCount) {
	// Error handling if user enter some arguments
	if(tokenCount != 1) {
		cout << "HALshell: showhistorysize does not require any arguments" << endl;
		return;
	}

	// Open historysize file and read in the data
	int historySize;
	ifstream in;
	in.open("historysize");

	// Error handling for file opening
	if(!in) {
		cout << "HALshell: historysize cannot be opened" << endl;
		return;
	}

	in >> historySize;

	// Display the message
	cout << "HALshell: historysize = " << historySize << endl;
	in.close();

	return;

}

//************************************************************
// Function : Show the history table
// Pre : history has been initialized
// Post: History table is displayed on the screen
//************************************************************
void ShowHistory(int tokenCount) {
    if (tokenCount != 1) {
        cout << "HALshell: showhistory does not require any arguments" << endl;
        return;
    }
    historyTable.showHistory();
}

//************************************************************
// Function : Access the previous commands from the history table
// Pre : history table has been initialized
// Post: the old command is executed
//************************************************************
void AccessHistory(string tokens[], int tokenCount) {

    Node* command; // Pointer to a node

    if (tokenCount > 2) {
        cout << "HALshell: the number of arguments is incorrect" << endl;
        return;
    }
    else if (tokenCount == 1) {
        // Execute the most recent command (which is the last one in the queue)
        command = historyTable.ExecuteCommand(historyTable.getCounter() - 1);
        ProcessCommand(command->data, command->tokenCounter);
    }
    else {
        // Error handling if user enter something which is not an integer
        char* temp;
        strtol(tokens[1].c_str(), &temp, 10);
        // Return message if the argument is not an integer (temp points to something other than 0)
        if (*temp != 0) {
            cout << "HALshell: the argument format is incorrect (must be an integer)" << endl;
            return;
        }

        // Conver the second argument to integer
        stringstream ss(tokens[1]);
        int index;
        ss >> index;

        // if the index is bigger than history size, execute the most recent command
        if(index > historyTable.getCounter()) {
            command = historyTable.ExecuteCommand(historyTable.getCounter() - 1);
            ProcessCommand(command->data, command->tokenCounter);
        }
        // error handling if index is less than 0
        else if (index < 0) {
            cout << "HALshell: the argument is incorrect" << endl;
            return;
        }
        else {
            command = historyTable.ExecuteCommand(historyTable.getCounter() - index);
            ProcessCommand(command->data, command->tokenCounter);
        }
    }
}

//**************************************************
// Function : setting new name size
// Pre : newnamesize with default value 10
// Post: newnamesize is updated based on user input
//**************************************************
void SetNewNameSize(string tokens[], int tokenCount) {
	if (tokenCount != 2) {
		cout << "HALshell: the number of arguments for setnewnamesize is incorrect" << endl;
		return;
	}
	// Error handling when user enter something which is not an integer
	char *temp; // char pointer to the character after the number (will be used in strtol)
	// User strtol to set up temp
	strtol(tokens[1].c_str(), &temp, 10);
	// Return message if the argument is not an integer (temp points to something other than 0)
	if (*temp != 0) {
		cout << "HALshell: the argument format is incorrect (must be an integer)" << endl;
		return;
	}

	// Open the file and write new content over its old one
	ofstream out;
	out.open("newnamessize", std::ofstream::out | std::ofstream::trunc);

	// Error handling for file opening 
	if(!out) {
		cout << "HALshell: newnamessize cannot be openned" << endl;
		return;
	}
	// Update newnamesiz file
	out << tokens[1];
	out.close();

	// Convert size to integer
	stringstream ss(tokens[1]);
	int newSize;
	ss >> newSize;
	// Update newnames size
	newnameList.setSize(newSize);
	// truncate newnames list if size is smaller than current number of items
	newnameList.truncate();
	return;
}

//*****************************************************
// Function : show newname size in the file newnamesize
// Pre : newnamesize file with value in it
// Post: display the content of newnamesize
//*****************************************************
void ShowNewNameSize(int tokenCount) {
	// Error handling if user enter some arguments
	if(tokenCount != 1) {
		cout << "HALshell: shownewnamesize does not require any arguments" << endl;
		return;
	}

	// Open newnamesize file and read in the data
	int newnameSize;
	ifstream in;
	in.open("newnamessize");

	// Error handling for file opening
	if(!in) {
		cout << "HALshell: newnamessize cannot be opened" << endl;
		return;
	}

	in >> newnameSize;

	// Display the message
	cout << "HALshell: newnamessize = " << newnameSize << endl;
	in.close();

	return;
}

//****************************************************
// Function : add new name into newnameList
// Pre : list has been initialized
// Post: new name is added into the list
//****************************************************
void SetNewName(string tokens[], int tokenCount) {
    if (tokenCount < 3) {
        cout << "HALshell: the number of arguments for setnewname is incorrect" << endl;
        return;
    }
    if(!newnameList.insert(tokens, tokenCount)) {
        cout << "HALshell: newnameList is full or the size is 0" << endl;
    }
    return;
}

//*****************************************************
// Function : display new name list
// Pre : list has been initialized
// Post: each elememt is displayed 
//*****************************************************
void ShowNewName(int tokenCount) {
    if (tokenCount != 1) {
        cout << "HALshell: shownewname does not require any arguments" << endl;
        return;
    }
    newnameList.display();
}

//****************************************************
// Function : remove an element from newnamelist based on new name
// Pre : list has been initialized
// Post: if the element is found, it will be removed
//****************************************************
void RemoveNewName(string tokens[], int tokenCount) {
	// Error handling
    if (tokenCount != 2) {
        cout << "HALshell: the number of arguments for removenewname is incorrect" << endl;
        return;
    }
    // Display a message if new name is not on the list
    if(!newnameList.remove(tokens[1]))
    	cout << "HALshell: name is not on newnames list" << endl;
}

//****************************************************
// Function : write newname list into a file
// Pre : list has been initialized
// Post: list is written into a file
//****************************************************
void WriteNewName(string tokens[], int tokenCount) {
	// Error handling
	if (tokenCount != 2) {
		cout << "HALshell: the number of arguments for writenewnames is incorrect" << endl;
		return;
	}
	ofstream output;
	output.open(tokens[1].c_str());
	// Output file stream error handling
	if(!output) {
		cout << "HALshell: " << tokens[1] << "cannot be opened" << endl;
		return;
	}
	// Write into file stream
	newnameList.write(output);
	output.close();
}

//********************************************************
// Function : read newname list from a file into the list
// Pre : list has been initialized
// Post: list's old content is deleted, and list is updated
//********************************************************
void ReadNewName(string tokens[], int tokenCount) {
	// Error handling
	if (tokenCount != 2) {
		cout << "HALshell: the number of arguments for readnewname is incorrect" << endl;
		return;
	}
	ifstream input;
	input.open(tokens[1].c_str());
	// Input file stream error handling
	if (!input) {
		cout << "HALshell: " << tokens[1] << " cannot be open" << endl;
		return;
	}
	// Read from file stream
	newnameList.read(input);
	input.close();
}

//*****************************************************
// Function : restore shellname, terminator, historysize and newnamessize to default
// Pre : Pre-existed files
// Post: All values are set to default as described in the assignment
//*****************************************************
void RestoreDefaults(string tokens[], int tokenCount) {
	// Error handling
	if(tokenCount != 1) {
		cout << "HALshell: restoredefaults does not require any arguments" << endl;
		return;
	}
	ofstream out;
	// Restore shell name to default----------------------------------------
	out.open("shellname", std::ofstream::out | std::ofstream::trunc);
	// Error handling
	if (!out) 
		cout << "HALshell: shellname cannot be opened" << endl;
	else
		out << "HALshell";
	out.close();

	// Restore terminator to default----------------------------------------
	out.open("terminator", std::ofstream::out | std::ofstream::trunc);
	// Error handling
	if (!out)
		cout << "HALshell: terminator cannot be opened" << endl;
	else
		out << ">";
	out.close();

	// Restore historysize to default---------------------------------------
	out.open("historysize", std::ofstream::out | std::ofstream::trunc);
	// Error handling
	if (!out)
		cout << "HALshell: historysize cannot be opened" << endl;
	else 
		out << 10;
	out.close();

	// Restore newnamessize to default---------------------------------------
	out.open("newnamessize", std::ofstream::out | std::ofstream::trunc);
	// Error handling
	if (!out)
		cout << "HALshell: newnamessize cannot be opened" << endl;
	else
		out << 10;
	out.close();

	// Update history table and newnames list if new size is smaller than current counter
	historyTable.truncate();
	newnameList.truncate();

}

//*************************************************************************
// Function : execute a command based on its substituted name(s)
// Pre : new names list has been initialized
// Post: the pre-defined command is executed
//*************************************************************************
void NewNameSubstitution(Alias *newCommand, string tokens[], int tokenCount) {
 	
	// if there is argument(s) after substituted name, add them to newCommand
	if (tokenCount != 1) {
		for (int i = 1; i < tokenCount; i++) {
			newCommand->command[newCommand->tokenCounter] = tokens[i];
			// Increase tokenCounter
			newCommand->tokenCounter++;
		}
	}
    ProcessCommand(newCommand->command, newCommand->tokenCounter);
    delete newCommand;
}






















