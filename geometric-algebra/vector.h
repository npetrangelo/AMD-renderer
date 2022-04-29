#include <math.h>
#pragma once

typedef struct {
    short len;
    double *arr;
} vector;

// Create and destroy vectors.
void free_vector(vector *v);
vector* make_vector(int count, ...);

// Handy shortcuts for creating vectors.
vector* vector2(double x, double y);
vector* vector3(double x, double y, double z);
vector* vector4(double x, double y, double z, double w);

// Vector math functions.
int vadd(vector* v1, vector* v2, vector* result);
int vscale(vector* v, double s, vector* result);
int vdot(vector* v1, vector* v2, double* result);
int vmag(vector* v, double* result);
int vlerp(vector* v0, vector* v1, float t, vector* result);