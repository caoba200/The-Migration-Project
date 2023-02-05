//
// HALos.cpp
//
// Copyright (c) 2018 Robert J. Hilderman.
// All Rights Reserved.
//

#include "HALos.h"
#include <fcntl.h>

// The "Operating System"

void HALos ()
{
    string type;
    string command;
    string arguments [MAX_COMMAND_LINE_ARGUMENTS];

    do
    {
        BlockSignals ("HALos");
        if (messageFromHALshell) // command entered in HALshell
        {
            messageFromHALshell = 0;
            command = GetMessageFromHALshell (arguments, type);
            HandleCommand (command, arguments, type);
        }
        else if (messageFromHAL9000)
        {
            messageFromHAL9000 = 0;
            GetMessageFromHAL9000 ();
            if (HAL9000Message.type == "INTERRUPT") // from cpu
            {
                HandleHAL9000Interrupt ();
            }
            else if (HAL9000Message.type == "SYSTEM_CALL") // from running process
            {
                HandleSystemCall ();
            }
            ClearMessageParameters (HAL9000Message);
        }
        else if (messageFromHALkeyboardDriver) // "INTERRUPT" from keyboard driver
        {
            messageFromHALkeyboardDriver = 0;
            GetMessageFromHALkeyboardDriver ();
            HandleHALkeyboardDriverInterrupt ();
            ClearMessageParameters (HALkeyboardDriverMessage);
        }
        else if (messageFromHALdisplayDriver) // "INTERRUPT" from display driver
        {
            messageFromHALdisplayDriver = 0;
            GetMessageFromHALdisplayDriver ();
            HandleHALdisplayDriverInterrupt ();
            ClearMessageParameters (HALdisplayDriverMessage);
        }
        else if (messageFromHALdiskDriver) // "INTERRUPT" from disk driver
        {
            messageFromHALdiskDriver = 0;
            GetMessageFromHALdiskDriver ();
            HandleHALdiskDriverInterrupt ();
            ClearMessageParameters (HALdiskDriverMessage);
        }
        RunCpuScheduler ();
        UnblockSignals ("HALos");
    } while (1);

    return;
}

void HandleCommand (string command, string arguments [], string type)
{
    string result;

    if (command == "shutdown" || command == "restart")
    {
        ShutdownAndRestart (command, arguments);
        // never returns!
    }
    else if (command == "cull")
    {
        Cull (command, arguments);
    }
    else if (command == "compile")
    {
        Compile (arguments);
    }
    else if (command == "stopcpuscheduler")
    {
        StopCpuScheduler ();
    }
    else if (command == "startcpuscheduler")
    {
        StartCpuScheduler ();
    }
    else
    {
        HandleNewProcess (command, arguments, type);
    }
     
    return;
}

void HandleNewProcess (string command, string arguments [], string type)
{
    int i;
    int j;
    processDescriptor process;
    struct stat fileStatusBuffer;
    size_t fileExtensionPosition;

    if (type == "FOREGROUND_PROCESS" && !cpuScheduler)
    {
        SendReturnStatusToHALshell ("", "error", "foreground process not created - cpu scheduler stopped");
        return;
    }

    fileExtensionPosition = command.find (".halx");
    if (fileExtensionPosition == string::npos)
    {
        command = command + ".halx";
    }
    else if (command.substr (fileExtensionPosition, 5) != command.substr ((command.length () - 5), 5))
    {
        command = command + ".halx";
    }

    if (command [0] == '/')
    {
        command = command.substr (1);
    }

    if (!stat (command.c_str (), &fileStatusBuffer))
    {
        process = NullProcess ();
        process.pid = itos (nextPid);
        process.type = type;
        process.action = "EXECUTE_NEW_PROCESS";
        process.command = command;
        process.priority = NOT_A_PRIORITY_PROCESS;
        i = 0;
        j = -1;
        while (i < MAX_COMMAND_LINE_ARGUMENTS)
        {
            if (arguments [i].length () > 0)
            {
                if (arguments [i].substr (0, 9) == "priority=")
                {
                    process.priority = atoi (arguments [i].substr (9).c_str ());
                }
                else
                {
                    j ++;
                    process.arguments [j] = arguments [i];
                }
            }
            i ++;
        }
        process.direction = "DOWN";
        process.interruptCounter = cpuSchedulingPolicies [process.queueNo].interruptsUntilMoveDown;
        if (ProcessImageToFile (process.pid, process.command))
        {
            readyQueue.Enqueue (process);
            if (type == "BACKGROUND_PROCESS")
            {
                SendReturnStatusToHALshell (itos (nextPid), "", "background process created");
            }
            nextPid ++;
        }
        else
        {
            SendReturnStatusToHALshell ("", "error", "process not created");
        }
    }
    else
    {
        SendReturnStatusToHALshell ("", "", "command not found");
    }

    return;
}

