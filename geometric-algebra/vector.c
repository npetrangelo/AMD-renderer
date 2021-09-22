#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

static vector* make_vector(int n) {
    vector *v = malloc(sizeof(vector));
    v->len = n;
    v->arr = malloc(sizeof(double) * n);
    return v;
}

void free_vector(vector *v) {
    if (!v) return;
    free(v->arr);
    free(v);
}

vector* vector2(double x, double y) {
    vector *v = make_vector(2);
    v->arr[0] = x;
    v->arr[1] = y;
    return v;
}

vector* vector3(double x, double y, double z) {
    vector *v = make_vector(3);
    v->arr[0] = x;
    v->arr[1] = y;
    v->arr[2] = z;
    return v;
}

vector* vector4(double x, double y, double z, double w) {
    vector *v = make_vector(4);
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
    vector *v = make_vector(v1->len);
    for (int i = 0; i<v1->len; i++) {
        v->arr[i] = v1->arr[i] + v2->arr[i];
    }
    return v;
}

int vdot(vector* v1, vector* v2, double* result) {
    if (v1->len != v2->len) {
        printf("Cannot compute dot product: Incompatible vector lengths %d != %d\n", v1->len, v2->len);
        return 0;
    }
    
    *result = 0;
    for (int i = 0; i<v1->len; i++) {
        *result += v1->arr[i]*v2->arr[i];
    }
    return 1;
}