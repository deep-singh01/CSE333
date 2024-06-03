/*
 * Copyright ©2024 Hannah C. Tang.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600
#define  _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#include "libhw1/CSE333.h"
#include "./CrawlFileTree.h"
#include "./DocTable.h"
#include "./MemIndex.h"

//////////////////////////////////////////////////////////////////////////////
// Helper function declarations, constants, etc
static void Usage(void);
// P
static void ProcessQueries(DocTable* dt, MemIndex* mi);
static int GetNextLine(FILE* f, char** ret_str);


//////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage();
  }

  DocTable* dt;
  MemIndex* mi;

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - Crawl from a directory provided by argv[1] to produce and index
  //  - Prompt the user for a query and read the query from stdin, in a loop
  //  - Split a query into words (check out strtok_r)
  //  - Process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  //
  // Note that you should make sure the fomatting of your
  // searchshell output exactly matches our solution binaries
  // to get full points on this part.

  printf("Indexing \'%s\'\n", argv[1]);

  // check if the directory is successfully crawled
  if (!(CrawlFileTree(argv[1], &dt, &mi)) || dt == NULL ||
      mi == NULL) {
    Usage();
  }
  Verify333(dt != NULL);
  Verify333(mi != NULL);

  // process queries
  ProcessQueries(dt, mi);

  // end process
  printf("shutting down...\n");

  DocTable_Free(dt);
  MemIndex_Free(mi);

  return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////////
// Helper function definitions

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

static void ProcessQueries(DocTable* dt, MemIndex* mi) {
  char* buf;
  ssize_t buf_size;
  char* res_ptr;
  char* token;
  int index;
  LinkedList* docs_found;

  while (1) {
    printf("enter query:\n");

    // read the query from stdin
    buf = NULL;
    buf_size = GetNextLine(stdin, &buf);

    // exit processing (ctrl-D)
    if (buf_size == EOF) {
      free(buf);
      break;
    }

    // convert the query to lowercase
    for (int i = 0; i < buf_size; i++) {
      buf[i] = tolower(buf[i]);
    }

    index = 0;
    char* queries[buf_size];
    token = strtok_r(buf, " ", &res_ptr);

    // split the query into words
    while (token != NULL) {
       queries[index] = token;
       token = strtok_r(NULL, " ", &res_ptr);
       index++;
    }

    // change last character from '\n' to '\0' if necessary
    if (queries[index - 1][strlen(queries[index - 1]) - 1] == '\n') {
      queries[index - 1][strlen(queries[index - 1]) - 1] = '\0';
    }

    docs_found = MemIndex_Search(mi, queries, index);
    free(buf);

    // check if the query is found in the index
    if (docs_found) {
      SearchResult* sr;
      int rank;
      char* doc_name;
      LLIterator* iter = LLIterator_Allocate(docs_found);

      // print out the results
      while (LLIterator_IsValid(iter)) {
        LLIterator_Get(iter, (LLPayload_t*) &sr);
        rank = sr->rank;
        doc_name = DocTable_GetDocName(dt, sr->doc_id);

        printf("  %s (%d)\n", doc_name, rank);

        LLIterator_Next(iter);
      }

      LLIterator_Free(iter);
      LinkedList_Free(docs_found, &free);
    }
  }
}

static int GetNextLine(FILE *f, char **ret_str) {
  size_t size;
  return getline(ret_str, &size, stdin);
}
