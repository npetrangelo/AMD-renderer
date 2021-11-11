#include <stdlib.h>
#include <stdio.h>
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

void transform(Camera *cam, Mesh *m) {
    float temp[4];
    float conjq[4];
    qconjugate(cam->q, conjq);
    for (int i = 0; i < m->num_points; i++) {
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