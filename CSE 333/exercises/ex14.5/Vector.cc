// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX14.5
// Vector
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// Vector (ex14.5) Implementation File

#include <iostream>
#include "Vector.h"

namespace vector333 {

Vector::~Vector() {}

Vector &Vector::operator=(const Vector &a) {
  if (this != &a) {
    this->x_ = a.x_;
    this->y_ = a.y_;
    this->z_ = a.z_;
  }
  return *this;
}

Vector &Vector::operator+=(const Vector &a) {
  this->x_ += a.x_;
  this->y_ += a.y_;
  this->z_ += a.z_;
  return *this;
}

Vector &Vector::operator-=(const Vector &a) {
  this->x_ -= a.x_;
  this->y_ -= a.y_;
  this->z_ -= a.z_;
  return *this;
}

Vector &Vector::operator()(const double x, const double y, const double z) {
  std::cout << "Operator (const double x, const double y, const double z) called\n" << std::endl;
  return *this;
}
Vector &Vector::operator()(const Vector &a) {
  std::cout << "Operator (const Vector &a) called" << std::endl;
  std::cout << "a: " << a << std::endl;
  return *this;
}

Vector operator+(const Vector &a, const Vector &b) {
  Vector temp = a;
  temp += b;
  return temp;
}

Vector operator-(const Vector &a, const Vector &b) {
  Vector temp = a;
  temp -= b;
  return temp;
}

double operator*(const Vector &a, const Vector &b) {
  return a.get_x() * b.get_x() + a.get_y() * b.get_y() + a.get_z() * b.get_z();
}

Vector operator*(const Vector &a, const double k) {
  return Vector(a.get_x() * k, a.get_y() * k, a.get_z() * k);
}

Vector operator*(const double k, const Vector &a) {
  return a * k;
}

std::ostream &operator<<(std::ostream &out, const Vector &a) {
  out << "(" << a.get_x() << "," << a.get_y() << "," << a.get_z() << ")";
  return out;
}

}  // namespace vector333
