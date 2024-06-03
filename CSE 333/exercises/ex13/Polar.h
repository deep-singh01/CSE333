/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX13
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Polar Class
*/

#include <string>
#include "Coordinate.h"

#ifndef POLAR_H_
#define POLAR_H_

class Polar : Coordinate {
 public:
  // Default constructor
  Polar(): r_(0), theta_(0) {}
  // Standard constructor
  Polar(double r, double theta): r_(r), theta_(theta) {}
  // Destructor
  ~Polar() {}
  // Returns a string representation of the Polar coordinate.
  std::string ToString() const override;
  // Returns the distance of between the object and another Polar coordinate.
  virtual double Distance(const Polar &other) const;

 private:
  // The radius and angle of the Polar coordinate.
  double r_;
  double theta_;
};

#endif  // POLAR_H_
