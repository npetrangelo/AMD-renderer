#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "utility.h"
#include "quaternion.h"
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

int vinvert(float v[4], float result[4]) {
    for (int i = 0; i < 4; i++) {
        result[i] = -v[i];
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

int norm(float v[4], float result[4]) {
    float m = mag(v);
    if (m == 0.0) {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        result[i] = v[i] / m;
    }
    return 1;
}

int rotate(float v[4], float axis[4], float angle, float result[4]) {
    if (!norm(axis, axis)) {
        return 0;
    }

    float p[4] = {0.0, v[0], v[1], v[2]};
    float temp[4];

    float s = sin(angle);
    float q[4] = {cos(angle), s*axis[0], s*axis[1], s*axis[2]};
    qmult(q, p, temp);
    qconjugate(q, q);
    qmult(temp, q, result);
    q2v(result, result);
    return 1;
}

float dot(float v0[4], float v1[4]) {
    float result = 0;
    for (int i = 0; i < 4; i++) {
        result += v0[i]*v1[i];
    }
    return result;
}

float mag(float v[4]) {
    return sqrt(dot(v, v));
}