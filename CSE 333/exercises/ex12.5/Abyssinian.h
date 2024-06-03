/*
* Copyright (c) 2024, Deepesh Singh. All rights reserved.
*
* CSE 333: EX12.5
*
* Name: Deepesh Singh
* Email: dsingh01@uw.edu
*
* Abyssinian Cat Header file
*/

#ifndef ABYSSINIAN_H_
#define ABYSSINIAN_H_

#include <string>

#include "Cat.h"

class Abyssinian : public Cat {
 public:
  Abyssinian(const std::string &n, int a, const std::string &fc,
    const std::string &b)
    : Cat(n, a, fc), breed_(b) { };

  virtual std::string getCatInfo() const override;

 private:
  std::string breed_;
};

#endif  // ABYSSINIAN_H_