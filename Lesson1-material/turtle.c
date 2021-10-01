#include <math.h>
#include <stdlib.h>
#include "line.h"
#include "turtle.h"

turtle* make_turtle( void ) {
    turtle* t = malloc(sizeof(turtle));
    t->cur_x = 0.0;
    t->cur_y = 0.0;
    t->cur_heading = 0.0;
    return t;
}

void forward(turtle* t, float length) {
    float newX = t->cur_x + length * cos(t->cur_heading);
    float newY = t->cur_y + length * sin(t->cur_heading);

    draw_line(t->cur_x, t->cur_y, newX, newY);

    t->cur_x = newX;
    t->cur_y = newY;
}

void back(turtle* t, float length) {
    forward(t, -length);
}

void left(turtle* t, float angle) {
    t->cur_heading = t->cur_heading + angle;
}

void right(turtle* t, float angle) {
    left(t, -angle);
}

void square(turtle* t, float size) {
    for (int i = 0; i < 4; i++) {
        forward(t, size);
        left(t, PI/2.0);
    }
}