#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "nvector.h"

nvector* univector(vector* v) {
    nvector *nv = malloc(sizeof(short) + sizeof(v));
    nv->len = 1;
    nv->arr[0] = v;
    return nv;
}

nvector* bivector(vector* v1, vector* v2) {
    if (v1->len != v2->len) {
        printf("Cannot make bivector: Incompatible vector lengths %d and %d\n", v1->len, v2->len);
        return NULL;
    }
    nvector *nv = malloc(sizeof(short) + 2*sizeof(v1));
    nv->len = 2;
    nv->arr[0] = v1;
    nv->arr[1] = v2;
    return nv;
}

nvector* trivector(vector* v1, vector* v2, vector* v3) {
    if (v1->len != v2->len || v1->len != v3->len) {
        printf("Cannot make trivector: Incompatible vector lengths %d, %d, and %d\n", v1->len, v2->len, v3->len);
        return NULL;
    }
    nvector *nv = malloc(sizeof(short) + 3*sizeof(v1));
    nv->len = 3;
    nv->arr[0] = v1;
    nv->arr[1] = v2;
    nv->arr[2] = v3;
    return nv;
}

nvector* nvadd(nvector* nv1, nvector* nv2) {
    if (nv1->len != nv2->len) {
        printf("Cannot add: Incompatible nvector lengths %d != %d\n", nv1->len, nv2->len);
        return NULL;
    }
    nvector *nv = malloc(sizeof(nv1));
    nv->len = nv1->len;
    for (int i = 0; i<nv1->len; i++) {
        nv->arr[i] = vadd(nv1->arr[i], nv2->arr[i]); //v1->arr[i] + v2->arr[i];
    }
    return nv;
}