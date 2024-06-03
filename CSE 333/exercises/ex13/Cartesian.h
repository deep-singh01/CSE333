/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX13
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Cartesian Class
*/

#include <string>
#include "Coordinate.h"

#ifndef CARTESIAN_H_
#define CARTESIAN_H_

class Cartesian : Coordinate {
 public:
  // Default constructor
  Cartesian(): x_(0), y_(0) {}
  // Standard constructor
  Cartesian(double x, double y): x_(x), y_(y) {}
  // Destructor
  ~Cartesian() {}
  // Returns a string representation of the Cartesian coordinate.
  std::string ToString() const override;
  // Returns the distance of between the object and another
  // Cartesian coordinate.
  virtual double Distance(const Cartesian &other) const;

 private:
  // The x and y coordinates of the Cartesian coordinate.
  double x_;
  double y_;
};

#endif  // CARTESIAN_H_
