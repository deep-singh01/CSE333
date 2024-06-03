/* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX8
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program prompts the user for a positive integer (strictly > 0) and
* prints out all integers that are factors of that integer.
*/

#include <iostream>   // cout, cin
#include <cstdlib>    // EXIT_SUCCESS or EXIT_FAILURE

using namespace std;  // std::cout, std::cin

// Prints all factors of a given positive integer
static void PrintFactors(int num);

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

  int num;
  cout << "Which positive integer would you like me to factorize? ";
  cin >> num;

  // check if num > 0
  if (num <= 0) {
    cerr << "Invalid Argument: Please Enter a Positive Integer\n";
    return EXIT_FAILURE;
  }

  // print factors
  PrintFactors(num);
  return EXIT_SUCCESS;
}

static void PrintFactors(int num) {
  cout << 1;
  for (int i = 2; i <= num; i++) {
    if (num % i == 0) {
      cout << " " << i;
    }
  }
  cout << endl;
}
