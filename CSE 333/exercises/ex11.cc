/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX11
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program prompts the user to type in 6 doubles, reads those doubles
* from stdin into a std::vector of doubles, sorts the vector using std::sort,
* and then prints out the sorted vector.
*/

#include <iostream>   // cout, cin
#include <cstdlib>    // EXIT_SUCCESS or EXIT_FAILURE
#include <vector>     // vector
#include <algorithm>  // sort

using namespace std;

// number of input values
const int kNumInputs = 6;

// reads input from the user
// throws an error if the input is not a double
template <typename T>
T ReadValue(istream& in);

/* main - runs program described
*
* @param argc
*            number of strings on the command line
* @param argv
*             array containing pointers to the arguments as strings
*/
int main(int argc, char** argv) {
  // user inputted incorrect number of arguments
  if (argc != 1) {
    printf("Invalid Argument: Too Many or Too Few Arguments\n");
    return EXIT_FAILURE;
  }
  int i;
  vector<double> v;

  // read 6 doubles from user
  cout << "Enter " << kNumInputs << " doubles:" << endl;
  for (i = 0; i < kNumInputs; i++) {
    v.push_back(ReadValue<double>(cin));
  }

  // sort vector in ascending order
  sort(v.begin(), v.end());

  // print out sorted doubles
  printf("Your sorted doubles are:\n");
  for (auto number : v) {
    cout << number << "\n";
  }

  return EXIT_SUCCESS;
}

template <class T> T ReadValue(istream& in) {
  T next;
  in >> next;
  if (!in.good()) {
    cerr << "Couldn't handle input; conversion error or EOF." << endl;
    exit(EXIT_FAILURE);
  }
  return next;
}
