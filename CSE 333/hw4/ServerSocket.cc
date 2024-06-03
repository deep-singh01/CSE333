/*
 * Copyright ©2024 Hannah C. Tang.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int* const listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd"
  // and set the ServerSocket data member "listen_sock_fd_"

  // STEP 1:

  // Check the ai_family parameter.
  if (ai_family != AF_INET && ai_family != AF_INET6 && ai_family != AF_UNSPEC) {
    std::cerr << "Invalid ai_family: " << ai_family << std::endl;
    return false;
  }

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
  std::string portnum = std::to_string(this->port_);
  int res = getaddrinfo(nullptr, portnum.c_str(), &hints, &result);

  // Did addrinfo() fail?
  if (res != 0) {
    std::cerr << "getaddrinfo() failed: ";
    std::cerr << gai_strerror(res) << std::endl;
    return -1;
  }

  // Loop through the returned address structures until we are able
  // to create a socket and bind to one.  The address structures are
  // linked in a list through the "ai_next" field of result.
  int fd = -1;
  for (struct addrinfo *rp = result; rp != nullptr; rp = rp->ai_next) {
    fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (fd == -1) {
      // Creating this socket failed.  So, loop to the next returned
      // result and try again.
      std::cerr << "socket() failed: " << strerror(errno) << std::endl;
      fd = -1;
      continue;
    }

    // Configure the socket; we're setting a socket "option."  In
    // particular, we set "SO_REUSEADDR", which tells the TCP stack
    // so make the port we bind to available again as soon as we
    // exit, rather than waiting for a few tens of seconds to recycle it.
    int optval = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));

    // Try binding the socket to the address and port number returned
    // by getaddrinfo().
    if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      // Bind worked!

      // Return to the caller the address family.
      this->sock_family_ = rp->ai_family;
      break;
    }

    // The bind failed.  Close the socket, then loop back around and
    // try the next address/port returned by getaddrinfo().
    close(fd);
    fd = -1;
  }

  // Free the structure returned by getaddrinfo().
  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (fd == -1)
    return fd;

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(fd, SOMAXCONN) != 0) {
    std::cerr << "Failed to mark socket as listening: ";
    std::cerr << strerror(errno) << std::endl;
    close(fd);
    return -1;
  }

  // Return to the client the listening file descriptor.
  *listen_fd = fd;
  this->listen_sock_fd_ = fd;

  return listen_fd;
}

bool ServerSocket::Accept(int* const accepted_fd,
                          std::string* const client_addr,
                          uint16_t* const client_port,
                          std::string* const client_dns_name,
                          std::string* const server_addr,
                          std::string* const server_dns_name) const {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  // STEP 2:
  int client_fd;
  struct sockaddr_storage client_addr_strge;
  socklen_t cas_len = sizeof(client_addr_strge);

  // Accept a new connection.
  while (1) {
    client_fd = accept(listen_sock_fd_,
                      reinterpret_cast<struct sockaddr*>(&client_addr_strge),
                      &cas_len);
    if (client_fd == -1) {
      if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;
      std::cerr << "accept() failed: " << strerror(errno) << std::endl;
      close(listen_sock_fd_);
      return false;
    }
    break;
  }

  *accepted_fd = client_fd;

  // Get the client's address and port.
  if (sock_family_ == AF_INET) {
    // IPv4
    struct sockaddr_in *v4addr = (struct sockaddr_in *) &client_addr_strge;
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(v4addr->sin_addr), ipstr, INET_ADDRSTRLEN);
    *client_addr = std::string(ipstr);
    *client_port = ntohs(v4addr->sin_port);

  } else if (sock_family_ == AF_INET6) {
    // IPv6
    struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *) &client_addr_strge;
    char ipstr[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &(v6addr->sin6_addr), ipstr, INET6_ADDRSTRLEN);
    *client_addr = std::string(ipstr);
    *client_port = ntohs(v6addr->sin6_port);

  } else {
    // Invalid address family
    std::cerr << "Invalid sock_family_: " << sock_family_ << std::endl;
    close(client_fd);
    return false;
  }

  // Get the client's DNS name.
  char hbuf[NI_MAXHOST];
  int res = getnameinfo(reinterpret_cast<struct sockaddr*>(&client_addr_strge),
                        cas_len,
                        hbuf, NI_MAXHOST,
                        nullptr, 0, 0);
  if (res != 0) {
    std::cerr << "getnameinfo() failed: " << gai_strerror(res) << std::endl;
    close(client_fd);
    return false;
  }
  *client_dns_name = std::string(hbuf);

  // Get the server's address and DNS name.
  char sbuf[NI_MAXHOST];
  sbuf[0] = '\0';

  if (sock_family_ == AF_INET) {
    // IPv4
    char saddr[INET_ADDRSTRLEN];
    struct sockaddr_in v4addr;
    socklen_t v4addr_len = sizeof(v4addr);

    getsockname(client_fd, (struct sockaddr*)(&v4addr),
                &v4addr_len);
    inet_ntop(AF_INET, &(v4addr.sin_addr), saddr, INET_ADDRSTRLEN);
    getnameinfo((const struct sockaddr*)(&v4addr),
                v4addr_len,
                sbuf, NI_MAXHOST,
                NULL, 0, 0);

    *server_addr = std::string(saddr);

  } else {
    // IPv6
    char saddr[INET6_ADDRSTRLEN];
    struct sockaddr_in6 v6addr;
    socklen_t v6addr_len = sizeof(v6addr);

    getsockname(client_fd, (struct sockaddr*)(&v6addr),
                &v6addr_len);
    inet_ntop(AF_INET6, &(v6addr.sin6_addr), saddr, INET6_ADDRSTRLEN);
    getnameinfo((const struct sockaddr*)(&v6addr),
                v6addr_len,
                sbuf, NI_MAXHOST,
                NULL, 0, 0);

    *server_addr = std::string(saddr);
  }

  *server_dns_name = std::string(sbuf);
  return true;
}

}  // namespace hw4
