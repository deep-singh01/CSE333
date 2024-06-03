# Copyright (c) 2024, Deepesh Singh. All rights reserved.
#
# CSE 333: EX15
#
# Name: Deepesh Singh
# Email: dsingh01@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++11
PROGS = ex15

all: $(PROGS)
	
ex15: ex15.o Connect.o
	$(CXX) $(CPPFLAGS) -o $@ $^

ex15.o: ex15.cc Connect.h
	$(CXX) $(CPPFLAGS) -c $<

Connect.o: Connect.cc Connect.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf ex15 *.o *~ ex15.dSYM