bool ProcessImageToFile (string pid, string command)
{
    ifstream programFile;
    ofstream processImageFile;
    string processImageFileName;
    string programLine;
    size_t foundRunningTime;
    size_t foundPid;

    foundRunningTime = string::npos;
    foundPid = string::npos;

    programFile.open (command.c_str ());
    if (!programFile)
    {
        return false;
    }

    processImageFileName = pid + "_backingstore";
    processImageFile.open (processImageFileName.c_str ());
    if (!processImageFile)
    {
        programFile.close ();
        return false;
    }

    getline (programFile, programLine);
    while (programFile)
    {
        programLine = InitializePidInProcessImage (pid, programLine, foundPid, foundRunningTime);
        processImageFile << programLine << endl;
        getline (programFile, programLine);
    }

    programFile.close ();
    processImageFile.close ();

    return true;
}

string InitializePidInProcessImage (string pid, string programLine, size_t &foundPid, size_t &foundRunningTime)
{
    if (foundRunningTime == string::npos)
    {
        foundRunningTime = programLine.find ("RUNNING_TIME :");
        if (foundRunningTime != string::npos)
        {
            programLine = programLine.substr (0, foundRunningTime);
            programLine = programLine + "RUNNING_TIME :0";
        }
    }
    else if (foundPid == string::npos)
    {
        foundPid = programLine.find ("PID :");
        if (foundPid != string::npos)
        {
            programLine = programLine.substr (0, foundPid);
            programLine = programLine + "PID :" + pid;
        }
    }

    return programLine;
}
void HandleHAL9000Interrupt ()
{
    if (HAL9000Message.parameter1 == "QUANTUM_EXPIRED")
    {
        SetSystemCallParameters (cpuProcess, "", "", "", "", "" ,"");
        // Step 16 -------------------------------------------------------
        cpuProcess.runningTime = cpuProcess.runningTime + atoi(HAL9000Message.parameter7.c_str());
        cpuProcess.timerInterruptCounter++;
        cpuProcess.action = "CONTINUE_EXECUTING_PROCESS";
        readyQueue.Enqueue (cpuProcess);
    }
    else if (HAL9000Message.parameter1 == "PROCESS_DONE")
    {
        // Step 21 --------------------------------------------------------
        string timingResults = "creation time =";
        // Step 21 : Build up the string timingResults
        timingResults += itos(cpuProcess.creationTime);
        timingResults += " ";
        cpuProcess.runningTime = cpuProcess.runningTime + atoi(HAL9000Message.parameter7.c_str());
        timingResults += itos(cpuProcess.runningTime);
        timingResults += " ";
        timingResults += HAL9000Message.parameter6;
        timingResults += " ";
        timingResults += itos(cpuProcess.timerInterruptCounter);
        timingResults += " ";
        timingResults += itos(cpuProcess.systemCallInterruptCounter);

        cpuProcess.action = "PROCESS_DONE";
        cpuProcess.partitionNo = UpdatePartitionTable (cpuProcess.pid, cpuProcess.action);
        remove ((cpuProcess.pid + "_backingstore").c_str ());
        if (cpuProcess.type == "FOREGROUND_PROCESS")
        {
            SendReturnStatusToHALshell (HAL9000Message.parameter2, HAL9000Message.parameter3, timingResults);
        }
        if (cpuProcess.type == "BACKGROUND_PROCESS"){
            SaveReturnStatusForHALshell (HAL9000Message.parameter2, HAL9000Message.parameter3, timingResults);
        }
    }

    cpuProcess = NullProcess ();

    return;
}

