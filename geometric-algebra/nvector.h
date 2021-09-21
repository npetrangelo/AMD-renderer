#include <math.h>
#include "vector.h"
#pragma once

typedef struct {
    short len;
    vector* arr[];
} nvector;

nvector* univector(vector* v1);
nvector* bivector(vector* v1, vector* v2);
nvector* trivector(vector* v1, vector* v2, vector* v3);

nvector* nvadd(nvector* v1, nvector* v2);
