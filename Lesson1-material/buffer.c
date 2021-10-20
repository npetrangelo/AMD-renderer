#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "point.h"
#include "vector.h"
#include "buffer.h"

float buffer[SCREEN_WIDTH][SCREEN_HEIGHT][4] = {0};

void draw_pixel( float x, float y, float color[4] ) {
    int i = (int)(x + 0.5);
    int j = (int)(y + 0.5);
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

void render_to_screen( void ) {
    glRasterPos2i(-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2);
    glDrawPixels(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_FLOAT, buffer);
}