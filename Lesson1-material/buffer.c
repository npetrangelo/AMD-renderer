#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "point.h"
#include "vector.h"
#include "utility.h"
#include "buffer.h"

float buffer[SCREEN_WIDTH+1][SCREEN_HEIGHT+1][4] = {0.0};
float zbuffer[SCREEN_WIDTH+1][SCREEN_HEIGHT+1] = {0.0};

void init_zbuffer() {
    for (int j = 0; j <= SCREEN_WIDTH; j++) {
        for (int i = 0; i <= SCREEN_HEIGHT; i++) {
            zbuffer[j][i] = 1.0;
        }
    }
}

void draw_pixel( float x, float y, float color[4] ) {
    int i = (int)(x) + SCREEN_WIDTH/2;
    int j = (int)(y) + SCREEN_HEIGHT/2;
    if (i < 0 || i > SCREEN_WIDTH || j < 0 || j > SCREEN_HEIGHT) {
        return;
    }
    vcopy(color, buffer[j][i]);
}

void draw_z( float x, float y, float depth ) {
    int i = (int)(x) + SCREEN_WIDTH/2;
    int j = (int)(y) + SCREEN_HEIGHT/2;
    zbuffer[j][i] = fminf(zbuffer[j][i], depth);
}

void draw_point( Point* p ) {
    draw_pixel(p->screen[0], p->screen[1], p->color);
}

void draw_line( Point* p0, Point* p1 ) {
    if (p0->screen[0]==p1->screen[0] && p0->screen[1]==p1->screen[1]) {
        console_log(Debug, "Single point line\n");
        float color[4] = {0.0};
        vlerp(p0->color, p1->color, 0.5, color);
        draw_pixel(p0->screen[0], p0->screen[1], color);
        return;
    }
    console_log(Debug, "Line from (%f, %f) to (%f, %f)\n", p0->screen[0], p0->screen[1], p1->screen[0], p1->screen[1]);
    float screen[4] = {0.0, 0.0, 0.0, 0.0};
    float color[4] = {0.0, 0.0, 0.0, 0.0};
    float increment = 1.0/fmax(fabs(p1->screen[0] - p0->screen[0]), fabs(p1->screen[1] - p0->screen[1]));
    for (float i = 0.0; i <= 1.0; i += increment) {
        vlerp(p0->screen, p1->screen, i, screen);
        vlerp(p0->color, p1->color, i, color);
        draw_pixel(screen[0], screen[1], color);
    }
}

void draw_n_lines(Point* points[], int n, int closed) {
    console_log(Debug, "Draw %d lines\n", n);
    for (int i = 0; i < n-1; i++) {
        draw_line(points[i], points[i+1]);
    }
    if (closed) {
        console_log(Debug, "Closing line\n");
        draw_line(points[n-1], points[0]);
    }
}

void draw_border(float color[4]) {
    float screen0[4] = {-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, 0.0, 0.0};
    float screen1[4] = {-SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0, 0.0};
    float screen2[4] = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0, 0.0};
    float screen3[4] = {SCREEN_WIDTH/2, -SCREEN_HEIGHT/2, 0.0, 0.0};

    Point* points[4] = {make_point(screen0, color),
                        make_point(screen1, color),
                        make_point(screen2, color),
                        make_point(screen3, color)};
    draw_n_lines(points, 4, 1);
}

void fill_triangle(Point* p0, Point* p1, Point* p2) {
    int minX = (int) fmaxf(-400.0, fminf(p0->screen[0], fminf(p1->screen[0], p2->screen[0])));
    int maxX = (int) fminf(400.0, (fmaxf(p0->screen[0], fmaxf(p1->screen[0], p2->screen[0]))) + 1);
    int minY = (int) fmaxf(-400.0, fminf(p0->screen[1], fminf(p1->screen[1], p2->screen[1])));
    int maxY = (int) fminf(400.0, (fmaxf(p0->screen[1], fmaxf(p1->screen[1], p2->screen[1]))) + 1);

    float e10[4], e12[4], normal[4];
    vsub(p0->screen, p1->screen, e10);
    vsub(p2->screen, p1->screen, e12);
    vcross(e12, e10, normal);
    norm(normal, normal);

    float d0[4], d1[4], d2[4], color[4];
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            // Barycentric coordinates
            float px[4] = {x, y, -1.0, 0.0};
            vsub(p0->screen, px, d0);
            vsub(p1->screen, px, d1);
            vsub(p2->screen, px, d2);

            float bary_coord[4] = {area(d0, d1, normal), area(d1, d2, normal), area(d2, d0, normal), 0.0};
            norm(bary_coord, bary_coord);

            if (bary_coord[0] < 0.0 || bary_coord[1] < 0.0 || bary_coord[2] < 0.0) {
                console_log(Debug, "bary=[%f %f %f]\n", bary_coord[0], bary_coord[1], bary_coord[2]);
                continue;
            }

            bary(p0->color, p1->color, p2->color, bary_coord, color);
            draw_pixel(x, y, color);
        }
    }
}

void render_to_screen( void ) {
    glDrawPixels(SCREEN_WIDTH+1, SCREEN_HEIGHT+1, GL_RGBA, GL_FLOAT, buffer);
}

void render_zbuffer( void ) {
    console_log(Info, "Zbuffer first pixel %f\n", zbuffer[0][0]);
    console_log(Info, "Zbuffer middle pixel %f\n", zbuffer[0][1]);

    glDrawPixels(SCREEN_WIDTH+1, SCREEN_HEIGHT+1, GL_LUMINANCE, GL_FLOAT, zbuffer);
}