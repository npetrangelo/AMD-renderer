#include "point.h"
#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

extern float buffer[SCREEN_WIDTH+1][SCREEN_HEIGHT+1][4];
extern float zbuffer[SCREEN_WIDTH+1][SCREEN_HEIGHT+1];

void init_zbuffer();
void draw_pixel( float x, float y, float color[4] );
void draw_z( float x, float y, float depth );
void draw_point( Point* p );
void draw_line( Point* p0, Point* p1 );
void draw_n_lines(Point* points[], int n, int closed);
void draw_border(float color[4]);

void fill_triangle(Point* p0, Point* p1, Point* p2);

void render_to_screen( void );
void render_zbuffer( void );