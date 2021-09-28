#include <math.h>
#include "vector.h"
#pragma once

typedef struct {
    short len;
    vector* *arr;
} blade;

// Create and destroy vectors.
void free_blade(blade *b);
blade* make_blade(int count, ...);

// Handy shortcuts for creating blades.
blade* univector(vector* v1);
blade* bivector(vector* v1, vector* v2);
blade* trivector(vector* v1, vector* v2, vector* v3);

// Blade math functions.
blade* badd(blade* b1, blade* b2);
blade* bmultiply(blade* b1, blade* b2);
int bmag(blade* b, double* mag);
