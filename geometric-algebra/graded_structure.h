#include <math.h>
#pragma once

/**
 * Index bitmap:
 *   0b0 -> scalar
 *  0b01 -> e1
 *  0b10 -> e2
 *  0b11 -> e1^e2
 * 0b100 -> e3
 * 0b101 -> e3^e1
 * 0b110 -> e2^e3
 * 0b111 -> e1^e2^e3
 */
typedef struct {
    unsigned int space;
    double *arr;
} gradedStructure;

// Create and destroy multivectors.
void free_gradedStructure(gradedStructure *g);
gradedStructure* make_vector(unsigned int space, ...);

// Handy shortcuts for creating vectors.
gradedStructure* vector2(double x, double y);
gradedStructure* vector3(double x, double y, double z);
gradedStructure* vector4(double x, double y, double z, double w);

// Graded structure math functions.
gradedStructure* gadd(gradedStructure* g1, gradedStructure* g2);
gradedStructure* wedge(gradedStructure* g1, gradedStructure* g2);
double gdot(gradedStructure* g1, gradedStructure* g2);