void HandleSystemCall ()
{
    fileDescriptor file;
    // Step 16 -------------------------------------------------------------
    cpuProcess.runningTime = cpuProcess.runningTime + atoi(HAL9000Message.parameter7.c_str());
    cpuProcess.systemCallInterruptCounter++;
    cpuProcess.action = "CONTINUE_EXECUTING_PROCESS";

    if (HAL9000Message.parameter1 == "OPEN")
    {
        if (HAL9000Message.parameter3 == "keyboard" || HAL9000Message.parameter3 == "display")
        {
            SetSystemCallParameters (cpuProcess, HAL9000Message.parameter1, HAL9000Message.parameter3, HAL9000Message.parameter5, "", "", "FILE_OPEN_OK");
            readyQueue.Enqueue (cpuProcess);
        }
        else // (HAL9000Message.parameter3 == some other file name)
        {
            SetSystemCallParameters (cpuProcess, HAL9000Message.parameter1, HAL9000Message.parameter3, HAL9000Message.parameter4, HAL9000Message.parameter5, "", "");
            if (diskProcess.pid == itos (-1) && diskQueue.IsEmpty ())
            {
                diskProcess = cpuProcess;
                SendMessageToHALdiskDriver (diskProcess.pid, diskProcess.systemCall, diskProcess.systemCallParameter1, diskProcess.systemCallParameter3, "", "");
            }
            else
            {
                diskQueue.Enqueue (cpuProcess);
            }
        }
    }
    else if (HAL9000Message.parameter1 == "READ")
    {
        if (HAL9000Message.parameter3 == "keyboard")
        {
            SetSystemCallParameters (cpuProcess, HAL9000Message.parameter1, "", "", "", "", "");
            if (keyboardProcess.pid == itos (-1) && keyboardQueue.IsEmpty ())
            {
                keyboardProcess = cpuProcess;
                SendMessageToHALkeyboardDriver (keyboardProcess.pid, keyboardProcess.systemCall);
            }
            else
            {
                keyboardQueue.Enqueue (cpuProcess);
            }
        }
        else // (HAL9000Message.parameter3 == some other file name)
        {
            SetSystemCallParameters (cpuProcess, HAL9000Message.parameter1, HAL9000Message.parameter3, HAL9000Message.parameter4, "", "", "");
            if (diskProcess.pid == itos (-1) && diskQueue.IsEmpty ())
            {
                cpuProcess.fileTable.Find (HAL9000Message.parameter3, HAL9000Message.parameter4);
                file = cpuProcess.fileTable.Read ();
                diskProcess = cpuProcess;
                SendMessageToHALdiskDriver (diskProcess.pid, diskProcess.systemCall, diskProcess.systemCallParameter1, "input", file.markerPosition, "");
            }
            else
            {
                diskQueue.Enqueue (cpuProcess);
            }
        }
    }
    else if (HAL9000Message.parameter1 == "WRITE" || HAL9000Message.parameter1 == "NEWLINE")
    {
        if (HAL9000Message.parameter3 == "display")
        {
            SetSystemCallParameters (cpuProcess, HAL9000Message.parameter1, HAL9000Message.parameter5, "", "", "", "");
            if (displayProcess.pid == itos (-1) && displayQueue.IsEmpty ())
            {
                displayProcess = cpuProcess;
                SendMessageToHALdisplayDriver (displayProcess.pid, displayProcess.systemCall, displayProcess.systemCallParameter1);
            }
            else
            {
                displayQueue.Enqueue (cpuProcess);
            }
        }
        else // (HAL9000Message.parameter3 == some file name)
        {
            SetSystemCallParameters (cpuProcess, HAL9000Message.parameter1, HAL9000Message.parameter5, HAL9000Message.parameter3, HAL9000Message.parameter4, "", "");
            if (diskProcess.pid == itos (-1) && diskQueue.IsEmpty ())
            {
                cpuProcess.fileTable.Find (HAL9000Message.parameter3, HAL9000Message.parameter4);
                file = cpuProcess.fileTable.Read ();
                diskProcess = cpuProcess;
                SendMessageToHALdiskDriver (diskProcess.pid, diskProcess.systemCall, diskProcess.systemCallParameter2, "output", "", diskProcess.systemCallParameter1);
            }
            else
            {
                diskQueue.Enqueue (cpuProcess);
            }
        }
    }
    else if (HAL9000Message.parameter1 == "CLOSE")
    {
        if (!(HAL9000Message.parameter3 == "keyboard") && !(HAL9000Message.parameter3 == "display"))
        {
            cpuProcess.fileTable.Find (HAL9000Message.parameter3, HAL9000Message.parameter4);
            cpuProcess.fileTable.Delete ();
        }
        SetSystemCallParameters (cpuProcess, "", "", "", "", "", "FILE_CLOSE_OK");
        readyQueue.Enqueue (cpuProcess);
    }

    cpuProcess = NullProcess ();

    return;
}

void HandleHALkeyboardDriverInterrupt ()
{
    SetSystemCallParameters (keyboardProcess, "", "", "", "", HALkeyboardDriverMessage.parameter3, HALkeyboardDriverMessage.parameter4);
    readyQueue.Enqueue (keyboardProcess);

    keyboardProcess = NullProcess ();

    if (!keyboardQueue.IsEmpty ())
    {
        keyboardProcess = keyboardQueue.Dequeue ();
        SendMessageToHALkeyboardDriver (keyboardProcess.pid, keyboardProcess.systemCall);
    }

    return;
}

void HandleHALdisplayDriverInterrupt ()
{
    SetSystemCallParameters (displayProcess, "", "", "", "", "", "");
    readyQueue.Enqueue (displayProcess);

    displayProcess = NullProcess ();

    if (!displayQueue.IsEmpty ())
    {
        displayProcess = displayQueue.Dequeue ();
        SendMessageToHALdisplayDriver (displayProcess.pid, displayProcess.systemCall, displayProcess.systemCallParameter1);
    }

    return;
}

