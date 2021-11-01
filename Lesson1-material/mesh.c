#include <stdlib.h>
#include <stdio.h>
#include "point.h"
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
    m->triangles = malloc(3 * sizeof(int) * len_tris); //(int (*)[len_tris][3]) 
    return m;
}

int add_point(Mesh *m, Point *p) {
    if (m->num_points == m->len_points) {
        printf("Cannot add more points to mesh\n");
        return 0;
    }
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
    printf("Added triangle with vertices %d %d %d\n", tris[m->num_tris][0], tris[m->num_tris][1], tris[m->num_tris][2]);
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
    Mesh *m = make_mesh(8, 12);

    for (int i = 0; i < 8; i++) {
        float world[4] = {(i>>0) & 0b1, (i>>1) & 0b1, (i>>2) & 0b1, 0.0};
        add_point(m, make_vertex(world, color));
    }

    // Front
    add_triangle(m, 0, 1, 2);
    add_triangle(m, 1, 2, 3);
    // Left
    add_triangle(m, 0, 2, 4);
    add_triangle(m, 2, 4, 6);
    // Right
    add_triangle(m, 1, 3, 5);
    add_triangle(m, 3, 5, 7);
    // Bottom
    add_triangle(m, 0, 1, 4);
    add_triangle(m, 1, 4, 5);
    // Top
    add_triangle(m, 2, 3, 6);
    add_triangle(m, 3, 6, 7);
    // Back
    add_triangle(m, 4, 5, 6);
    add_triangle(m, 5, 6, 7);

    return m;
}