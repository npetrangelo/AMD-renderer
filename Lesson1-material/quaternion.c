#include <math.h>
#include "vector.h"
#include "quaternion.h"

int qaxis(float angle, float axis[4], float result[4]) {
    vnorm(axis, result);
    vscale(result, sin(angle), result);
    result[3] = result[2];
    result[2] = result[1];
    result[1] = result[0];
    result[0] = cos(angle);
    return 1;
}

int qeuler(float yaw, float pitch, float roll, float result[4]) {
    float cy = cos(yaw * 0.5);
    float sy = sin(yaw * 0.5);
    float cp = cos(pitch * 0.5);
    float sp = sin(pitch * 0.5);
    float cr = cos(roll * 0.5);
    float sr = sin(roll * 0.5);

    result[0] = cy * cp * cr   +   sy * sp * sr;
    result[1] = cy * cp * sr   -   sy * sp * cr;
    result[2] = sy * cp * sr   +   cy * sp * cr;
    result[3] = sy * cp * cr   -   cy * sp * sr;

    return 1;
}

int qconjugate(float q[4], float result[4]) {
    result[0] =  q[0];
    result[1] = -q[1];
    result[2] = -q[2];
    result[3] = -q[3];
    return 1;
}

int qmult(float q0[4], float q1[4], float result[4]) {
    result[0] = (q0[0] * q1[0]) - (q0[1] * q1[1]) - (q0[2] * q1[2]) - (q0[3] * q1[3]);
    result[1] = (q0[1] * q1[0]) + (q0[0] * q1[1]) - (q0[3] * q1[2]) + (q0[2] * q1[3]);
    result[2] = (q0[2] * q1[0]) + (q0[3] * q1[1]) + (q0[0] * q1[2]) - (q0[1] * q1[3]);
    result[3] = (q0[3] * q1[0]) - (q0[2] * q1[1]) + (q0[1] * q1[2]) + (q0[0] * q1[3]);
    return 1;
}

int q2v(float q[4], float v[4]) {
    for (int i = 0; i < 3; i++) {
        v[i] = q[i+1];
    }
    v[3] = 0.0;
    return 1;
}