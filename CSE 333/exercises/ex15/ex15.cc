/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX15
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program accepts three command line arguments: the hostname of a server,
* the port number of that server, and the name of a local file. Upon receiving
* these arguments it connects (via TCP) to the server on the supplied hostname
* and port. Once connected, the program reads the bytes from the local 
* file, and writes those bytes over the TCP connection. Once all of
* the bytes have been written, the program closes the TCP connection and 
* exit.
*/

#include <iostream>     // cout, cin
#include <cstdlib>      // EXIT_SUCCESS or EXIT_FAILURE
#include <arpa/inet.h>  // sockaddr_storage
#include <errno.h>      // errno
#include <unistd.h>     // read, write, close
#include <string.h>     // strerror
#include <fcntl.h>      // open

#include "./Connect.h"

#define BUF_SIZE 1024

void Usage(char *progname);
void Close(int fd, int socket_fd);

/* main - runs program described
*
* @param argc
*            number of strings on the command line
* @param argv
*             array containing pointers to the arguments as strings
*/
int main(int argc, char** argv) {
  if (argc != 4) {
    Usage(argv[0]);
  }

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    Usage(argv[0]);
  }

  // Get an appropriate sockaddr structure.
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    Usage(argv[0]);
  }

  // Create socket & Connect to the remote host.
  int socket_fd;
  if (!CreateandConnect(addr, addrlen, &socket_fd)) {
    Usage(argv[0]);
  }

  // Open the file.
  int fd = open(argv[3], O_RDONLY);
  if (fd == -1) {
    Usage(argv[0]);
  }

  char buf[BUF_SIZE];
  int bytes_read;

  while (1) {
    // Read from the file.
    bytes_read = read(fd, buf, BUF_SIZE - 1);
    if (bytes_read == 0) {  // EOF
      break;
    }
    if (bytes_read == -1) {  // Error
      if (errno == EINTR) {
        continue;
      }
      std::cerr << "file read failure: " << strerror(errno) << std::endl;
      Close(fd, socket_fd);
      return EXIT_FAILURE;
    }

    // Write to the socket.
    int wr = write(socket_fd, buf, bytes_read);
    if (wr == 0) {  // Error
      std::cerr << "socket closed prematurely" << std::endl;
      Close(fd, socket_fd);
      return EXIT_FAILURE;
    }
    if (wr == -1) {  // Error
      if (errno == EINTR) {
        continue;
      }
      std::cerr << "socket write failure: " << strerror(errno) << std::endl;
      Close(fd, socket_fd);
      return EXIT_FAILURE;
    }
  }

  // Clean up.
  Close(fd, socket_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " hostname port" << std::endl;
  exit(EXIT_FAILURE);
}

void Close(int fd, int socket_fd) {
  close(socket_fd);
  close(fd);
}
