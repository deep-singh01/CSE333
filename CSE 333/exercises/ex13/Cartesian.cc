/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX13
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Cartesian Class Implementation
*/

#include <sstream>

#include "Cartesian.h"
#include <cmath>

using std::string;
using std::stringstream;

// Returns a string representation of the Cartesian coordinate.
string Cartesian::ToString() const {
  stringstream ss;
  ss << "(" << x_ << ", " << y_ << ")";
  return ss.str();
}

// Returns the distance of between the object and another Cartesian coordinate.
double Cartesian::Distance(const Cartesian &other) const {
  double dx = x_ - other.x_;
  double dy = y_ - other.y_;
  return sqrt(dx * dx + dy * dy);
}
