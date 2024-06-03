/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX10
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program tests the constructors, destructors, operators including assignment and stream output, 
* and a simple user-defined namespace of Vector.
*/

#include <iostream>   // cout, cin
#include <cstdlib>    // EXIT_SUCCESS or EXIT_FAILURE

#include "Vector.h"

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

  // create two vectors
  Vector a(1, 2, 3);
  Vector b(4, 5, 6);
  Vector x(1, 1, 1);

  // print vectors
  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;

  // add vectors
  Vector c = a + b;
  std::cout << "a + b: " << c << std::endl;            // (5, 7, 9)

  // subtract vectors
  Vector d = a - b;
  std::cout << "a - b: " << d << std::endl;            // (-3, -3, -3)

  // dot product
  double dot = a * b;
  std::cout << "a * b: " << dot << std::endl;          // 32

  // scalar multiplication
  Vector e = a * 2;
  std::cout << "a * 2: " << e << std::endl;            // (2, 4, 6)
  std::cout << "e == 2 * a: " << 2 * a << std::endl;   // (2, 4, 6)

  // new vector values
  a += x;
  std::cout << "a += x: " << a << std::endl;           // (2, 3, 4)
  b -= x;
  std::cout << "b -= x: " << b << std::endl;           // (3, 4, 5)

  std::cout << "That's all Folks!" << std::endl;
  return EXIT_SUCCESS;
}
