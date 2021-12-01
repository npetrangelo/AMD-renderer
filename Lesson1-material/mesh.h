#include "point.h"
#pragma once

typedef struct {
    float min[4];
    float max[4];
    int len_points;
    int num_points;
    int len_tris;
    int num_tris;
    Point *points;
    int *triangles;
} Mesh;

void free_mesh(Mesh *m);
Mesh* make_mesh(int num_points, int num_tris);
int add_point(Mesh *m, Point *p);
int add_triangle(Mesh *m, int p0, int p1, int p2);
int add_quad(Mesh *m, int p0, int p1, int p2, int p3);

// Geometric Primitives

Mesh* make_plane(float color[4]);
Mesh* make_cube(float color[4]);

Mesh* make_torus(float color[4], float R, float r, int toroidal, int poloidal);
