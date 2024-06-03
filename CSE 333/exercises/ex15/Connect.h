/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX15
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Connect Header File
*/

#ifndef CONNECT_H_
#define CONNECT_H_

#include <sys/socket.h>  // sockaddr_storage
#include <sys/types.h>   // size_t

bool LookupName(char *name, unsigned short port,
  struct sockaddr_storage *ret_addr, size_t *ret_addrlen);

bool CreateandConnect(const struct sockaddr_storage &addr,
  const size_t &addrlen, int *ret_fd);

#endif  // CONNECT_H_
