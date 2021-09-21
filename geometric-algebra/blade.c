#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "blade.h"

blade* univector(vector* v) {
    blade *b = malloc(sizeof(short) + sizeof(v));
    b->len = 1;
    b->arr[0] = v;
    return b;
}

blade* bivector(vector* v1, vector* v2) {
    if (v1->len != v2->len) {
        printf("Cannot make bivector: Incompatible vector lengths %d and %d\n", v1->len, v2->len);
        return NULL;
    }
    blade *b = malloc(sizeof(short) + 2*sizeof(v1));
    b->len = 2;
    b->arr[0] = v1;
    b->arr[1] = v2;
    return b;
}

blade* trivector(vector* v1, vector* v2, vector* v3) {
    if (v1->len != v2->len || v1->len != v3->len) {
        printf("Cannot make trivector: Incompatible vector lengths %d, %d, and %d\n", v1->len, v2->len, v3->len);
        return NULL;
    }
    blade *b = malloc(sizeof(short) + 3*sizeof(v1));
    b->len = 3;
    b->arr[0] = v1;
    b->arr[1] = v2;
    b->arr[2] = v3;
    return b;
}

blade* badd(blade* nv1, blade* nv2) {
    if (nv1->len != nv2->len) {
        printf("Cannot add: Incompatible nvector lengths %d != %d\n", nv1->len, nv2->len);
        return NULL;
    }
    blade *b = malloc(sizeof(nv1));
    b->len = nv1->len;
    for (int i = 0; i<nv1->len; i++) {
        b->arr[i] = vadd(nv1->arr[i], nv2->arr[i]); //v1->arr[i] + v2->arr[i];
    }
    return b;
}