#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "blade.h"

int main ( void ) {
    vector* v1 = vector3(1.0, 0.0, 0.0);
    vector* v2 = vector3(0.0, 1.0, 0.0);
    vector* v = vadd(v1, v2);
    if (!v) {
        printf("Addition error\n");
        return 1;
    }
    printf("sum len=%d, {%f, %f, %f}\n", v->len, v->arr[0], v->arr[1], v->arr[2]);

    blade* b = bivector(v1, v2);
    if (!b) {
        printf("Bivector error\n");
        return 1;
    }
    printf("Bivector len=%d\n", b->len);
    printf("{%f, %f, %f}, {%f, %f, %f}\n",
        b->arr[0]->arr[0], b->arr[0]->arr[1], b->arr[0]->arr[2],
        b->arr[1]->arr[0], b->arr[1]->arr[1], b->arr[1]->arr[2]);

    double dot = 0;
    if (!vdot(v1,v1, &dot)) {
        printf("Dot product error\n");
        return 1;
    }

    printf("Dot product %f\n", dot);
}