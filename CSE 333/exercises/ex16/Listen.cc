/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX16
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Listen Implementation File
*/

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include "./Listen.h"

#define BUF_SIZE 1024

int Listen(char *portnum, int *sock_family) {
  // Populate the "hints" addrinfo structure for getaddrinfo().
  // ("man addrinfo")
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET6;       // IPv6 (also handles IPv4 clients)
  hints.ai_socktype = SOCK_STREAM;  // stream
  hints.ai_flags = AI_PASSIVE;      // use wildcard "in6addr_any" address
  hints.ai_flags |= AI_V4MAPPED;    // use v4-mapped v6 if no v6 found
  hints.ai_protocol = IPPROTO_TCP;  // tcp protocol
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  // Use argv[1] as the string representation of our portnumber to
  // pass in to getaddrinfo().  getaddrinfo() returns a list of
  // address structures via the output parameter "result".
  struct addrinfo *result;
  int res = getaddrinfo(nullptr, portnum, &hints, &result);

  // Did addrinfo() fail?
  if (res != 0) {
    std::cerr << "getaddrinfo() failed: ";
    std::cerr << gai_strerror(res) << std::endl;
    return -1;
  }

  // Loop through the returned address structures until we are able
  // to create a socket and bind to one.  The address structures are
  // linked in a list through the "ai_next" field of result.
  int listen_fd = -1;
  for (struct addrinfo *rp = result; rp != nullptr; rp = rp->ai_next) {
    listen_fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (listen_fd == -1) {
      // Creating this socket failed.  So, loop to the next returned
      // result and try again.
      std::cerr << "socket() failed: " << strerror(errno) << std::endl;
      listen_fd = -1;
      continue;
    }

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(listen_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind worked!

      // Return to the caller the address family.
      *sock_family = rp->ai_family;
      break;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(listen_fd);
    listen_fd = -1;
  }

  // Free the structure returned by getaddrinfo().
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (listen_fd == -1)
    return listen_fd;

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(listen_fd, SOMAXCONN) != 0) {
    std::cerr << "Failed to mark socket as listening: ";
    std::cerr << strerror(errno) << std::endl;
    close(listen_fd);
    return -1;
  }

  // Return to the client the listening file descriptor.
  return listen_fd;
}

void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family) {
  // Loop, reading data and echo'ing it back, until the client
  // closes the connection.
  while (1) {
    char clientbuf[BUF_SIZE];
    ssize_t res = read(c_fd, clientbuf, BUF_SIZE - 1);

    if (res == 0) {
      break;
    }

    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      std::cerr << " [Error on client socket: ";
      std::cerr << strerror(errno) << "]" << std::endl;
      break;
    }
    clientbuf[res] = '\0';
    ssize_t wrt = 0;

    // Write data to stdout.
    while (wrt < res) {
      ssize_t wr = fwrite(clientbuf + wrt, sizeof(char), res - wrt, stdout);
      if (wr == -1) {
        if ((errno == EINTR) || (errno == EAGAIN)) {
          continue;
        } else {
          std::cerr << "fwrite() failed: " << strerror(errno) << std::endl;
          close(c_fd);
          exit(EXIT_FAILURE);
        }
      }
      wrt += wr;
    }
  }

  close(c_fd);
}
