/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX9
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
  std::cout << "a.x: " << a.get_x();
  std::cout << " a.y: " << a.get_y();
  std::cout << " a.z: " << a.get_z() << std::endl;

  std::cout << "b: " << b << std::endl;
  std::cout << "b.x: " << b.get_x();
  std::cout << " b.y: " << b.get_y();
  std::cout << " b.z: " << b.get_z() << std::endl;

  // add vectors
  Vector c = a + b;
  std::cout << "a + b: " << c << std::endl;

  // subtract vectors
  Vector d = a - b;
  std::cout << "a - b: " << d << std::endl;

  // dot product
  double dot = a * b;
  std::cout << "a * b: " << dot << std::endl;

  // scalar multiplication
  Vector e = a * 2;
  std::cout << "a * 2: " << e << std::endl;
  std::cout << "e == 2 * a: " << 2 * a << std::endl;

  // new vector values
  a += x;
  std::cout << "a += x: " << a << std::endl;
  b -= x;
  std::cout << "b -= x: " << b << std::endl;

  std::cout << "That's all Folks!" << std::endl;
  return EXIT_SUCCESS;
}
