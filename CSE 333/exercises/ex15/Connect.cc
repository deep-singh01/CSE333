/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX15
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Connect Implementation File
*/

#include <arpa/inet.h>  // sockaddr_storage
#include <assert.h>     // assert
#include <errno.h>      // errno
#include <netdb.h>      // getaddrinfo
#include <unistd.h>     // close
#include <stdlib.h>     // freeaddrinfo
#include <string.h>     // memset, strerror
#include <iostream>     // cerr`

#include "./Connect.h"

bool LookupName(char *name, unsigned short port,
  struct sockaddr_storage *ret_addr, size_t *ret_addrlen) {
  struct addrinfo hints, *results;
  int retval;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  // Do the lookup by invoking getaddrinfo().
  if ((retval = getaddrinfo(name, nullptr, &hints, &results)) != 0) {
    std::cerr << "getaddrinfo failed: ";
    std::cerr << gai_strerror(retval) << std::endl;
    return false;
  }

  // Set the port in the first result.
  if (results->ai_family == AF_INET) {
    struct sockaddr_in *v4addr = (struct sockaddr_in *) results->ai_addr;
    v4addr->sin_port = htons(port);
  } else if (results->ai_family == AF_INET6) {
    struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *) results->ai_addr;
    v6addr->sin6_port = htons(port);
  } else {
    std::cerr << "getaddrinfo failed to provide an IPv4 or IPv6 address";
    std::cerr << std::endl;
    freeaddrinfo(results);
    return false;
  }

  // Return the first result.
  assert(results != nullptr);
  memcpy(ret_addr, results->ai_addr, results->ai_addrlen);
  *ret_addrlen = results->ai_addrlen;

  // Clean up.
  freeaddrinfo(results);
  return true;
}

bool CreateandConnect(const struct sockaddr_storage &addr,
  const size_t &addrlen, int *ret_fd) {
  // Create a socket.
  int socket_fd = socket(addr.ss_family, SOCK_STREAM, 0);

  // Check for errors.
  if (socket_fd == -1) {
    std::cerr << "socket() failed: " << strerror(errno) << std::endl;
    return false;
  }

  // Connect to the server.
  if (connect(socket_fd,
    reinterpret_cast<const sockaddr *>(&addr), addrlen) == -1) {
    std::cerr << "connect() failed: " << strerror(errno) << std::endl;
    close(socket_fd);
    return false;
  }

  *ret_fd = socket_fd;
  return true;
}
