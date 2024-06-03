/* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX6
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program accepts a filename as a single command-line argument.
* Then, it reads the file, copying the contents of the file to stdout
* in reverse order, character by character (or, more precisely, byte by byte).
*/

#include <stdio.h>    // printf, I/O
#include <stdlib.h>   // EXIT_SUCCESS or EXIT_FAILURE

/* main - runs program described
*
* @param argc
*            number of strings on the command line
* @param argv
*             array containing pointers to the arguments as strings
*/
int main(int argc, char *argv[]) {
  // user inputted correct number of arguments
  if (argc != 2) {
    fprintf(stderr, "Invalid Argument: Too Many or Too Few Arguments\n");
    return EXIT_FAILURE;
  }

  FILE *pFile;    // file pointer
  long size;      // number of bytes in file
  char buffer;    // buffer to store character
  size_t result;  // number of bytes read
  int index = 0;  // character index

  // open file
  pFile = fopen(argv[1], "rb");
  if (pFile==NULL) {
    perror("Error Opening File");
    return EXIT_FAILURE;

  // if true, get size
  } else {
    fseek(pFile, index, SEEK_END);
    size = ftell(pFile);
  }

  // read file in reverse order byte-by-byte
  while (size > 0) {
    fseek(pFile, --index, SEEK_END);
    result = fread(&buffer, 1, 1, pFile);

    if (result != 1) {
      perror("Error Reading File");
      return EXIT_FAILURE;
    }

    printf("%c", buffer);
    size--;
  }

  printf("\n");

  fclose(pFile);
  return EXIT_SUCCESS;
}
