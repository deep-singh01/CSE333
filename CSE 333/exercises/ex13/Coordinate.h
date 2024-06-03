/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX13
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Coordinate Class
*/

#include <string>

#ifndef COORDINATE_H_
#define COORDINATE_H_

class Coordinate {
 public:
  // Returns a string representation of the coordinate.
  virtual std::string ToString() const = 0;
  // Destructor
  virtual ~Coordinate() {}
};

#endif  // COORDINATE_H_
