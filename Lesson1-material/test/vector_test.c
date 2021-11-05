#include <stdlib.h>
#include <stdio.h>
#include "../vector.h"
#include "../quaternion.h"

#define PI 3.141592653589

int print_logs = 0;

void testRotate() {
    float unit[4] = {1.0, 0.0, 0.0, 0.0};
    float axis[4] = {0.0, 0.0, 1.0, 0.0};
    float q[4];
    qrotate(unit, axis, PI/2.0, q);

    float v[4] = {1.0, 0.0, 0.0, 0.0};
    float result[4] = {0.0};
    if (!vrotate(v, q, result)) {
        printf("Rotate failed\n");
    };
    printf("[%f %f %f]\n", result[0], result[1], result[2]);
}

int main(int argc, char **argv) {
    testRotate();
}