void HandleHALdiskDriverInterrupt ()
{
    fileDescriptor file;

    if (diskProcess.systemCall == "OPEN")
    {
        if (HALdiskDriverMessage.parameter5 == "FILE_OPEN_OK")
        {
            if (!diskProcess.fileTable.Find (diskProcess.systemCallParameter1, diskProcess.systemCallParameter2))
            {  
                diskProcess.fileTable.Insert (diskProcess.systemCallParameter1, diskProcess.systemCallParameter2, diskProcess.systemCallParameter3);
            }
            else 
            {
                HALdiskDriverMessage.parameter5 = "FILE_ALREADY_OPEN";
            }
        }
        SetSystemCallParameters (diskProcess, "", "", "", "", "", HALdiskDriverMessage.parameter5);
    }
    else if (diskProcess.systemCall == "READ")
    {
        diskProcess.fileTable.Find (diskProcess.systemCallParameter1, diskProcess.systemCallParameter2);
        diskProcess.fileTable.Write (HALdiskDriverMessage.parameter3);
        SetSystemCallParameters (diskProcess, "", "", "", "", HALdiskDriverMessage.parameter4, HALdiskDriverMessage.parameter5);
    }
    else if (diskProcess.systemCall == "WRITE" || diskProcess.systemCall == "NEWLINE")
    {
        SetSystemCallParameters (diskProcess, "", "", "", "", "", HALdiskDriverMessage.parameter5);
    }
    readyQueue.Enqueue (diskProcess);

    diskProcess = NullProcess ();

    if (!diskQueue.IsEmpty ())
    {
        diskProcess = diskQueue.Dequeue ();
        if (diskProcess.systemCall == "OPEN")
        {
            SendMessageToHALdiskDriver (diskProcess.pid, diskProcess.systemCall, diskProcess.systemCallParameter1, diskProcess.systemCallParameter3, "", "");
        }
        else
        {
            if (diskProcess.systemCall == "READ")
            {
                diskProcess.fileTable.Find (diskProcess.systemCallParameter1, diskProcess.systemCallParameter2);
            }
            else // (diskProcess.systemCall == "WRITE" || "NEWLINE")
            {
                diskProcess.fileTable.Find (diskProcess.systemCallParameter2, diskProcess.systemCallParameter3);
            }              
            file = diskProcess.fileTable.Read ();
            if (file.mode == "input")
            {
                SendMessageToHALdiskDriver (diskProcess.pid, diskProcess.systemCall, file.name, file.mode, file.markerPosition, "");
            }
            else
            {
                SendMessageToHALdiskDriver (diskProcess.pid, diskProcess.systemCall, file.name, file.mode, "", diskProcess.systemCallParameter1);
            }
        }
    }

    return;
}

void SetSystemCallParameters (processDescriptor &process, string systemCall, string systemCallParameter1, string systemCallParameter2, string systemCallParameter3, string systemCallBuffer, string systemCallResult)
{
    process.systemCall = systemCall;
    process.systemCallParameter1 = systemCallParameter1;
    process.systemCallParameter2 = systemCallParameter2;
    process.systemCallParameter3 = systemCallParameter3;
    process.systemCallBuffer = systemCallBuffer;
    process.systemCallResult = systemCallResult;

    return;
}

void RunCpuScheduler ()
{
    if (!cpuScheduler)
    {
        return;
    }

    if (cpuProcess.pid == itos (-1))
    {
        if (readyQueue.IsEmpty ())
        {
            NoOp;
        }
        else
        {
            cpuProcess = readyQueue.Dequeue ();
            if (cpuProcess.action == "CONTINUE_EXECUTING_PROCESS")
            {
                cpuProcess = readyQueue.SetQueueNo (cpuProcess);
            }
            cpuProcess.quantumLength = cpuSchedulingPolicies [cpuProcess.queueNo].quantumLengthMultiplier * QUANTUM_LENGTH;
            cpuProcess.quantumLength = cpuProcess.quantumLength + RandomQuantumLengthAdjustment (cpuProcess.quantumLength);
            cpuProcess.partitionNo = UpdatePartitionTable (cpuProcess.pid, cpuProcess.action);
            SendMessageToHAL9000 (cpuProcess);
        }
    }

    return;
}

void StopCpuScheduler ()
{
    if (!cpuScheduler)
    {
        SendReturnStatusToHALshell (itos (nextPid), "ok", "cpu scheduler already stopped");
        nextPid ++;
    }
    else
    {
        cpuScheduler = false;
        SendReturnStatusToHALshell (itos (nextPid), "ok", "cpu scheduler stopped");
        nextPid ++;
    }

    return;
}

void StartCpuScheduler ()
{
    if (cpuScheduler)
    {
        SendReturnStatusToHALshell (itos (nextPid), "ok", "cpu scheduler already started");
        nextPid ++;
    }
    else
    {
        cpuScheduler = true;
        SendReturnStatusToHALshell (itos (nextPid), "ok", "cpu scheduler started");
        nextPid ++;
    }

    return;
}

// The "Communication Media"

string GetMessageFromHALshell (string arguments [], string &type)
{
    ifstream commandLineFile;
    string command;
    int i;

    for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i ++)
    {
        arguments [i] = "";
    }

    commandLineFile.open ("HALshellToHALos");
    if (!commandLineFile)
    {
        cout << "HALos: connection to HALshell failed" << endl;
        exit (1);
    }
    if (getline (commandLineFile, command))
    {
        i = 0;
        while (getline (commandLineFile, arguments [i]))
        {
            i ++;
        }
    }
    else
    {
        cout << "HALos: command received from HALshell corrupted" << endl;
        exit (1);
    }
    commandLineFile.close ();

    type = "FOREGROUND_PROCESS";
    if (i > 0)
    {
        i --;
        if (arguments [i] == "-")
        {
            type = "BACKGROUND_PROCESS";
            arguments [i] = "";
        }
    }

    return command;
}

