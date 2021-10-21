#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "vector.h"
#include "buffer.h"

float buffer[SCREEN_WIDTH][SCREEN_HEIGHT][4] = {0};

void draw_pixel( float x, float y, float color[4] ) {
    int i = (int)(x + 0.5) + SCREEN_WIDTH/2;
    int j = (int)(y + 0.5) + SCREEN_HEIGHT/2;
    vcopy(color, buffer[i][j]);
}

void draw_point( Point* p ) {
    draw_pixel(p->screen[0], p->screen[1], p->color);
}

void draw_line( Point* p0, Point* p1 ) {
    if (p0->screen[0]==p1->screen[0] && p0->screen[1]==p1->screen[1]) {
        float color[4] = {0.0};
        vlerp(p0->color, p1->color, 0.5, color);
        draw_pixel(p0->screen[0], p0->screen[1], color);
        return;
    }
    
    float increment = 1.0/fmax(fabs(p1->screen[0] - p0->screen[0]), fabs(p1->screen[1] - p0->screen[1]));
    for (float i = 0.0; i <= 1.0; i += increment) {
        float screen[4] = {0.0};
        vlerp(p0->screen, p1->screen, i, screen);
        float color[4] = {0.0};
        vlerp(p0->color, p1->color, i, color);
        draw_pixel(screen[0], screen[1], color);
    }
}

void draw_n_lines( Point* points[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Line %d\n", i);
        draw_line(points[i], points[i+1]);
    }
}

void draw_border(float color[4]) {
    float screen0[4] = {-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, 0.0, 0.0};
    float screen1[4] = {-SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0, 0.0};
    float screen2[4] = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0, 0.0};
    float screen3[4] = {SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, 0.0, 0.0};

    Point *p0 = make_point(screen0, color);
    Point* points[5] = {p0, make_point(screen1, color), make_point(screen2, color), make_point(screen3, color), p0};
    draw_n_lines(points, 4);
}

void render_to_screen( void ) {
    glRasterPos2i(-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2);
    glDrawPixels(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_FLOAT, buffer);
}