#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "nvector.h"

int main ( void ) {
    vector* v1 = vector3(1.0, 0.0, 0.0);
    vector* v2 = vector3(0.0, 1.0, 0.0);
    vector* v = vadd(v1, v2);
    if (!v) {
        printf("Addition error\n");
    } else {
        printf("len=%d, {%f, %f, %f}\n", v->len, v->arr[0], v->arr[1], v->arr[2]);
    }

    nvector* nv = bivector(v1, v2);
    if (!nv) {
        printf("Bivector error\n");
    } else {
        printf("Bivector len=%d\n", nv->len);
        printf("{%f, %f, %f}, {%f, %f, %f}\n",
            nv->arr[0]->arr[0], nv->arr[0]->arr[1], nv->arr[0]->arr[2],
            nv->arr[1]->arr[0], nv->arr[1]->arr[1], nv->arr[1]->arr[2]);
    }
}