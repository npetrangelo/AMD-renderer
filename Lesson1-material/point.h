#pragma once

typedef struct {
    float screen[4];
    float color[4];
    float pos[4];
} Point;

// Create and destroy points.
Point* make_point(float screen[4], float color[4]);