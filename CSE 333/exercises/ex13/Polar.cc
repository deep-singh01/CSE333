/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX13
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Polar Class Implementation
*/

#include <sstream>

#include "Polar.h"
#include <cmath>

using std::string;
using std::stringstream;

// Returns a string representation of the Polar coordinate.
string Polar::ToString() const {
  stringstream ss;
  ss << "(" << r_ << ", " << theta_ << ")";
  return ss.str();
}

// Returns the distance of between the object and another Polar coordinate.
double Polar::Distance(const Polar &other) const {
  double radicand = r_ * r_ + other.r_ * other.r_ - 2 * r_ *
    other.r_ * cos(theta_ - other.theta_);
  return sqrt(radicand);
}
