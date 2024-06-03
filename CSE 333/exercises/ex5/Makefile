# Copyright (c) 2024, Deepesh Singh. All rights reserved.
#
# CSE 333: EX5
#
# Name: Deepesh Singh
# Email: dsingh01@uw.edu
#
# This is the Makefile for the ex5 program. It compiles the ex5 program.

CC = gcc
CFLAGS = -Wall -g -std=c17
HEADERS = NthPrime.h
SRCS = ex5.c NthPrime.c
OBJS = $(SRCS:.c=.o)

all: ex5

ex5: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ex5 *.o *~
