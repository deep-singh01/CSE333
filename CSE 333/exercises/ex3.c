// Copyright (c) 2024, Deepesh Singh. All rights reserved.
//
// CSE 333: EX3
//
// Name: Deepesh Singh
// Email: dsingh01@uw.edu
//
// This program tests a function that can create points in 3d space.

#include <stdio.h>     // printf
#include <stdlib.h>    // EXIT_SUCCESS or EXIT_FAILURE
#include <inttypes.h>  // intX_t types

typedef struct point_st {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} Point3d;

Point3d* AllocatePoint3d(uint16_t x, uint16_t y, uint16_t z);

//
// main - runs program described
//
// @param argc
//            number of strings on the command line
// @param argv
//             array containing pointers to the arguments as strings
//
int main(int argc, char **argv) {
    Point3d* point = AllocatePoint3d(1, 2, 3);

    if (point == NULL) {
        printf("Memory allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Point3d:\n");
    printf("x: %d\n", point->x);
    printf("y: %d\n", point->y);
    printf("z: %d\n", point->z);

    free(point);
    return EXIT_SUCCESS;
}

//
// Allocate Point3d - creates a new Point3d struct and initializes its fields
//
// @param x
//            x-coordinate of the point
// @param y
//            y-coordinate of the point
// @param z
//            z-coordinate of the point
//
Point3d* AllocatePoint3d(uint16_t x, uint16_t y, uint16_t z) {
    Point3d* point = (Point3d*) malloc(sizeof(Point3d));

    if (point == NULL) {
        printf("Memory allocation Failed\n");
        exit(EXIT_FAILURE);
    }

    point->x = x;
    point->y = y;
    point->z = z;
    return point;
}
