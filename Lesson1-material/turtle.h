#include <math.h>
#pragma once

#define PI 3.14159

typedef struct {
    float cur_x;
    float cur_y;
    float cur_heading;
} turtle;

turtle* make_turtle( void );

void forward(turtle* t, float length);
void back(turtle* t, float length);
void left(turtle* t, float angle);
void right(turtle* t, float angle);

void square(turtle* t, float size);
void ngon(turtle* t, int numSides, float size);
void circle(turtle* t);
void spiral(turtle* t);
void star(turtle* t, float size);
void V(turtle* t, float size, float angle);

void square_fractal(turtle* t, float size);
void V_fractal(turtle* t, float size, float angle);
void koch_fractal(turtle* t, float length);