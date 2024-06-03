// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX4
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// This program tests NthPrime (a function that calculates
// the nth prime number).

#include "NthPrime.h"
#define MAX 32767  // int16_t max value

// main - runs program described
//
// @param argc
//            number of strings on the command line
// @param argv
//             array containing pointers to the arguments as strings
//
int main() {
  int16_t n;
  // Invalid Inputs
  printf("%d-th prime number is %ld.\n", -1, NthPrime(-1));
  printf("%d-th prime number is %ld.\n", 0, NthPrime(0));


  // Valid Inputs
  // Small Values
  for (n = 1; n < 5; n++) {
    printf("%d-th prime number is %ld.\n", n, NthPrime(n));
  }

  // Large Values
  printf("%d-th prime number is %ld.\n", 25, NthPrime(25));
  printf("%d-th prime number is %ld.\n", 50, NthPrime(50));
  printf("%d-th prime number is %ld.\n", 100, NthPrime(100));
  return EXIT_SUCCESS;
}
