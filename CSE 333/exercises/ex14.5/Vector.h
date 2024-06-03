// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX14.5
//
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// Vector (ex14.5) Header File

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

namespace vector333 {

// A Vector is a class that represents a point in 3D space.
class Vector {
 public:
  // Constructors
  // Create a new default Vector, setting the x, y, and z values to 0.
  Vector() : x_(0), y_(0), z_(0) {}

  // Create a new Vector with the given x, y, and z values.
  Vector(const double x, const double y, const double z) :
    x_(x), y_(y), z_(z) {
    std::cout << "Constructor called\n" << std::endl;
    }

  // Create a copy of the given Vector.
  Vector(const Vector &v) : x_(v.x_), y_(v.y_), z_(v.z_) {
    std::cout << "Copy Constructor called" << std::endl;
  }

  // Destructor
  ~Vector();

  // get X, Y, Z values
  double get_x() const { return x_; }
  double get_y() const { return y_; }
  double get_z() const { return z_; }

  // operators
  Vector &operator=(const Vector &a);
  Vector &operator+=(const Vector &a);
  Vector &operator-=(const Vector &a);
  Vector &operator()(const double x, const double y, const double z);
  Vector &operator()(const Vector &a);

 private:
  // x, y, and z values of Vector
  double x_, y_, z_;
};  // class Vector

// additional non-member operators
Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);

double operator*(const Vector &a, const Vector &b);
Vector operator*(const Vector &a, const double k);
Vector operator*(const double k, const Vector &a);

std::ostream &operator<<(std::ostream &out, const Vector &a);

}  // namespace vector333

#endif  // VECTOR_H_
