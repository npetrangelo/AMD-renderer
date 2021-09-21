#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

vector* vector2(double x, double y) {
    vector *v = malloc(sizeof(short) + 2*sizeof(double));
    v->len = 2;
    v->arr[0] = x;
    v->arr[1] = y;
    return v;
}

vector* vector3(double x, double y, double z) {
    vector *v = malloc(sizeof(short) + 3*sizeof(double));
    v->len = 3;
    v->arr[0] = x;
    v->arr[1] = y;
    v->arr[2] = z;
    return v;
}

vector* vector4(double x, double y, double z, double w) {
    vector *v = malloc(sizeof(short) + 4*sizeof(double));
    v->len = 4;
    v->arr[0] = x;
    v->arr[1] = y;
    v->arr[2] = z;
    v->arr[3] = w;
    return v;
}

vector* vadd(vector* v1, vector* v2) {
    if (v1->len != v2->len) {
        printf("Cannot add: Incompatible vector lengths %d != %d\n", v1->len, v2->len);
        return NULL;
    }
    vector *v = malloc(sizeof(short) + 4*sizeof(double));
    for (int i = 0; i<v1->len; i++) {
        v->arr[i] = v1->arr[i] + v2->arr[i];
    }
    return v;
}