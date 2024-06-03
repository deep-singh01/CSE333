# Copyright (c) 2024, Deepesh Singh. All rights reserved.
#
# CSE 333: EX16
#
# Name: Deepesh Singh
# Email: dsingh01@uw.edu

CXX = g++
CPPFLAGS = -Wall -g -std=c++11
PROGS = ex16

all: $(PROGS)
	
ex16: ex16.o Listen.o
	$(CXX) $(CPPFLAGS) -o $@ $^

ex16.o: ex16.cc Listen.h
	$(CXX) $(CPPFLAGS) -c $<

Listen.o: Listen.cc Listen.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf ex16 *.o *~ ex16.dSYM