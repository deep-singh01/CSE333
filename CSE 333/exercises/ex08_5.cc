/*
 * Name : Deepesh Singh
 * Email : dsingh01@uw.edu
 * 
 * Copyright ©2024 Jennifer Xu.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <cstdlib>
#include <iostream>  // for cout, endl

void Modify(const int& ref, int* dst);

int main() {
  int a = 5;
  const int b = 10;
  const int *c = &a;
  const int& d = b;

  Modify(d, &a);
  Modify(*c, &a);

  std::cout << "Modified value of a: " << a << std::endl;

  return 0;
}

// Adds the first param to the second param
void Modify(const int& ref, int* dst) {
  *dst += ref;
}

// ======================================
// ====== Comprehension Questions =======
// ======================================
//
// Each of the below questions can be answered in ~20 words (and
// definitely no more than 40).  For reference, the sample solution's
// answers are <20 words.  WE WILL STOP READING IF YOUR ANSWER IS
// >40 WORDS, so keep them concise please :)
//
// 1. What is the difference between "const int *" and "int *const"?
//    The difference between "const int *" and "int *const" is that
//    the former is a pointer to a constant integer, while the latter
//    is a constant pointer to an integer.
//
// 2. List one difference between a pointer and a reference.
//    One difference between a pointer and a reference is that a
//    a pointer can be reassigned to point to a different memory while
//    a reference cannot.
//
//
