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
void circle(turtle* t);
void spiral(turtle* t);
void star(turtle* t);