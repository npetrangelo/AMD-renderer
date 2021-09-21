#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main ( void ) {
    vector* v1 = vector3(1.0, 0.0, 0.0);
    vector* v2 = vector3(0.0, 1.0, 0.0);
    vector* v = vadd(v1, v2);
    if (!v) {
        printf("Addition error\n");
    } else {
        printf("len=%d, {%f, %f, %f}\n", v->len, v->arr[0], v->arr[1], v->arr[2]);
    }
}