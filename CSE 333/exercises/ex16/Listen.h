/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX15
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Listen Header File
*/

#ifndef _LISTEN_H_
#define _LISTEN_H_

#include <sys/socket.h>
#include <sys/types.h>

int  Listen(char *portnum, int *sock_family);
void HandleClient(int c_fd, struct sockaddr *addr,
  size_t addrlen, int sock_family);

#endif  // _LISTEN_H_
