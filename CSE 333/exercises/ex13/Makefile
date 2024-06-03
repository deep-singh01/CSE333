# Copyright (c) 2024, Deepesh Singh. All rights reserved.
#
# CSE 333: EX13
#
# Name: Deepesh Singh
# Email: dsingh01@uw.edu
#
# Coordinates Makefile

CXX = g++
CPPFLAGS = -g -Wall -std=c++11
PROGS = ex13

all: $(PROGS)

ex13: ex13.o Cartesian.o Polar.o
	$(CXX) $(CPPFLAGS) $^ -o $@

ex13.o: ex13.cc Cartesian.h Polar.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Cartesian.o: Cartesian.cc Cartesian.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Polar.o: Polar.cc Polar.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf *.o *~ *.dSYM $(PROGS)
