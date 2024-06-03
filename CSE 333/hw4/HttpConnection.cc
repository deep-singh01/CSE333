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

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;
using std::vector;
using boost::split;
using boost::is_any_of;
using boost::token_compress_on;
using boost::algorithm::trim_right;
using boost::algorithm::to_lower_copy;
using boost::algorithm::trim_left;

namespace hw4 {

#define BUF_SIZE 1024

static const char* kHeaderEnd = "\r\n\r\n";
static const int kHeaderEndLen = 4;

bool HttpConnection::GetNextRequest(HttpRequest* const request) {
  // Use WrappedRead from HttpUtils.cc to read bytes from the files into
  // private buffer_ variable. Keep reading until:
  // 1. The connection drops
  // 2. You see a "\r\n\r\n" indicating the end of the request header.
  //
  // Hint: Try and read in a large amount of bytes each time you call
  // WrappedRead.
  //
  // After reading complete request header, use ParseRequest() to parse into
  // an HttpRequest and save to the output parameter request.
  //
  // Important note: Clients may send back-to-back requests on the same socket.
  // This means WrappedRead may also end up reading more than one request.
  // Make sure to save anything you read after "\r\n\r\n" in buffer_ for the
  // next time the caller invokes GetNextRequest()!

  // STEP 1:
  size_t header_end = buffer_.find(kHeaderEnd);

  while (header_end == string::npos) {
    // Read data
    unsigned char buf[BUF_SIZE];
    int res = WrappedRead(fd_, buf, BUF_SIZE);

    // Connection dropped.
    if (res <= 0) {
      return false;
    }

    buffer_ += string(reinterpret_cast<char*>(buf), res);
    header_end = buffer_.find(kHeaderEnd);
  }

  // Parse the request.
  *request = this->ParseRequest(buffer_.substr(0, header_end + kHeaderEndLen));
  buffer_ = buffer_.substr(header_end + kHeaderEndLen);

  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse& response) const {
  string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         reinterpret_cast<const unsigned char*>(str.c_str()),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(const string& request) const {
  HttpRequest req("/");  // by default, get "/".

  // Plan for STEP 2:
  // 1. Split the request into different lines (split on "\r\n").
  // 2. Extract the URI from the first line and store it in req.URI.
  // 3. For the rest of the lines in the request, track the header name and
  //    value and store them in req.headers_ (e.g. HttpRequest::AddHeader).
  //
  // Hint: Take a look at HttpRequest.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for:
  // - Splitting a string into lines on a "\r\n" delimiter
  // - Trimming whitespace from the end of a string
  // - Converting a string to lowercase.
  //
  // Note: If a header is malformed, skip that line.

  // STEP 2:

  // Split the request into different lines.
  vector<string> lines;
  split(lines, request, is_any_of("\r\n"), token_compress_on);

  // Extract the URI from the first line.
  if (!lines.empty()) {
    vector<string> parts;
    split(parts, lines[0], is_any_of(" "), token_compress_on);

    if (parts.size() > 1) {
      req.set_uri(parts[1]);
    }
  }

  // Extract the headers.
  for (size_t i = 1; i < lines.size(); i++) {
    string line = lines[i];
    trim_right(line);  // Remove trailing whitespace.

    // Skip empty lines.
    if (line.empty()) {
      continue;
    }

    // Split the line into header name and value.
    vector<string> parts;
    split(parts, line, is_any_of(":"));

    // Skip malformed lines.
    if (parts.size() > 1) {
      string val = parts[1];
      trim_left(val);
      req.AddHeader(to_lower_copy(parts[0]), val);
    }
  }

  return req;
}

}  // namespace hw4
