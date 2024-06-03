/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX12
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* This program reads a text file and counts the individual words in the file.
* After reading the entire file, it prints a list of the words sorted by the words,
* and the number of times each word appears in the file.
*/

#include <iostream>   // cout, cin
#include <cstdlib>    // EXIT_SUCCESS or EXIT_FAILURE
#include <fstream>    // ifstream
#include <string>     // string
#include <map>        // map

using namespace std;

// reads file and prints the words and their counts
void ReadAndPrintFile(string filename);

// prints the word count
void PrintWordCount(map<string, int> word_count);

/* main - runs program described
*
* @param argc
*            number of strings on the command line
* @param argv
*             array containing pointers to the arguments as strings
*/
int main(int argc, char** argv) {
  // user inputted incorrect number of arguments
  if (argc != 2) {
    cout << "Invalid Number of Arguments: 2 Needed" << endl;
    return EXIT_FAILURE;
  }

  string filename = string(argv[1]);

  ReadAndPrintFile(filename);
  return EXIT_SUCCESS;
}

void ReadAndPrintFile(string filename) {
  ifstream file(filename);
  string word;
  map<string, int> word_count;

  if (file.is_open()) {
    // read file and count words
    while (file >> word) {
      word_count[word]++;
    }
    file.close();

  } else {
    cout << "Error Opening File" << endl;
    exit(EXIT_FAILURE);
  }

  PrintWordCount(word_count);
}

void PrintWordCount(map<string, int> word_count) {
  for (auto word : word_count) {
    cout << word.first << " " << word.second << endl;
  }
}
