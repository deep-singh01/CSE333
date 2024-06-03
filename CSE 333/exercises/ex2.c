// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX2
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// This program uses a function to print, in hex, the values of the bytes
// allocated to some variable.

#include <stdio.h>     // printf
#include <stdlib.h>    // EXIT_SUCCESS or EXIT_FAILURE
#include <inttypes.h>  // intX_t types


void PrintBytes(void* mem_addr, int num_bytes);

//
// main - runs program described
//
// @param argc
//            number of strings on the command line
// @param argv
//             array containing pointers to the arguments as strings
//
int main(int argc, char **argv) {
  char     char_val = '0';
  int32_t  int_val = 1;
  float    float_val = 1.0;
  double   double_val  = 1.0;

  typedef struct {
    char     char_val;
    int32_t  int_val;
    float    float_val;
    double   double_val;
  } Ex2Struct;

  Ex2Struct struct_val = { '0', 1, 1.0, 1.0 };

  PrintBytes(&char_val, sizeof(char));
  PrintBytes(&int_val, sizeof(int32_t));
  PrintBytes(&float_val, sizeof(float));
  PrintBytes(&double_val, sizeof(double));
  PrintBytes(&struct_val, sizeof(struct_val));

  return EXIT_SUCCESS;
}

//
// Prints, in hex, the first n (num_bytes) values of the bytes
// allocated to some variable
//
// @param mem_addr
//            address of object to be printed
// @param num_bytes
//             number of bytes to be printed
//
void PrintBytes(void* mem_addr, int num_bytes) {
    if (mem_addr == NULL || num_bytes <= 0) {
        printf("Invalid input\n");
        return;
    }
    int i;
    printf("The %d bytes starting at %p are:", num_bytes, mem_addr);
    for (i = 0; i < num_bytes; i++) {
        printf(" %02x", *((unsigned char*)mem_addr + i));
    }
    printf("\n");
}
