// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX1
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// This program prints the elements of a given array in ascending order
// by utilizing a function that copies and sorts the given array into
// another element-by-element using insertion sort.

#include <stdio.h>    // printf
#include <stdlib.h>   // EXIT_SUCCESS or EXIT_FAILURE
#include <stdint.h>   // int64_t
#include <string.h>   // strlen
#include <stdbool.h>  // bool
#include <ctype.h>    // isdigit

// Size of data arrays
#define ARRAY_SIZE 12

void CopyAndSort(__int64_t src[], __int64_t dst[], int size);

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
    int64_t dst[ARRAY_SIZE];
    int64_t src[ARRAY_SIZE] = {3, 2, -5, 7, 17, 42, 6, 333, 7, 8, -8, 6};

    CopyAndSort(src, dst, ARRAY_SIZE);

    // printing numbers
    for (i = 0; i < ARRAY_SIZE-2; i++) {
        printf("%ld ", dst[i]);
    }

    printf("%ld\n", dst[ARRAY_SIZE-1]);
}

//
// Copies and sorts source array into destincation array
// element-by-element using insertion sort
//
// @param src
//            source array (unsorted)
// @param dst
//             destination array (sorted)
// @param size
//             length of src and dst
//
void CopyAndSort(__int64_t src[], __int64_t dst[], int size) {
    int j, k, val;

    // insertion sort one-by-one
    for (j = 1; j < size; j++) {
        dst[j] = src[j];
        val = dst[j];
        k = j-1;

        while (k >= 0 && dst[k] > val) {
            dst[k+1] = dst[k];
            k -=1;
        }

        dst[k + 1] = val;
    }
}
