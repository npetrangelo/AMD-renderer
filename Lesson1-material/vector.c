#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "vector.h"

static vector* alloc_vector(int n) {
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

vector* make_vector(int count, ...) {
    if (count < 2 || count > 4) return NULL;

    vector *v = alloc_vector(count);

    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        v->arr[i] = va_arg(ap, double);
    }
    va_end(ap);
    return v;
}

vector* vector2(double x, double y) { return make_vector(2, x, y); }
vector* vector3(double x, double y, double z) { return make_vector(3, x, y, z); }
vector* vector4(double x, double y, double z, double w) { return make_vector(4, x, y, z, w); }

int vadd(vector* v1, vector* v2, vector* result) {
    if (v1->len != v2->len || result->len != v1->len) {
        printf("Cannot add: Incompatible vector lengths %d ≠ %d ≠ %d\n", v1->len, v2->len, result->len);
        return 0;
    }
    for (int i = 0; i < result->len; i++) {
        result->arr[i] = v1->arr[i] + v2->arr[i];
    }
    return 1;
}

int vscale(vector* v, double s, vector* result) {
    if (v->len != result->len) {
        return 0;
    }
    for (int i = 0; i < v1->len; i++) {
        result->arr[i] = v->arr[i] * scalar;
    }
    return 1;
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

int vmag(vector* v, double* result) {
    double dot = 0;
    if (!vdot(v, v, &dot)) {
        return 0;
    }
    *result = sqrt(dot);
    return 1;
}