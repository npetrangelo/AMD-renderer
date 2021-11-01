#include "mesh.h"
#pragma once

typedef struct {
    float zoom;
    float pos[4];
    float orientation[4];
    
} Camera;

Camera* make_camera(float zoom, float pos[4]);

void transform(Camera *cam, Mesh *m);
void project(Camera *cam, Mesh *m);
void ortho(Camera *cam, Mesh *m);
void wireframe(Camera *cam, Mesh *m);