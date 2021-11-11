#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../utility.h"
#include "../vector.h"
#include "../quaternion.h"
#include "../camera.h"
#include "../buffer.h"

#define PI 3.141592653589

Log_Level print_logs = 0;

void testRotate(float v[4], float angle) {
    float axis[4] = {0.0, 0.0, 1.0, 0.0};
    float q[4] = {1.0, 0.0, 0.0, 0.0};
    qrotate(q, axis, angle, q);

    float result[4] = {0.0};
    if (!vrotate(v, q, result)) {
        printf("Rotate failed\n");
    };
    printf("[%f %f %f]\n", result[0], result[1], result[2]);
}

void testLookAt() {
    float pos[4] = {0.0, 0.0, 3.0, 0.0};
    Camera *cam = make_camera(500.0, pos);
    float origin[4] = {0.0};
    look_at(cam, origin);
    printf("cam->q = [%f, %f, %f, %f]\n", cam->q[0], cam->q[1], cam->q[2], cam->q[3]);
}

void test_half_angle_cos() {
    printf("%f = %f?\n", 0.0, half_angle_cos(-1.0));
    printf("%f = %f?\n", sqrt(2.0)/2.0, half_angle_cos(0.0));

    printf("%f = %f?\n", -sqrt(2.0)/2.0, half_angle_sin(0.0, -1.0));
    printf("%f = %f?\n", 0.0, half_angle_sin(1.0, 0.0));
}

int main(int argc, char **argv) {
    float v[4] = {1.0, 0.0, 0.0, 0.0};
    testRotate(v, PI/4.0);
    test_half_angle_cos();
    testLookAt();
}