void SendReturnStatusToHALshell (string pid, string returnValue, string message)
{    
    ofstream returnStatusFile;
    union sigval dummyValue;
   
    returnStatusFile.open ("HALosToHALshell");
    if (!returnStatusFile)
    {
        cout << "HALos: unable to initialize return status buffer" << endl;
        exit (1);
    }

    returnStatusFile << pid << endl;
    returnStatusFile << returnValue << endl;
    returnStatusFile << message << endl;
    returnStatusFile.close ();

    if (sigqueue (HALshellPid, SIGRTMIN, dummyValue) == -1)
    {
        cout << "HALos: return code signal not sent to HALshell" << endl;
        exit (1);
    }

    return;
}

// Step 23 -------------------------------------------------------------------------------
void SaveReturnStatusForHALshell (string pid, string returnValue, string message) {
    // Lock mechanism
    int lock;
    struct flock key;
    // file variable declaration
    ofstream returnStatusFile;

    // Lock mechanism continuous
    key.l_type = F_WRLCK;
    key.l_whence = SEEK_SET;
    key.l_start = 0;
    key.l_len = 0;
    key.l_pid = getpid();
    lock = open("HALreturnStatusLock", O_WRONLY);
    fcntl (lock, F_SETLKW, &key);

    // File open and write
    returnStatusFile.open ("HALosForHALshell", std::ofstream::out | std::ofstream::app);
    if (!returnStatusFile) {
        cout << "HALos: unable to initialize return status buffer" << endl;
        exit(1);
    }
    returnStatusFile << pid << endl;
    returnStatusFile << returnValue << endl;
    returnStatusFile << message << endl;
    returnStatusFile.close();

    // Lock mechanism continuous
    key.l_type = F_UNLCK;
    fcntl (lock, F_SETLK, &key);
    close (lock);

    return;

}

void GetMessageFromHAL9000 ()
{
    static int seqNo = 0;
    static string fileNamePrefix = "HAL9000ToHALos_";
    static string fileName;
    ifstream hal9000MessageFile;

    if (seqNo > 0)
    {
        remove (fileName.c_str ());
    }

    seqNo ++;
    fileName = fileNamePrefix + itos (seqNo);
    hal9000MessageFile.open (fileName.c_str ());
    if (!hal9000MessageFile)
    {
        cout << "HALos: connection to HAL9000 failed" << endl;
        exit (1);
    }

    getline (hal9000MessageFile, HAL9000Message.type);
    getline (hal9000MessageFile, HAL9000Message.parameter1);
    getline (hal9000MessageFile, HAL9000Message.parameter2);
    getline (hal9000MessageFile, HAL9000Message.parameter3);
    getline (hal9000MessageFile, HAL9000Message.parameter4);
    getline (hal9000MessageFile, HAL9000Message.parameter5);
    getline (hal9000MessageFile, HAL9000Message.parameter6);
    getline (hal9000MessageFile, HAL9000Message.parameter7);

    if (!hal9000MessageFile)
    {
        cout << "HALos: message not received from HAL9000" << endl;
        exit (1);
    }

    #ifdef HAL9000_MESSAGE_TRACE_ON
    {
        cout << endl;
        if (HAL9000Message.type == "EXECUTING_PROCESS_PAUSED" || HAL9000Message.type == "NO_EXECUTING_PROCESS")
        {
            cout << "HALos: received message from HAL9000 for pid = " << HAL9000Message.parameter1 << endl;
        }
        else // (HAL9000Message.type == "INTERRUPT" || HAL9000Message.type == "SYSTEM_CALL")
        {
            cout << "HALos: received message from HAL9000 for pid = " << HAL9000Message.parameter2 << endl;
        }
        cout << "    type = " << HAL9000Message.type << endl;
        cout << "    parameter1 = " << HAL9000Message.parameter1 << endl;
        cout << "    parameter2 = " << HAL9000Message.parameter2 << endl;
        cout << "    parameter3 = " << HAL9000Message.parameter3 << endl;
        cout << "    parameter4 = " << HAL9000Message.parameter4 << endl;
        cout << "    parameter5 = " << HAL9000Message.parameter5 << endl;
        cout << "    parameter6 = " << HAL9000Message.parameter6 << endl;
        cout << "    parameter7 = " << HAL9000Message.parameter7 << endl;
    }
    #endif

    hal9000MessageFile.close ();

    if (seqNo == INT_MAX)
    {
        seqNo = 1;
    }

    return;
}

