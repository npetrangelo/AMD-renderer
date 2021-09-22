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

    vector *v = malloc(sizeof(vector));
    v->len = count;
    v->arr = malloc(sizeof(double) * count);

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

vector* vadd(vector* v1, vector* v2) {
    if (v1->len != v2->len) {
        printf("Cannot add: Incompatible vector lengths %d != %d\n", v1->len, v2->len);
        return NULL;
    }
    vector *v = alloc_vector(v1->len);
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