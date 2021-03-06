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

int vset(float v[4], float v0, float v1, float v2, float v3) {
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
    return 1;
}

int vinvert(float v[4], float result[4]) {
    for (int i = 0; i < 4; i++) {
        result[i] = -v[i];
    }
    return 1;
}

int vadd(float v0[4], float v1[4], float result[4]) {
    for (int i = 0; i < 4; i++) {
        result[i] = v0[i] + v1[i];
    }
    return 1;
}

int vsub(float v0[4], float v1[4], float result[4]) {
    vinvert(v1, result);
    return vadd(v0, result, result);
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

int vrotate(float v[4], float q[4], float result[4]) {
    float p[4] = {0.0, v[0], v[1], v[2]};
    float temp[4];
    qmult(q, p, temp);
    float qconj[4];
    qconjugate(q, qconj);
    qmult(temp, qconj, result);
    q2v(result, result);
    return 1;
}

int vcross(float v0[4], float v1[4], float result[4]) {
    float q0[4], q1[4];
    vcopy(v0, q0); vcopy(v1, q1);

    result[0] = q0[1]*q1[2] - q0[2]*q1[1];
    result[1] = q0[2]*q1[0] - q0[0]*q1[2];
    result[2] = q0[0]*q1[1] - q0[1]*q1[0];
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

float area(float v0[4], float v1[4], float normal[4]) {
    float area[4];
    vcross(v0, v1, area);
    int sign = signum(dot(area, normal));
    return sign * mag(area);
}

int bary(float v0[4], float v1[4], float v2[4], float bary[4], float result[4]) {
    console_log(Debug, "bary=[%f %f %f]\n", bary[0], bary[1], bary[2]);
    float scaled[4];
    vscale(v0, bary[0], result);
    vscale(v1, bary[1], scaled);
    vadd(result, scaled, result);
    vscale(v2, bary[2], scaled);
    vadd(result, scaled, result);
    return 1;
}