void SendMessageToHAL9000 (processDescriptor process)
{
    static int seqNo = 0;
    static string fileNamePrefix = "HALosToHAL9000_";
    static string fileName;
    ofstream halOsMessageFile;
    int i;
    union sigval dummyValue;

    seqNo ++;
    fileName = fileNamePrefix + itos (seqNo);
    halOsMessageFile.open (fileName.c_str ());
    if (!halOsMessageFile)
    {
        cout << "HALos: unable to initialize HAL9000 message buffer" << endl;
        exit (1);
    }

    halOsMessageFile << process.action << endl;
    halOsMessageFile << process.pid << endl;
    halOsMessageFile << process.command << endl;
    for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i ++)
    {
        halOsMessageFile << process.arguments [i] << endl;
    }
    halOsMessageFile << process.systemCallBuffer << endl;
    halOsMessageFile << process.systemCallResult << endl;
    halOsMessageFile << process.quantumLength << endl;
    halOsMessageFile << process.partitionNo << endl;

    #ifdef HAL9000_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALos: sending message to HAL9000 for pid = " << process.pid << endl;
        cout << "    action = " << process.action << endl;
        cout << "    pid = " << process.pid << endl;
        cout << "    command = " << process.command << endl;
        cout << "    systemCallBuffer = " << process.systemCallBuffer << endl;
        cout << "    systemCallResult = " << process.systemCallResult << endl;
        cout << "    quantumLength = " << process.quantumLength << endl;
        cout << "    partitionNo = " << process.partitionNo << endl;
    }
    #endif

    halOsMessageFile.close ();

    if (sigqueue (HAL9000Pid, SIGRTMIN, dummyValue) == -1)
    {
        cout << "HALos: message not sent to HAL9000" << endl;
        exit (1);
    }

    if (seqNo == INT_MAX)
    {
        seqNo = 1;
    }

    return;
}

void GetMessageFromHALkeyboardDriver ()
{
    ifstream halKeyboardDriverMessageFile;

    halKeyboardDriverMessageFile.open ("HALkeyboardDriverToHALos");
    if (!halKeyboardDriverMessageFile)
    {
        cout << "HALos: connection to HALkeyboardDriver failed" << endl;
        exit (1);
    }

    getline (halKeyboardDriverMessageFile, HALkeyboardDriverMessage.type);
    getline (halKeyboardDriverMessageFile, HALkeyboardDriverMessage.parameter1);
    getline (halKeyboardDriverMessageFile, HALkeyboardDriverMessage.parameter2);
    getline (halKeyboardDriverMessageFile, HALkeyboardDriverMessage.parameter3);
    getline (halKeyboardDriverMessageFile, HALkeyboardDriverMessage.parameter4);
    HALkeyboardDriverMessage.parameter5 = "";
    HALkeyboardDriverMessage.parameter6 = "";
    HALkeyboardDriverMessage.parameter7 = "";

    if (!halKeyboardDriverMessageFile)
    {
        cout << "HALos: message not received from HALkeyboardDriver" << endl;
        exit (1);
    }

    #ifdef HALkeyboardDriver_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALos: received message from HALkeyboardDriver for pid = " << HALkeyboardDriverMessage.parameter2 << endl;
        cout << "    type = " << HALkeyboardDriverMessage.type << endl;
        cout << "    parameter1 = " << HALkeyboardDriverMessage.parameter1 << endl;
        cout << "    parameter2 = " << HALkeyboardDriverMessage.parameter2 << endl;
        cout << "    parameter3 = " << HALkeyboardDriverMessage.parameter3 << endl;
        cout << "    parameter4 = " << HALkeyboardDriverMessage.parameter4 << endl;
    }
    #endif

    halKeyboardDriverMessageFile.close ();

    return;
}

void SendMessageToHALkeyboardDriver (string pid, string systemCall)
{
    ofstream halOsMessageFile;
    union sigval dummyValue;

    halOsMessageFile.open ("HALosToHALkeyboardDriver");
    if (!halOsMessageFile)
    {
        cout << "HALos: unable to initialize HALkeyboardDriver message buffer" << endl;
        exit (1);
    }

    halOsMessageFile << pid << endl;
    halOsMessageFile << systemCall << endl;

    #ifdef HALkeyboardDriver_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALos: sending message to HALkeyboardDriver for pid = " << pid << endl;
        cout << "    systemCall = " << systemCall << endl;
    }
    #endif

    halOsMessageFile.close ();

    if (sigqueue (HALkeyboardDriverPid, SIGRTMIN, dummyValue) == -1)
    {
        cout << "HALos: message not sent to HALkeyboardDriver" << endl;
        exit (1);
    }

    return;
}

