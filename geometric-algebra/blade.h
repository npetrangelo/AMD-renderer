#include <math.h>
#include "vector.h"
#pragma once

typedef struct {
    short len;
    vector* arr[];
} blade;

blade* univector(vector* v1);
blade* bivector(vector* v1, vector* v2);
blade* trivector(vector* v1, vector* v2, vector* v3);

blade* badd(blade* v1, blade* v2);
