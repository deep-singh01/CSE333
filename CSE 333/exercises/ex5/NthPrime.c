// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX5
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// This program calculates the nth prime number
// where is n is inputted by the user.

#include "NthPrime.h"

// checks if inputted number is prime (prime)
static bool checkIfPrime(int64_t prime);

int64_t NthPrime(int16_t n) {
  if (n <= 0) {
    printf("Invalid Input.\n");
    return -1;
  }

  int16_t i = 0;
  int64_t prime = 2;

  while (i < n) {
    if (checkIfPrime(prime)) {
        i++;
    }
    prime++;
  }

  return prime - 1;
}

static bool checkIfPrime(int64_t prime) {
  int64_t i;

  for (i = 2; i < prime; i++) {
    if (prime % i == 0) {
      return false;
    }
  }

  return true;
}
