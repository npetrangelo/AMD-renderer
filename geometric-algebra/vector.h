#include <math.h>
#pragma once

typedef struct {
    short len;
    double arr[];
} vector;

vector* vector2(double x, double y);
vector* vector3(double x, double y, double z);
vector* vector4(double x, double y, double z, double w);

vector* vadd(vector* v1, vector* v2);
double* vdot(vector* v1, vector* v2);