void GetMessageFromHALdisplayDriver ()
{
    ifstream halDisplayDriverMessageFile;

    halDisplayDriverMessageFile.open ("HALdisplayDriverToHALos");
    if (!halDisplayDriverMessageFile)
    {
        cout << "HALos: connection to HALdisplayDriver failed" << endl;
        exit (1);
    }

    getline (halDisplayDriverMessageFile, HALdisplayDriverMessage.type);
    getline (halDisplayDriverMessageFile, HALdisplayDriverMessage.parameter1);
    getline (halDisplayDriverMessageFile, HALdisplayDriverMessage.parameter2);
    HALdisplayDriverMessage.parameter3 = "";
    HALdisplayDriverMessage.parameter4 = "";
    HALdisplayDriverMessage.parameter5 = "";
    HALdisplayDriverMessage.parameter6 = "";
    HALdisplayDriverMessage.parameter7 = "";

    if (!halDisplayDriverMessageFile)
    {
        cout << "HALos: message not received from HALdisplayDriver" << endl;
        exit (1);
    }

    #ifdef HALdisplayDriver_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALos: received message from HALdisplayDriver for pid = " << HALdisplayDriverMessage.parameter2 << endl;
        cout << "    type = " << HALdisplayDriverMessage.type << endl;
        cout << "    parameter1 = " << HALdisplayDriverMessage.parameter1 << endl;
        cout << "    parameter2 = " << HALdisplayDriverMessage.parameter2 << endl;
    }
    #endif

    halDisplayDriverMessageFile.close ();

    return;
}

void SendMessageToHALdisplayDriver (string pid, string systemCall, string buffer)
{
    ofstream halOsMessageFile;
    union sigval dummyValue;

    halOsMessageFile.open ("HALosToHALdisplayDriver");
    if (!halOsMessageFile)
    {
        cout << "HALos: unable to initialize HALdisplayDriver message buffer" << endl;
        exit (1);
    }

    halOsMessageFile << pid << endl;
    halOsMessageFile << systemCall << endl;
    halOsMessageFile << buffer << endl;

    #ifdef HALdisplayDriver_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALos: sending message to HALdisplayDriver for pid = " << pid << endl;
        cout << "    systemCall = " << systemCall << endl;
        cout << "    buffer = " << buffer << endl;
    }
    #endif

    halOsMessageFile.close ();

    if (sigqueue (HALdisplayDriverPid, SIGRTMIN, dummyValue) == -1)
    {
        cout << "HALos: message not sent to HALdisplayDriver" << endl;
        exit (1);
    }

    return;
}

void GetMessageFromHALdiskDriver ()
{
    static int seqNo = 0;
    static string fileNamePrefix = "HALdiskDriverToHALos_";
    static string fileName;
    ifstream halDiskDriverMessageFile;

    if (seqNo > 0)
    {
        remove (fileName.c_str ());
    }

    seqNo ++;
    fileName = fileNamePrefix + itos (seqNo);
    halDiskDriverMessageFile.open (fileName.c_str ());
    if (!halDiskDriverMessageFile)
    {
        cout << "HALos: connection to HALdiskDriver failed" << endl;
        exit (1);
    }

    getline (halDiskDriverMessageFile, HALdiskDriverMessage.type);
    getline (halDiskDriverMessageFile, HALdiskDriverMessage.parameter1);
    getline (halDiskDriverMessageFile, HALdiskDriverMessage.parameter2);
    getline (halDiskDriverMessageFile, HALdiskDriverMessage.parameter3);
    getline (halDiskDriverMessageFile, HALdiskDriverMessage.parameter4);
    getline (halDiskDriverMessageFile, HALdiskDriverMessage.parameter5);
    HALdiskDriverMessage.parameter6 = "";
    HALdiskDriverMessage.parameter7 = "";

    #ifdef HALdiskDriver_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALos: received message from HALdiskDriver for pid = " << HALdiskDriverMessage.parameter2 << endl;
        cout << "    type = " << HALdiskDriverMessage.type << endl;
        if (HALdiskDriverMessage.parameter1 == "OPEN")
        {
            cout << "    systemCall = " << HALdiskDriverMessage.parameter1 << endl;
            cout << "    pid = " << HALdiskDriverMessage.parameter2 << endl;
            cout << "    fileName = " << HALdiskDriverMessage.parameter3 << endl;
            cout << "    address = " << HALdiskDriverMessage.parameter4 << endl;
            cout << "    mode = " << HALdiskDriverMessage.parameter5 << endl;
        }
        else if (HALdiskDriverMessage.parameter1 == "READ")
        {
            cout << "    systemCall = " << HALdiskDriverMessage.parameter1 << endl;
            cout << "    pid = " << HALdiskDriverMessage.parameter2 << endl;
            cout << "    markerPosition = " << HALdiskDriverMessage.parameter3 << endl;
            cout << "    buffer = " << HALdiskDriverMessage.parameter4 << endl;
            cout << "    result = " << HALdiskDriverMessage.parameter5 << endl;
        }
        else if (HALdiskDriverMessage.parameter1 == "WRITE" || HALdiskDriverMessage.parameter1 == "NEWLINE")
        {
            cout << "    systemCall = " << HALdiskDriverMessage.parameter1 << endl;
            cout << "    pid = " << HALdiskDriverMessage.parameter2 << endl;
            cout << "    markerPosition = " << HALdiskDriverMessage.parameter3 << endl;
            cout << "    buffer = " << HALdiskDriverMessage.parameter4 << endl;
            cout << "    result = " << HALdiskDriverMessage.parameter5 << endl;
        }
        else if (HALdiskDriverMessage.parameter1 == "CLOSE")
        {
            cout << "    systemCall = " << HALdiskDriverMessage.parameter1 << endl;
            cout << "    pid = " << HALdiskDriverMessage.parameter2 << endl;
            cout << "    fileName = " << HALdiskDriverMessage.parameter3 << endl;
            cout << "    address = " << HALdiskDriverMessage.parameter4 << endl;
            cout << "    mode = " << HALdiskDriverMessage.parameter5 << endl;
        }
    }
    #endif

    if (!halDiskDriverMessageFile)
    {
        cout << "HALos: message not received from HALdiskDriver" << endl;
        exit (1);
    }

    halDiskDriverMessageFile.close ();

    if (seqNo == INT_MAX)
    {
        seqNo = 1;
    }

    return;
}

