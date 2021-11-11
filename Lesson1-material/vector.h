#pragma once

int vcopy(float from[4], float to[4]);
int vset(float v[4], float v0, float v1, float v2, float v3);

// Vector math functions.
int vinvert(float v[4], float result[4]);
int vadd(float v0[4], float v1[4], float result[4]);
int vsub(float v0[4], float v1[4], float result[4]);
int vscale(float v[4], float s, float result[4]);
int vlerp(float v0[4], float v1[4], float t, float result[4]);
int norm(float v[4], float result[4]);
int vrotate(float v[4], float q[4], float result[4]);
int vcross(float v0[4], float v1[4], float result[4]);
float dot(float v0[4], float v1[4]);
float mag(float v[4]);