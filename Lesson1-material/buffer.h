#include "point.h"
#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

extern float buffer[SCREEN_WIDTH][SCREEN_HEIGHT][4];

void draw_pixel( float x, float y, float color[4] );
void draw_point( Point* p );
void draw_line( Point* p0, Point* p1 );
void draw_n_lines( Point* points[], int n);
void draw_border(float color[4]);

void render_to_screen( void );