void SendMessageToHALdiskDriver (string pid, string systemCall, string fileName, string mode, string markerPosition, string buffer)
{
    ofstream halOsMessageFile;
    union sigval dummyValue;

    halOsMessageFile.open ("HALosToHALdiskDriver");
    if (!halOsMessageFile)
    {
        cout << "HALos: unable to initialize HALdiskDriver message buffer" << endl;
        exit (1);
    }

    halOsMessageFile << pid << endl;
    halOsMessageFile << systemCall << endl;
    halOsMessageFile << fileName << endl;
    halOsMessageFile << mode << endl;
    halOsMessageFile << markerPosition << endl;
    halOsMessageFile << buffer << endl;

    #ifdef HALdiskDriver_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALos: sending message to HALdiskDriver for pid = " << pid << endl;
        cout << "    systemCall = " << systemCall << endl;
        cout << "    fileName = " << fileName << endl;
        cout << "    mode = " << mode << endl;
        cout << "    markerPosition = " << markerPosition << endl;
        cout << "    buffer = " << buffer << endl;
    }
    #endif

    halOsMessageFile.close ();

    if (sigqueue (HALdiskDriverPid, SIGRTMIN, dummyValue) == -1)
    {
        cout << "HALos: message not sent to HALdiskDriver" << endl;
        exit (1);
    }

    return;
}

// Miscellaneous Functions and Procedures

void ClearMessageParameters (message &halMessage)
{
    halMessage.type = "";
    halMessage.parameter1 = "";
    halMessage.parameter2 = "";
    halMessage.parameter3 = "";
    halMessage.parameter4 = "";
    halMessage.parameter5 = "";
    halMessage.parameter6 = "";
    halMessage.parameter7 = "";

    return;
}

int UpdatePartitionTable (string pid, string &action)
{
    int partitionNo;

    partitionNo = 0;

    return (partitionNo);
}

processDescriptor NullProcess ()
{
    processDescriptor process;
    int i;

    process.pid = itos (-1);
    process.type = "";
    process.action = "";
    process.command = "";
    for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i ++)
    {
        process.arguments [i] = "";
    }
    process.returnValue = "";
    process.queueNo = 0;
    process.quantumLength = 0;
    process.partitionNo = 0;
    process.direction = "";
    process.interruptCounter = 0;
    process.priority = NOT_A_PRIORITY_PROCESS;
    process.fileTable.Clear ();
    process.systemCall = "";
    process.systemCallParameter1 = "";
    process.systemCallParameter2 = "";
    process.systemCallParameter3 = "";
    process.systemCallBuffer = "";
    process.systemCallResult = "";

    return process;
}

unsigned int TimeSeed ()
{
    time_t now;
    unsigned char *p;
    unsigned seed;
    size_t i;

    now = time (0);
    p = (unsigned char *) &now;
    seed = 0;

    for (i = 0; i < sizeof (now); i ++)
    {
        seed = seed * (UCHAR_MAX + 2U) + p [i];
    }

    return seed;
}

int GetRandomNoFromZeroTo (int maxNo)
{
    double randomNumber;
    int randomNumberScaled;

    randomNumber = rand () / (1.0 + (double) RAND_MAX);
    randomNumberScaled = (int) (randomNumber * (double) maxNo);

    return randomNumberScaled;
}

int RandomQuantumLengthAdjustment (int baseQuantumLength)
{
    int quantumLengthAdjustment;
    int quantumLengthAdjustmentSign;

    quantumLengthAdjustment = (int) (baseQuantumLength / 20) + 1;
    quantumLengthAdjustment = GetRandomNoFromZeroTo (quantumLengthAdjustment);
    quantumLengthAdjustmentSign = GetRandomNoFromZeroTo (2);
    if (quantumLengthAdjustmentSign == 0)
    {
        quantumLengthAdjustment = quantumLengthAdjustment * -1;
    }

    return quantumLengthAdjustment;
}

// Numeric to String Function

string itos (int i)
{
    stringstream s;

    s << i;

    return s.str ();
}
