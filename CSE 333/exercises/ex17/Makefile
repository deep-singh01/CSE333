# Copyright ©2024 Hannah c. Tang.  All rights reserved.  Permission is
# hereby granted to students registered for University of Washington
# CSE 333 for use solely during Spring Quarter 2024 for purposes of
# the course.  No other use, copying, distribution, or modification
# is permitted without prior written consent. Copyrights for
# third-party components of this work must be honored.  Instructors
# interested in reusing these course materials should contact the
# author.
#
# CSE 333: EX17
#
# Name: Deepesh Singh
# Email: dsingh01@uw.edu

CXX = g++
OBJS = SimpleQueue.o ex17.o
EXE  = ex17
HEADERS = SimpleQueue.h
CPPFLAGS = -Wall -g -std=c++17
LDFLAGS += -pthread

# default target
$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS) $(LDFLAGS)

# source files
%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM