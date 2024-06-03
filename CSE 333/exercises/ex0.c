// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX0
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// One way to estimate π is to use the following infinite series,
// which was discovered by Nilakantha in the 15th century:
// π = 3 + (4 / (2 x 3 x 4)) - (4 / (4 x 5 x 6)) + (4 / (6 x 7 x 8)) - ...
//
// This program utilizes this series to estimate π by adding together terms 0
// through n, inclusive, and prints out that estimate to 20 decimal places.

#include <stdio.h>    // printf
#include <stdlib.h>   // EXIT_SUCCESS or EXIT_FAILURE
#include <string.h>   // strlen
#include <stdbool.h>  // bool
#include <ctype.h>    // isdigit

//
// main - runs program described
//
// @param argc
//            number of strings on the command line - should equal 2
// @param argv
//             array containing pointers to the arguments as strings
//             * argv[1] = n
//
int main(int argc, char* argv[]) {
  int i;
  int num_iterations = atoi(argv[1]);
  int size = strlen(argv[1]);
  double n = 1;
  double pi = 3;

  // checks if first character is not a digit or '-' for negative numbers
  bool contains_letter_or_symbol = !(isdigit(argv[1][0])) && argv[1][0] != '-';

  // checks if num_iterations is an integer
  for (i = 1; i < size; i++) {
    if (!(isdigit(argv[1][i]))) {
      contains_letter_or_symbol = true;
    }
  }

  // user inputted too many arguments
  if (argc > 2) {
    printf("Invalid Argument: Too Many Arguments\n");
    return EXIT_FAILURE;

  // user did not input an integer
  } else if (contains_letter_or_symbol) {
    printf("Invalid Argument: Not an Integer\n");
    return EXIT_FAILURE;

  // user inputted negative number
  } else if (num_iterations < 0 && argv[1][0] == '-') {
    printf("Invalid Argument: Negative Number\n");
    return EXIT_FAILURE;

  // user inputted too large of number
  // max acceptable value: 10000000272564223
  } else if (num_iterations < 0) {
    printf("Invalid Argument: Too Large - Overflow\n");
    return EXIT_FAILURE;
  }

  printf("Our estimate of Pi is ");
  for (i = 1; i <= num_iterations; i++) {
    // if n is odd, (-1)^(n+1) = 1 -> add
    if (i % 2 == 1) {
      pi +=  (4 / (2*n * (2*n + 1) * (2*n+2)));

    // if n is even, (-1)^(n+1) = -1 -> subtract
    } else {
      pi -=  (4 / (2*n * (2*n + 1) * (2*n+2)));
    }
    n++;
  }

  printf("%.20lf\n", pi);
  return EXIT_SUCCESS;
}
