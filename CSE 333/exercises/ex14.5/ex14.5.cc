/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX14.5
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program tests the constructors, copy constructor, and operator 
* overloading of the Vector class as well as when they are used.
*/

#include <iostream>   // cout, cin
#include <cstdlib>    // EXIT_SUCCESS or EXIT_FAILURE

#include "Vector.h"

using namespace std;
using namespace vector333;

/* main - runs program described
*
* @param argc
*            number of strings on the command line
* @param argv
*             array containing pointers to the arguments as strings
*/
int main(int argc, char** argv) {
  // user inputted correct number of arguments
  if (argc != 1) {
    printf("Invalid Argument: Too Many or Too Few Arguments\n");
    return EXIT_FAILURE;
  }

  // constructor vs operator(const double x, const double y, const double z)
  Vector b(2, 3, 4);

  Vector a;
  a(1, 2, 3);

  // copy vs operator(const Vector &a)
  Vector copy2(b);
  cout << copy2 << endl << endl;
  Vector copy;
  copy(a);

  return EXIT_SUCCESS;
}
