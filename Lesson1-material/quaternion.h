#include "vector.h"
#pragma once

int qaxis(float angle, float axis[4], float result[4]);
int qeuler(float yaw, float pitch, float roll, float result[4]);
int qconjugate(float q[4], float result[4]);
int qmult(float q0[4], float q1[4], float result[4]);
int q2v(float q[4], float v[4]);