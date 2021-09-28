#include <math.h>
#include "vector.h"
#include "blade.h"
#pragma once

typedef struct {
    short rows;
    short cols;
    double* *arr;
} matrix;

void free_matrix(matrix *m);
matrix* to_matrix(blade* b);
int is_square(matrix* m);
matrix* msub(matrix* m, int col, int row);
int mdet(matrix* m, double* result);
void mprint(matrix* m);