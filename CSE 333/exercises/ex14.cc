/*
 * Copyright ©2024 Hannah C. Tang.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 * 
 * Name: Deepesh Singh
 * Email: dsingh01@uw.edu
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char **argv) {
  // Allocate an integer on the heap, initialize to value 5.
  std::unique_ptr<int> x(new int(5));
  std::cout << "*x is: " << *(x.get()) << std::endl;

  // Allocate a vector of integers on the heap, add some values to
  // that vector, sort the vector, print the values.
  std::unique_ptr<std::vector<int>> v(new std::vector<int>);
  v->push_back(13);
  v->push_back(42);
  v->push_back(17);
  std::sort(v->begin(), v->end());
  std::cout << "sorted v: ";
  for (int &el : *v) {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  // Allocate a vector of (integer pointers) on the stack, add some
  // values to the vector from the heap, print the values.
  std::unique_ptr<std::vector<std::unique_ptr<int>>> v2(new std::vector<std::unique_ptr<int>>);
  v2->push_back(std::unique_ptr<int>(new int(13)));
  v2->push_back(std::unique_ptr<int>(new int(42)));
  v2->push_back(std::unique_ptr<int>(new int(17)));
  std::cout << "unsorted v2: ";
  for (std::unique_ptr<int> &el : *v2) {
    std::cout << *el << " ";
  }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
