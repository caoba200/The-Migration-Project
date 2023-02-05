//
// HALshell.h
//
// Copyright (c) 2018 Robert J. Hilderman.
// All Rights Reserved.
//

#define HAL_SHELL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

using namespace std;

#ifndef HAL_GLOBALS_H
    #include "HALglobals.h"
#endif

#ifndef HAL_SIGNALS_H
    #include "HALsignals.h"
#endif

// New include (for the Assignment 1)
#include "CommandHistoryTable.h"
#include "NewNameList.h"

// Global Variables

pid_t HALosPid;
string returnPid = "";
string returnValue = "";
string returnMessage = "";

//*****************************************************************
// NEW GLOBAL VARIABLES FOR THE ASSIGNMENT
//******************************************************************
// Initialize the command history table with the default value is 10
HistoryTable historyTable(10);

// Initialize the new name list with the default value is 10
NewNameList newnameList(10);

//******************************************************************

// The "Shell"

void HALshell ();
int GetCommand (string tokens []);
int TokenizeCommandLine (string tokens [], string commandLine);
void ProcessCommand (string tokens [], int tokenCount);
void PrintReturnStatus ();

// The "Communication Media"

void GetMessageFromHALos ();
void SendCommandLineToHALos (string tokens [], int tokenCount);

// "Built-in" Commands

void About (int tokenCount);
void BadCommand ();
void Result (int tokenCount);
void ShutdownAndRestart (string tokens [], int tokenCount);
//void RestoreDefaults (string tokens [], int tokenCount, string history [], int &historySize, string newNames [], string oldNames [], int &newNamesSize);

//****************************************************************
// Customed Commands (for the assignment 1)
//****************************************************************

// Procedure for the command "setshellname"
void SetShellName(string tokens[], int tokenCount);

// Procedure for the command "setterminator"
void SetTerminator(string tokens[], int tokenCount);

// Procedure for the command "sethistorysize"
void SetHistorySize(string tokens[], int tokenCount);

// Procedure for the command "showhistorysize"
void ShowHistorySize(int tokenCount);

// Procedure for the command "showhistory"
void ShowHistory(int tokenCount);

// Procedure for the command "! | <n>"
void AccessHistory(string tokens[], int tokenCount);

// Procedure for the command "setnewnamesize"
void SetNewNameSize(string tokens[], int tokenCount);

// Procedure for the command "shownewnamesize"
void ShowNewNameSize(int tokenCount);

// Procedure for the command "setnewname"
void SetNewName(string tokens[], int tokenCount);

// Procedure for the command "shownewname"
void ShowNewName(int tokenCount);

// Procedure for the command "removenewname"
void RemoveNewName(string tokens[], int tokenCount);

// Procedure for the command "writenewnames"
void WriteNewName(string tokens[], int tokenCount);

// Procedure for the command "readnewnames"
void ReadNewName(string tokens[], int tokenCount);

// Procedure for the command "restoredefaults"
void RestoreDefaults(string tokens[], int tokenCount);

// Procedure for new name substitution
void NewNameSubstitution(Alias* newName, string tokens[], int tokenCount);

// Miscellaneous Functions and Procedures

bool IsInteger (string value);
string itos (int i);

/*

  #####
 #     #
#       # THE CODE THAT FOLLOWS SHOULD NOT BE CHANGED IN ANY WAY!
# STOP! #
#       # IF YOUR O/S IS NOT WORKING, YOU WON'T FIND THE PROBLEM HERE!
 #     #
  #####

*/

void Initialize ();
bool CheckForCommand ();
void Wait ();

static volatile sig_atomic_t commandHandled = 0;
static volatile sig_atomic_t cullProcess = 0;

int main ()
{
    Initialize ();
    HALshell ();

    return 0;
}

void Initialize ()
{
    cout << "HALos: HALshell OK" << endl;
    usleep (SLEEP_DELAY);

    cout << "HALshell: initializing ..." << endl;
    if ((sigemptyset (&interruptMask) == -1) ||
        (sigaddset (&interruptMask, SIGRTMIN) == -1))
    {
        cout << "HALshell: unable to initialize signal mask" << endl;
        exit (1);
    }
    act.sa_sigaction = &SignalHandler;
    act.sa_mask = interruptMask;
    act.sa_flags = SA_SIGINFO;
    if ((sigemptyset (&act.sa_mask) == -1) ||
        (sigaction (SIGRTMIN, &act, NULL) == -1) ||
        (sigaction (SIGINT, &act, NULL) == -1))
    {
        cout << "HALshell: unable to connect to HALos" << endl;
        exit (1);
    }
    usleep (SLEEP_DELAY);

    cout << endl;

    HALosPid = getppid ();

    return;
}

bool CheckForCommand ()
{
    if (cullProcess)
    {
        cullProcess = 0;
        cin.clear ();
        cout << "\b\b  \b\b";
        return false;
    }

    return true;
}

void Wait ()
{
    string tokens [MAX_COMMAND_LINE_ARGUMENTS];

    do
    {
        BlockSignals ("HALshell");
        if (cullProcess)
        {
            cullProcess = 0;
            tokens [0] = "cull";
            SendCommandLineToHALos (tokens, 1);
            cin.clear ();
            cout << endl;
        }
        else if (commandHandled)
        {
            commandHandled = 0;
            break;
        }
        UnblockSignals ("HALshell");
    } while (1);

    return;
}

static void SignalHandler (int signalNo, siginfo_t* info, void* context)
{
    if (signalNo == SIGRTMIN)
    {
        if (info -> si_pid == HALosPid)
        {
            commandHandled = 1;
        }
    }
    else if (signalNo == SIGINT)
    {
        cullProcess = 1;
    }
}
