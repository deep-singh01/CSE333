/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX16
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program accepts one command line argument: a port number to listen to.
* After which, it creates a TCP listening socket on the supplied port number. 
* Once a client connects, the program should read data from the connected
* client socket and write it to stdout until there is no more data to read from
* the client (i.e., until EOF or a socket error occurs). Once all of the data
* has been read and written, the program should close the client socket and
* the listening socket, and then exit.
*/

#include <cstdlib>   // EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>  // close
#include <string.h>  // strerror
#include <errno.h>   // errno
#include <iostream>  // cout, cerr

#include "./Listen.h"

void Usage(char *progname);

int main(int argc, char **argv) {
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // Loop forever, accepting a connection from a client and doing
  // an echo trick to it.
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr *>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      break;
    }

    HandleClient(client_fd,
                 reinterpret_cast<struct sockaddr *>(&caddr),
                 caddr_len,
                 sock_family);
    break;  // We only want to handle one client.
  }

  // Close up shop.
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}
