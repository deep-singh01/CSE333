/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX13
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program tests Coordinate and its subclasses.
*/

#include <iostream>
#include <cmath>
#include "Cartesian.h"
#include "Polar.h"

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {
  if (argc != 1) {
    cerr << "Error: Too Many or Few Arguments - " << argv[0] << endl;
    return EXIT_FAILURE;
  }

  Cartesian c1(-2, 3);                              // x = -2, y = 3
  Cartesian c2(4, -7);                              // x = 4, y = -7
  cout << "Cartesian 1: " << c1.ToString() << endl;
  cout << "Cartesian 2: " << c2.ToString() << endl << endl;

  cout << "Distance between Cartesian 1 and Cartesian 2: "
       << c1.Distance(c2) << endl << endl;          // Expected: 11.6619

  Polar p1(4, 0);                                   // r = 4, theta = 0
  Polar p2(1, M_PI / 2);                            // r = 1, theta = pi/2
  cout << "Polar 1: " << p1.ToString() << endl;
  cout << "Polar 2: " << p2.ToString() << endl << endl;

  cout << "Distance between Polar 1 and Polar 2: "
       << p1.Distance(p2) << endl;                  // Expected: 4.12311

  return EXIT_SUCCESS;
}
