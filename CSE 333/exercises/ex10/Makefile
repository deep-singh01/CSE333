# Copyright (c) 2024, Deepesh Singh. All rights reserved.
#
# CSE 333: EX10
#
# Name: Deepesh Singh
# Email: dsingh01@uw.edu
#
# Vector Makefile

CXX = g++
CPPFLAGS = -Wall -g -std=c++17
PROGS = testvector

all: $(PROGS)

testvector: ex10.o Vector.o
	$(CXX) $(CPPFLAGS) -o $@ $^

ex10.o: ex10.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

Vector.o: Vector.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf *.o *~ *.dSYM $(PROGS)
