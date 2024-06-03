// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX10
//
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// Vector Header File

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

namespace vector333 {

// A Vector is a class that represents a point in 3D space.
class Vector {
 public:
  // Constructors
  // Create a new default Vector, setting the x, y, and z values to 0.
  Vector();

  // Create a new Vector with the given x, y, and z values.
  Vector(const double x, const double y, const double z);

  // Create a copy of the given Vector.
  Vector(const Vector &v);

  // Destructor
  ~Vector();

  // operators
  Vector &operator=(const Vector &a);
  Vector &operator+=(const Vector &a);
  Vector &operator-=(const Vector &a);

  // friend functions
  // print Vector
  friend std::ostream &operator<<(std::ostream &out, const Vector &a);
  friend double operator*(const Vector &a, const Vector &b);
  friend Vector operator*(const Vector &a, const double k);

 private:
  // x, y, and z values of Vector
  double *vector_;
};  // class Vector

// additional non-member functions
Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);
Vector operator*(const double k, const Vector &a);

}  // namespace vector333

#endif  // VECTOR_H_
