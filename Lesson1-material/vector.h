#pragma once

int vcopy(float from[4], float to[4]);

// Vector math functions.
int vadd(float v0[4], float v1[4], float result[4]);
int vinvert(float v[4], float result[4]);
int vscale(float v[4], float s, float result[4]);
int vlerp(float v0[4], float v1[4], float t, float result[4]);
int norm(float v[4], float result[4]);
int rotate(float v[4], float axis[4], float angle, float result[4]);
float dot(float v0[4], float v1[4]);
float mag(float v[4]);