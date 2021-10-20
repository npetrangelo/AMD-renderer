#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "utility.h"
#include "vector.h"

int vcopy(float from[4], float to[4]) {
    for (int i = 0; i < 4; i++) {
        to[i] = from[i];
    }
    return 1;
}

int vadd(float v0[4], float v1[4], float result[4]) {
    for (int i = 0; i < 4; i++) {
        result[i] = v0[i] + v1[i];
    }
    return 1;
}

int vscale(float v[4], float s, float result[4]) {
    for (int i = 0; i < 4; i++) {
        result[i] = v[i]*s;
    }
    return 1;
}

int vlerp(float v0[4], float v1[4], float t, float result[4]) {
    for (int i = 0; i < 4; i++) {
        result[i] = flerp(v0[i], v1[i], t);
    }
    return 1;
}

float vdot(float v0[4], float v1[4]) {
    float result = 0;
    for (int i = 0; i < 4; i++) {
        result += v0[i]*v1[i];
    }
    return result;
}

float vmag(float v[4]) {
    return sqrt(vdot(v, v));
}