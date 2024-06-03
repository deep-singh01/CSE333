/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX12.5
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Abyssinian Cat Implementation file
*/

#include "Cat.h"
#include "Abyssinian.h"

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

string Abyssinian::getCatInfo() const {
  stringstream ss;
  ss <<  "Name: " << get_name() << ", Age: " << get_age()
     << ", Fur Color: " << get_fur_color() << ", Breed: " << breed_;
  return ss.str();
}