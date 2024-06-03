// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX10
// Vector
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// Vector Implementation File

#include <iostream>
#include "Vector.h"

namespace vector333 {

// member functions
Vector::Vector() {
  vector_ = new double[3];
  vector_[0] = 0;
  vector_[1] = 0;
  vector_[2] = 0;
}

Vector::Vector(const double x, const double y, const double z) {
  vector_ = new double[3];
  vector_[0] = x;
  vector_[1] = y;
  vector_[2] = z;
}

Vector::Vector(const Vector &v) {
  vector_ = new double[3];
  vector_[0] = v.vector_[0];
  vector_[1] = v.vector_[1];
  vector_[2] = v.vector_[2];
}

Vector::~Vector() {
  delete[] vector_;
}

Vector &Vector::operator=(const Vector &a) {
  if (this != &a) {
    vector_[0] = a.vector_[0];
    vector_[1] = a.vector_[1];
    vector_[2] = a.vector_[2];
  }
  return *this;
}

Vector &Vector::operator+=(const Vector &a) {
  vector_[0] += a.vector_[0];
  vector_[1] += a.vector_[1];
  vector_[2] += a.vector_[2];
  return *this;
}

Vector &Vector::operator-=(const Vector &a) {
  vector_[0] -= a.vector_[0];
  vector_[1] -= a.vector_[1];
  vector_[2] -= a.vector_[2];
  return *this;
}

// friend functions
double operator*(const Vector &a, const Vector &b) {
  return a.vector_[0] * b.vector_[0] + a.vector_[1] * b.vector_[1]
     + a.vector_[2] * b.vector_[2];
}

Vector operator*(const Vector &a, const double k) {
  return Vector(a.vector_[0] * k, a.vector_[1] * k, a.vector_[2] * k);
}

std::ostream &operator<<(std::ostream &out, const Vector &a) {
  out << "(" << a.vector_[0] << "," << a.vector_[1] <<
      "," << a.vector_[2] << ")";
  return out;
}

// non-member functions
Vector operator+(const Vector &a, const Vector &b) {
  Vector temp(a);
  temp += b;
  return temp;
}

Vector operator-(const Vector &a, const Vector &b) {
  Vector temp(a);
  temp -= b;
  return temp;
}

Vector operator*(const double k, const Vector &a) {
  return a * k;
}

}  // namespace vector333
