#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "quaternion.h"
#include "point.h"
#include "buffer.h"
#include "utility.h"
#include "camera.h"

Camera* make_camera(float zoom, float pos[4]) {
    Camera *cam = malloc(sizeof(Camera));
    cam->zoom = zoom;
    vcopy(pos, cam->pos);
    vset(cam->q, 1.0, 0.0, 0.0, 0.0);
    return cam;
}

void look_at(Camera *cam, float target[4]) { // Still weird
    float dir[4];
    vsub(target, cam->pos, dir);
    console_log(Debug, "Looking (%f, %f, %f)\n", dir[0], dir[1], dir[2]);
    norm(dir, dir);
    // Reset to no rotation
    vset(cam->q, 1.0, 0.0, 0.0, 0.0);
    // Normalize yaw vector without y component
    float yawVec[4] = {dir[0], 0.0, dir[2], 0.0};
    norm(yawVec, yawVec);
    float cosp = sqrt(dir[0]*dir[0] + dir[2]*dir[2]);
    // Half angle formulas because quaternions work with half angles
    float pitch[4] = {half_angle_cos(cosp), half_angle_sin(cosp, dir[1]), 0.0, 0.0};
    float yaw[4] = {-half_angle_cos(-yawVec[2]), 0.0, half_angle_sin(-yawVec[2], yawVec[0]), 0.0};
    qmult(pitch, cam->q, cam->q);
    qmult(yaw, cam->q, cam->q);
    console_log(Debug, "Look at: cam->q=[%f, %f, %f, %f]\n", cam->q[0], cam->q[1], cam->q[2], cam->q[3]);
}

void transform(Camera *cam, Mesh *m) {
    float temp[4];
    float conjq[4];
    console_log(Debug, "Transform: Conjugate\n");
    qconjugate(cam->q, conjq);
    console_log(Debug, "Transform: Loop\n");
    for (int i = 0; i < m->num_points; i++) {
        console_log(Debug, "Transform: In loop i=%d\n", i);
        temp[0] = m->points[i].world[0] - cam->pos[0];
        temp[1] = m->points[i].world[1] - cam->pos[1];
        temp[2] = m->points[i].world[2] - cam->pos[2];
        temp[3] = 0.0;

        vrotate(temp, conjq, m->points[i].cam);
    } 
}

void project(Camera *cam, Mesh *m) {
    console_log(Debug, "Num points projected %d\n", m->num_points);
    for (int i = 0; i < m->num_points; i++) {
        console_log(Debug, "Cam z %f\n", m->points[i].cam[2]);
        m->points[i].screen[0] = cam->zoom * m->points[i].cam[0] / -m->points[i].cam[2];
        m->points[i].screen[1] = cam->zoom * m->points[i].cam[1] / -m->points[i].cam[2];
        m->points[i].screen[2] = m->points[i].cam[2];
        m->points[i].screen[3] = 0.0;
    }
}

void ortho(Camera *cam, Mesh *m) {
    for (int i = 0; i < m->num_points; i++) {
        m->points[i].screen[0] = cam->zoom * m->points[i].cam[0];
        m->points[i].screen[1] = cam->zoom * m->points[i].cam[1];
        m->points[i].screen[2] = m->points[i].cam[2];
        m->points[i].screen[3] = 0.0;
    }
}

void wireframe(Camera *cam, Mesh *m) {
    int (*tris)[3] = (int (*)[3])(m->triangles);
    Point *pts[3];
    for (int i = 0; i < m->num_tris; i++) {
        console_log(Debug, "Get points for triangle %d\n", i);
        pts[0] = &(m->points[tris[i][0]]);
        pts[1] = &(m->points[tris[i][1]]);
        pts[2] = &(m->points[tris[i][2]]);
        console_log(Debug, "Draw triangle %d\n", i);
        draw_n_lines(pts, 3, 1);
    }
}

void render(Camera *cam, Mesh *m) {
    console_log(Info, "Transform\n");
    transform(cam, m);
    console_log(Info, "Project\n");
    project(cam, m);
    console_log(Info, "Wireframe\n");
    wireframe(cam, m);
}