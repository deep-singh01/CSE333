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

#include "./QueryProcessor.h"

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

extern "C" {
  #include "./libhw1/CSE333.h"
}

using std::list;
using std::sort;
using std::string;
using std::vector;

namespace hw3 {

// Simplifies both lists to one that only includes commonalities.
static list<DocIDElementHeader> Simplify(const list<DocIDElementHeader>&
    dID_headers, const list<DocIDElementHeader>& temp);

// Updates the final_result by adding headers in dID_headers.
void Update(const list<DocIDElementHeader>& dID_headers, DocTableReader* dtr,
    vector<QueryProcessor::QueryResult>* final_result);

QueryProcessor::QueryProcessor(const list<string>& index_list, bool validate) {
  // Stash away a copy of the index list.
  index_list_ = index_list;
  array_len_ = index_list_.size();
  Verify333(array_len_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader* [array_len_];
  itr_array_ = new IndexTableReader* [array_len_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::const_iterator idx_iterator = index_list_.begin();
  for (int i = 0; i < array_len_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = fir.NewDocTableReader();
    itr_array_[i] = fir.NewIndexTableReader();
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (int i = 0; i < array_len_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

// This structure is used to store a index-file-specific query result.
typedef struct {
  DocID_t doc_id;  // The document ID within the index file.
  int     rank;    // The rank of the result so far.
} IdxQueryResult;

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string>& query) const {
  Verify333(query.size() > 0);

  // STEP 1.
  // (the only step in this file)
  vector<QueryProcessor::QueryResult> final_result;
  DocTableReader* dtr;
  IndexTableReader* itr;
  DocIDTableReader* dIDtr;
  list<DocIDElementHeader> dID_headers;
  bool found;

  for (int i = 0; i < array_len_; i++) {
    dtr = dtr_array_[i];
    itr = itr_array_[i];

    // Look up the first query.
    dIDtr = itr -> LookupWord(query[0]);

    // Query was found.
    if (dIDtr != nullptr) {
      found = true;

      // Get all the docIDs for the first query.
      dID_headers = dIDtr -> GetDocIDList();
      delete dIDtr;

      // Look up the rest of the queries and simplify the results.
      for (size_t j = 1; j < query.size(); j++) {
        dIDtr  = itr -> LookupWord(query[j]);

        // Query was found - simplify the results.
        if (dIDtr != nullptr) {
          dID_headers = Simplify(dID_headers, dIDtr -> GetDocIDList());
          delete dIDtr;

        // Query was not found - break out of the loop.
        } else {
          found = false;
          break;
        }
      }

      // Update the final results.
      if (found) {
        Update(dID_headers, dtr, &final_result);
      }
    }
  }

  // Sort the final results.
  sort(final_result.begin(), final_result.end());
  return final_result;
}

static list<DocIDElementHeader> Simplify(const list<DocIDElementHeader>&
    dID_headers, const list<DocIDElementHeader>& temp) {
  list<DocIDElementHeader> simplified_dID_header;

  // Iterate through dID_headers and temp.
  for (DocIDElementHeader header : dID_headers) {
    for (DocIDElementHeader new_header : temp) {
      // If both lists have the same doc_id, add the num_positions together.
      if (header.doc_id == new_header.doc_id) {
        simplified_dID_header.push_back(DocIDElementHeader(header.doc_id,
          header.num_positions + new_header.num_positions));
      }
    }
  }
  return simplified_dID_header;
}

void Update(const list<DocIDElementHeader>& dID_headers, DocTableReader* dtr,
    vector<QueryProcessor::QueryResult>* final_result) {
  QueryProcessor::QueryResult qr;

  // Iterate through dID_headers and update the final results.
  for (DocIDElementHeader header : dID_headers) {
    qr.rank = header.num_positions;
    Verify333(dtr -> LookupDocID(header.doc_id, &qr.document_name));
    (*final_result).push_back(qr);
  }
}

}  // namespace hw3
