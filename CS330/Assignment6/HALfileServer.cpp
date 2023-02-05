//
// HALdiskDriver.cpp
//
// Copyright (c) 2018 Robert J. Hilderman.
// All Rights Reserved.
//

#include "HALfileServer.h"

// The "Disk Driver"

void HALfileServer ()
{
    do
    {
        BlockSignals ("HALfileServer");
        if (messageFromHALos)
        {
            messageFromHALos = 0;
            GetMessageFromHALos ();
            ProcessIORequest ();
            SendMessageToHALos ();
        }
        UnblockSignals ("HALfileServer");
    } while (1);

    return;
}

void ProcessIORequest ()
{
    fstream inOutFile;
    struct stat statusBuffer;
    size_t eofMarker;

    // ----------------- Socket on server ----------------
    int socketFD;
    int newSocketFD;
    socklen_t addr_length;
    pid_t child_pid;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    char host_name[256];

    // -------- Socket system call ----------
    if ((socketFD = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        result = "SOCKET_OPEN_FAILED";
        exit(1);
    }
    else {
        cout << "HALfileServer: Socket openned." << endl;
    }

    memset (&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    gethostname(host_name, sizeof(host_name));
    hp = gethostbyname (host_name);
    if (hp == (struct hostent *) NULL) {
        result = "HOST_NAME_DOES_NOT_EXIST";
        exit(1);
    }
    else {
        cout << "HALfileServer: host_name " << host_name << endl;
    }

    memcpy (&server_addr.sin_addr, hp -> h_addr, hp -> h_length);

    server_addr.sin_port = htons (TCP_PORTNO);

    // --------- Bind system call ------------
    if (bind (socketFD, (struct sockaddr *) &server_addr, sizeof (server_addr)) < 0) {
        result = "SOCKET_BIND_FAILED";
        exit(1);
    }
    else {
        cout << "HALfileServer: bind successful." << endl;
    }

    // ---------- Listen system call ----------
    if (listen (socketFD, 5) < 0) {
        result = "SOCKET_LISTEN_FAILED";
        exit(1);
    }
    else {
        cout << "HALfileServer: listening on port " << TCP_PORTNO << endl;
    }

    // ----------- Infinite loop --------------
    while (1) {

        // ------ Accept system call ----------
        addr_length = sizeof(client_addr);
        newSocketFD = accept (socketFD, (struct sockaddr *) &client_addr, &addr_length);
        if (newSocketFD < 0) {
            result = "SOCKET_ACCEPT_ERROR";
            exit(1);
        }

        // ------- Fork a child process ----------
        if ((child_pid = fork()) < 0) {
            result = "FORK_ERROR_ON_SERVER";
            exit(1);
        }
        // ----- Child process -----
        else if (child_pid == 0) {

            // ------- Read from the socket ------------
            ReceiveResponse(newSocketFD);

            if (systemCall == "OPEN")
            {
                if (mode == "input")
                {
                    // check for existence of file
                    if (stat (fileName.c_str (), &statusBuffer) != -1)
                    {
                        result = "FILE_OPEN_OK";
                    }
                    else
                    {
                        result = "FILE_OPEN_FAILED";
                    }
                }
                else // (mode == "output")
                {
                    // create empty file
                    inOutFile.open (fileName.c_str (), fstream::trunc | fstream::out);
                    if (inOutFile)
                    {
                        result = "FILE_OPEN_OK";
                    }
                    else
                    {
                        result = "FILE_OPEN_FAILED";
                    }
                    inOutFile.close ();
                }
            }
            else if (systemCall == "READ")
            {
                inOutFile.open (fileName.c_str (), fstream::ate | fstream::in);
                if (inOutFile)
                {
                    eofMarker = inOutFile.tellg ();
                    if (atoi (markerPosition.c_str ()) != eofMarker)
                    {
                        inOutFile.seekg (atoi (markerPosition.c_str ()));
                        getline (inOutFile, buffer);
                        if (inOutFile)
                        {
                            markerPosition = itos (inOutFile.tellg ());
                            result = "FILE_READ_OK";
                        }
                        else
                        {
                            buffer = "";
                            markerPosition = "";
                            result = "FILE_READ_FAILED";
                        }
                    }
                    else
                    {
                        buffer = "";
                        markerPosition = "EOF";
                        result = "FILE_AT_END";
                    }
                }
                else
                {
                    buffer = "";
                    markerPosition = "";
                    result = "FILE_READ_FAILED";
                }
                inOutFile.close ();
            }
            else if (systemCall == "WRITE")
            {
                inOutFile.open (fileName.c_str (), fstream::app | fstream ::out);
                if (inOutFile)
                {
                    inOutFile << buffer << flush;
                    markerPosition = "";
                    result = "FILE_WRITE_OK";
                }
                else
                {
                    markerPosition = "";
                    result = "FILE_WRITE_FAILED";
                }
                inOutFile.close ();
            }
            else if (systemCall == "NEWLINE")
            {
                inOutFile.open (fileName.c_str (), fstream::app | fstream ::out);
                if (inOutFile)
                {
                    inOutFile << endl;
                    markerPosition = "";
                    result = "FILE_NEWLINE_OK";
                }
                else
                {
                    markerPosition = "";
                    result = "FILE_NEWLINE_FAILED";
                }
                inOutFile.close ();
            }
            else if (systemCall == "SHUTDOWN")
            {
                system ("HALdiskDriverCleanup");
                exit (0);
            }

            // ------- send back to client -------
            
            SendRequest(newSocketFD);
            close(newSocketFD);
        }
        // ----- Parent process -----
        else {
            close(newSocketFD);
        }
    }
    

    return;
}

// The "Communication Media"

void GetMessageFromHALos ()
{
    ifstream ioRequestFile;

    ioRequestFile.open ("HALosToHALfileServer");
    if (!ioRequestFile)
    {
        cout << "HALfileServer: unable to open io request buffer" << endl;
        exit (1);
    }

    getline (ioRequestFile, pid);
    getline (ioRequestFile, systemCall);
    getline (ioRequestFile, fileName);
    getline (ioRequestFile, mode);
    getline (ioRequestFile, markerPosition);
    getline (ioRequestFile, buffer);

    #ifdef HALfileServer_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALfileServer: message received from HALos for pid = " << pid << endl;
        cout << "    pid = " << pid << endl;
        cout << "    systemCall = " << systemCall << endl;
        cout << "    fileName = " << fileName << endl;
        cout << "    mode = " << mode << endl;
        cout << "    markerPosition = " << markerPosition << endl;
        cout << "    buffer = " << buffer << endl;
    }
    #endif

    if (!ioRequestFile)
    {
        cout << "HALdiskDriver: message from HALos corrupted" << endl;
        exit (1);
    }

    ioRequestFile.close ();

    return;
}

void SendMessageToHALos ()
{
    static int seqNo = 0;
    static string fileNamePrefix = "HALfileServerToHALos_";
    string fileName;
    ofstream ioResponseFile;
    union sigval dummyValue;

    seqNo ++;
    fileName = fileNamePrefix + itos (seqNo);
    ioResponseFile.open (fileName.c_str ());
    if (!ioResponseFile)
    {
        cout << "HALfileServer: unable to open io response buffer" << endl;
        exit (1);
    }

    ioResponseFile << "INTERRUPT" << endl;
    ioResponseFile << systemCall << endl;
    ioResponseFile << pid << endl;
    ioResponseFile << markerPosition << endl;
    ioResponseFile << buffer << endl;
    ioResponseFile << result << endl;

    #ifdef HALdiskDriver_MESSAGE_TRACE_ON
    {
        cout << endl;
        cout << "HALfileServer: message sent to HALos for pid = " << pid << endl;
        cout << "    type = INTERRUPT" << endl;
        cout << "    systemCall = " << systemCall << endl;
        cout << "    pid = " << pid << endl;
        cout << "    markerPosition = " << markerPosition << endl;
        cout << "    buffer = " << buffer << endl;
        cout << "    result = " << result << endl;
    }
    #endif

    ioResponseFile.close ();

    if (sigqueue (HALosPid, SIGRTMIN, dummyValue) == -1)
    {
        cout << "HALfileServer: error sending io response signal to HALos" << endl;
        exit (1);
    }

    if (seqNo == INT_MAX)
    {
        seqNo = 1;
    }

    return;
}

// -------------------------------------------------------------------------------------
void SendRequest (int socketFD) {
    string workLine[6];
    workLine[0] = pid;
    workLine[1] = systemCall;
    workLine[2] = fileName;
    workLine[3] = mode;
    workLine[4] = markerPosition;
    workLine[5] = buffer;

    int counter;
    int length;
    // Write each workLine to the socket
    for (int i = 0; i < 6; i++) {
        length = strlen(workLine[i].c_str());
        if ((counter = WriteN (socketFD, (char *)workLine[i].c_str(), length)) != length) {
            result = "WRITE_N_ERROR_IN_SEND_REQUEST";
            exit(1);
        }
    }
}

void ReceiveResponse (int socketFD) {
    string workLine[6];

    int counter;

    for (int i = 0; i < 6; i++) {
        counter = ReadLine (socketFD, (char *)workLine[i].c_str(), 255);
        if (counter < 0) {
            result = "READ_LINE_ERROR_IN_RECEIVE_RESPONSE";
            exit(1);
        }
    }
    pid = workLine[0];
    systemCall = workLine[1];
    fileName = workLine[2];
    mode = workLine[3];
    markerPosition = workLine[4];
    buffer = workLine[5];
}
// -------------------------------------------------------------------------------------

string itos (int i)
{
    stringstream s;

    s << i;

    return s.str ();
}
