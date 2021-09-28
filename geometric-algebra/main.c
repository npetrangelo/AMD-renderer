#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "blade.h"
#include "matrix.h"

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
    double mag = 0;
    if (!bmag(b, &mag)) {
        printf("Magnitude error\n");
        return 1;
    }
    printf("Bivector Magnitude: %f\n", mag);

    double dot = 0;
    if (!vdot(v1,v1, &dot)) {
        printf("Dot product error\n");
        return 1;
    }

    printf("Dot product %f\n", dot);

    matrix* m = to_matrix(trivector(vector3(7.0,0.0,4.0), vector3(3.0,9.0,2.0), vector3(1.0,5.0,0.0)));
    printf("Matrix\n");
    mprint(m);
    printf("Submatrix\n");
    mprint(msub(m, -1, 1));
    double det = 0;
    if (!mdet(m, &det)) {
        printf("Determinant error\n");
        return 1;
    }
    printf("Determinant %f\n", det);
}