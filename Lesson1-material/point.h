#pragma once

typedef struct {
    float screen[4];
    float color[4];
    float world[4];
} Point;

// Create and destroy points.
Point* make_point(float screen[4], float color[4]);
Point* make_vertex(float world[4], float color[4]);