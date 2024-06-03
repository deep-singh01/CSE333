/*
 * Name: Deepesh Singh
 * Email: dsingh01@uw.edu
 *
 * Copyright ©2024 Yiqing Wang.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 * 
 * This program demonstrates the use of inheritance in C++.
 */

#include <iostream>

#include "Cat.h"
#include "Abyssinian.h"

using std::cout;
using std::endl;

int main() {
  Cat c("Sushi", 4, "Gold");
  cout << c.getCatInfo() << endl;

  Abyssinian a("Mittens", 3, "Brown", "Abyssinian");
  cout << a.getCatInfo() << endl;
  return EXIT_SUCCESS;
}
