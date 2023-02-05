//
// HALsocketFunctions.h
//
// Copyright (c) 2018 Robert J. Hilderman.
// All Rights Reserved.
//

#include "HALsocketInclude.h"

#define HAL_SOCKET_FUNCTIONS_H

int ReadLine (int socketFD, char *ptr, int lineSize)
{
    int n;
    int rc;
    char c;

    for (n = 1; n < lineSize; n++)
    {
        if ((rc = ReadN (socketFD, &c, 1)) == 1)
        {
	    *ptr++ = c;
	    if (c == '\n')
	    {
	        break;
            }
        }
        else if (rc == 0)
        {
            if (n == 1)
            {
                return (0);
            }
            else
            {
                break;
            }
        }
        else
        {
	    return (-1);
        }
    }
    *ptr = 0;

    return (n);
}

int WriteN (int socketFD, char *ptr, int nBytes)
{
    int nLeft;
    int nWritten;

    nLeft = nBytes;

    while (nLeft > 0)
    {
        nWritten = write (socketFD, ptr, nLeft);
        if (nWritten <= 0)
        { 
	    return (nWritten);
        }
        nLeft = nLeft - nWritten;
        ptr = ptr + nWritten;
    }

    return (nBytes - nLeft);
}

int ReadN (int socketFD, char *ptr, int nBytes)
{
    int nLeft;
    int nRead;

    nLeft = nBytes;

    while (nLeft > 0)
    {
        nRead = read (socketFD, ptr, nLeft);
        if (nRead < 0)
        {
	    return (nRead);
        }
        else if (nRead == 0)
        {
	    break;
        }
        nLeft = nLeft - nRead;
        ptr = ptr + nRead;
    }

    return (nBytes - nLeft);
}
