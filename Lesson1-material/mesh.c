#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "point.h"
#include "utility.h"
#include "mesh.h"

void free_mesh(Mesh *m) {
    if (!m) return;
    free(m->triangles);
    free(m->points);
    free(m);
}

Mesh* make_mesh(int len_points, int len_tris) {
    Mesh *m = malloc(sizeof(Mesh));
    m->num_points = 0;
    m->num_tris = 0;
    m->len_points = len_points;
    m->len_tris = len_tris;
    m->points = malloc(sizeof(Point) * len_points);
    m->triangles = malloc(3 * sizeof(int) * len_tris);
    // printf("Setting points null\n");
    // for (int i = 0; i < m->len_points; i++) {
    //     m->points = NULL;
    // }
    for (int i = 0; i < (3*len_tris); i++) {
        m->triangles[i] = 0;
    }
    return m;
}

int add_point(Mesh *m, Point *p) {
    if (m->num_points == m->len_points) {
        printf("Cannot add more points to mesh\n");
        return 0;
    }
    // printf("Adding point x=%f y=%f z=%f\n", p->world[0], p->world[1], p->world[2]);
    m->points[m->num_points++] = *p;
    return 1;
}

int add_triangle(Mesh *m, int p0, int p1, int p2) {
    if (m->num_tris == m->len_tris) {
        printf("Cannot add more triangles to mesh\n");
        return 0;
    }
    int (*tris)[3] = (int (*)[3])(m->triangles);
    tris[m->num_tris][0] = p0;
    tris[m->num_tris][1] = p1;
    tris[m->num_tris++][2] = p2;
    // printf("Added triangle with vertices [%d %d %d]\n", tris[m->num_tris-1][0], tris[m->num_tris-1][1], tris[m->num_tris-1][2]);
    return 1;
}

int add_quad(Mesh *m, int p0, int p1, int p2, int p3) {
    add_triangle(m, p0, p1, p2);
    add_triangle(m, p1, p2, p3);
    return 1;
}

Mesh* make_plane(float color[4]) {
    Mesh *m = make_mesh(4, 2);

    for (float y = 0.0; y < 2.0; y++) {
        for (float x = 0.0; x < 2.0; x++) {
            float world[4] = {x, y, 0.0, 0.0};
            add_point(m, make_vertex(world, color));
        }
    }

    add_triangle(m, 0, 1, 2);
    add_triangle(m, 1, 2, 3);

    return m;
}

Mesh* make_cube(float color[4]) {
    console_log(Debug, "Making cube\n");
    Mesh *m = make_mesh(8, 12);

    console_log(Debug, "Adding points\n");
    for (int i = 0; i < 8; i++) {
        float world[4] = {((i>>0) & 0b1) ? 1.0 : -1.0, ((i>>1) & 0b1) ? 1.0 : -1.0, ((i>>2) & 0b1) ? 1.0 : -1.0, 0.0};
        add_point(m, make_vertex(world, color));
    }

    console_log(Debug, "Adding triangles\n");
    // Front
    add_quad(m, 0, 1, 2, 3);
    // Left
    add_quad(m, 0, 2, 4, 6);
    // Right
    add_quad(m, 1, 3, 5, 7);
    // Bottom
    add_quad(m, 0, 1, 4, 5);
    // Top
    add_quad(m, 2, 3, 6, 7);
    // Back
    add_quad(m, 4, 5, 6, 7);

    return m;
}

Mesh* make_torus(float color[4], float R, float r, int toroidal, int poloidal) {
    console_log(Debug, "Making torus\n");
    Mesh *m = make_mesh(toroidal*poloidal, 2*toroidal*poloidal);

    for (int t = 0; t < toroidal; t++) {
        for (int p = 0; p < poloidal; p++) {
            float theta = 2.0*PI*t/toroidal;
            float phi = 2.0*PI*p/poloidal;
            float world[4] = {(R + r*cos(theta))*cos(phi), r*sin(theta), (R + r*cos(theta))*sin(phi), 0.0};
            add_point(m, make_vertex(world, color));
            int p0 = p + poloidal*t;
            int p1 = (p + 1) % poloidal + poloidal*t;
            int p2 = p + poloidal*((t + 1) % toroidal);
            int p3 = (p + 1) % poloidal + poloidal*((t + 1) % toroidal);
            add_quad(m, p0, p1, p2, p3);
        }
    }

    return m;
}