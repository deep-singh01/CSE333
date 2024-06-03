// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX5
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// Header file for NthPrime

#ifndef NTHPRIME_H_
#define NTHPRIME_H_

#include <stdio.h>     // printf
#include <stdlib.h>    // EXIT_SUCCESS or EXIT_FAILURE
#include <inttypes.h>  // intX_t types
#include <stdbool.h>   // bool type

// NthPrime - returns the nth prime number starting from 2,
// where "n" is the function's input parameter.
// If n is less than or equal to 0, the function will print 
// "Invalid Input." and return -1.
// Ex:
// NthPrime(1) -> 2
// NthPrime(2) -> 3
// NthPrime(3) -> 5, and so on.
//
// @param n
//            the nth prime number to be returned
//
int64_t NthPrime(int16_t n);

#endif  // NTHPRIME_H_
