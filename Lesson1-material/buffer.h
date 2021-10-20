#include "point.h"
#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

extern float buffer[SCREEN_WIDTH][SCREEN_HEIGHT][4];

void draw_pixel( float x, float y, float color[4] );
void draw_point( Point* p );
void draw_line( Point* p0, Point* p1 );

void render_to_screen( void );