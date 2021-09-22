#include <math.h>
#pragma once

typedef struct {
    short len;
    double *arr;
} vector;

void free_vector(vector *v);

vector* make_vector(int count, ...);

vector* vector2(double x, double y);
vector* vector3(double x, double y, double z);
vector* vector4(double x, double y, double z, double w);

vector* vadd(vector* v1, vector* v2);
int vdot(vector* v1, vector* v2, double* result);