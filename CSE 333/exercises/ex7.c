/* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX7
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program prints the elements of a given array in ascending order
* by utilizing a function that copies and sorts the given array into
* another element-by-element using insertion sort.
*/

#include <stdio.h>    // printf
#include <stdlib.h>   // EXIT_SUCCESS or EXIT_FAILURE
#include <dirent.h>   // directory
#include <string.h>   // string
#include <unistd.h>   // POSIX File Operations
#include <fcntl.h>    // File Control
#include <errno.h>    // Error Handling

#define READBUFSIZE 1024

// Reads a Given Directory and Prints its Text Files
// dir: directory to read & dir_name: name of directory
static void ReadDirAndPrintFiles(DIR *dir, char *dir_name);

// Prints the Contents of a Given Text File
// file_name: name of file to print
static void PrintFile(char *file_name);

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

  DIR *dir;

  // open directory
  dir = opendir(argv[1]);
  if (dir == NULL) {
    perror("Error Opening Directory");
    return EXIT_FAILURE;
  }

  // read directory and print its files
  ReadDirAndPrintFiles(dir, argv[1]);

  // close directory
  closedir(dir);
  return EXIT_SUCCESS;
}


static void ReadDirAndPrintFiles(DIR *dir, char* dir_name) {
  struct dirent *entry;
  int path_name_len;
  int dir_name_length = strlen(dir_name);

  // read directory
  while ((entry = readdir(dir)) != NULL) {
    path_name_len = dir_name_length + strlen(entry->d_name);

    // Check if the filename ends with ".txt"
    if (strlen(entry->d_name) >= 4 &&
        strcmp(entry->d_name + (strlen(entry->d_name) - 4), ".txt") == 0) {
      char *file_name = (char*) malloc(sizeof(char) * (path_name_len + 2));
      if (file_name == NULL) {
        perror("Error Allocating Memory\n");
        exit(EXIT_FAILURE);
      }

      // create file path
      snprintf(file_name, path_name_len + 2, "%s/%s", dir_name, entry->d_name);
      PrintFile(file_name);  // print contents of file
      free(file_name);
    }
  }
}

static void PrintFile(char *file_name) {
  int fd;
  char buf[READBUFSIZE];
  int result, bytes_left;

  // open file
  fd = open(file_name, O_RDONLY);
  if (fd == -1) {
    perror("Error Opening File");
    exit(EXIT_FAILURE);
  }

  // get file size
  bytes_left = lseek(fd, 0, SEEK_END);
  if (bytes_left == -1) {
    perror("Error Getting File Size");
    exit(EXIT_FAILURE);
  }

  lseek(fd, 0, SEEK_SET); // rest file pointer to beginning

  while (bytes_left > 0) {
    // read file
    result = read(fd, buf, READBUFSIZE);

    if (result == -1) {
      // a real error happened, so return an error result
      if (errno != EINTR) {
        perror("Error Reading File");
        exit(EXIT_FAILURE);
      }
      // EINTR happened, so do nothing and try again
      continue;
    } else if (result == 0) {
      // EOF reached, so stop reading
      break;
    }

    // write to stdout
    if (fwrite(buf, 1, result, stdout) < result) {
      perror("Error Writing to File");
      exit(EXIT_FAILURE);
    }

    fwrite("\n", sizeof(char), 1, stdout);
    bytes_left -= result;
  }

  // close file
  if (close(fd) == -1) {
    perror("Error Closing File");
    exit(EXIT_FAILURE);
  }
}
