//
// HALsocketInclude.h
//
// Copyright (c) 2018 Robert J. Hilderman.
// All Rights Reserved.
//

#define HAL_SOCKET_INCLUDE_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/file.h>

#define TCP_PORTNO 9424

// The "Network Interface"

void SendRequest (int socketFD);
void ReceiveResponse (int socketFD);
int ReadLine (int socketFD, char *ptr, int lineSize);
int WriteN (int socketFD, char *ptr, int nBytes);
int ReadN (int socketFD, char *ptr, int nBytes);
