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
        right(t, PI/2.0);
    }
}

void ngon(turtle* t, int numSides, float size) {
    for (int i = 0; i < numSides; i++) {
        forward(t, size);
        right(t, 2.0*PI/((float) numSides));
    }
}

void circle(turtle* t) {
    ngon(t, 30, 30);
}

void spiral(turtle* t) {
    float increment = 0.2;
    for (float i = 0; i <= 2*PI; i+=increment) {
        forward(t, i*10);
        right(t, increment);
    }
}

void star(turtle* t, float size) {
    for (int i = 0; i < 5; i++) {
        forward(t, size);
        right(t, 4.0*PI/5.0);
    }
}

void V(turtle* t, float size, float angle) {
    left(t, angle/2.0);
    forward(t, size);
    back(t, size);
    right(t, angle);
    forward(t, size);
    back(t, size);
    left(t, angle/2.0);
}

void square_fractal(turtle* t, float size) {
    for (int i = 0; i < 4; i++) {
        forward(t, size);
        if (size > 10.0) {
            square_fractal(t, size/2.0);
        }
        right(t, PI/2.0);
    }
}

void V_fractal(turtle* t, float size, float angle) {
    left(t, angle/2.0);
    forward(t, size);
    if (size > 10.0) {
        V_fractal(t, size/2.0, angle);
    }
    back(t, size);
    right(t, angle);
    forward(t, size);
    if (size > 10.0) {
        V_fractal(t, size/2.0, angle);
    }
    back(t, size);
    left(t, angle/2.0);
}

void koch_fractal(turtle* t, float length) {
    if (length <= 5.0) {
        forward(t, length);
        return;
    }
    koch_fractal(t, length/3.0);
    left(t, PI/3.0);
    koch_fractal(t, length/3.0);
    right(t, 2.0*PI/3.0);
    koch_fractal(t, length/3.0);
    left(t, PI/3.0);
    koch_fractal(t, length/3.0);
}