# Copyright (c) 2024, Deepesh Singh. All rights reserved.
#
# CSE 333: EX14.5
#
# Name: Deepesh Singh
# Email: dsingh01@uw.edu
#
# Vector (ex14.5) Makefile

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = ex14.5

all: $(PROGS)

ex14.5: ex14.5.o Vector.o
	$(CXX) $(CPPFLAGS) -o $@ $^

ex14.5.o: ex14.5.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

Vector.o: Vector.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o *~ *.dSYM $(PROGS)