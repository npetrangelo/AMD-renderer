/*
 *
 * point.c - simple GLUT app that draws one frame with a single point at origin
 *
 * To build:  gcc -framework OpenGL -framework GLUT point.c -o point
 *
 */
#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

/*************************************************************************/
/* header files                                                          */
/*************************************************************************/
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include "line.h"
#include "turtle.h"
#include "bresenham.h"
#include "xiaolin.h"

/*************************************************************************/
/* defines                                                               */
/*************************************************************************/
#define repeat(x)       for( global_index = 0; global_index < (int)(x); global_index++ )
#define PI 3.14159

/*************************************************************************/
/* global variables                                                      */
/*************************************************************************/
int window_size = 400;
int Mojave_WorkAround = 0;
int draw_one_frame = 1;
int global_index;

/*************************************************************************/
/* utility functions                                                     */
/*************************************************************************/

/*
 * lerp()
 */
float lerp(float a, float b, float t)
{
    return a*(1.0-t) + b*t;
}

/*
 * random_float()
 */
float random_float( float low, float high )
{
    return( (float)(low + (rand()/(float)RAND_MAX)*(high - low)) );
}

/*
 * random_int()
 */
float random_int( int low, int high )
{
    return( (int)(low + (rand()/(float)RAND_MAX)*(high+1 - low)) );
}

/*
 * randomGL()
 */
float randomGL( int m )
{
    return rand()%m;
}

double sign( double a )
{
    if ( a < 0.0 ) {
        return( -1.0 );
    }
    if( a > 0.0 ) {
        return( 1.0 );
    }
    return( 0.0 );
}

double dabs( double a )
{
    if( a < 0.0 ) {
        return( -a );
    }
    return( a );
}

/*
 * set_color()
 */
void set_color( float r, float g, float b, float a )
{
    glColor4f( r, g, b, a );
}

/*
 * draw_point()
 */
void draw_point( float x, float y )
{
    /*
     * draw points
     */
    glBegin(GL_POINTS);
        glVertex2f( 0.5+x, 0.5+y );
    glEnd();

}

void draw_line(float x0, float y0, float x1, float y1) {
    if (x0==x1 && y0==y1) {
        draw_point(x0, y0);
        return;
    }
    
    float increment = 1.0/fmax(fabs(x1 - x0), fabs(y1 - y0));
    for (float i = 0.0; i <= 1.0; i += increment) {
        draw_point(lerp(x0, x1, i), lerp(y0, y1, i));
    }
}

void random_lines( void ) {
    for (int i = 0; i < 20; i++) {
        set_color(random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0), 0.0);
        draw_line(random_int(-400, 400), random_int(-400, 400), random_int(-400, 400), random_int(-400, 400));
    }
}

void draw_fan( void ) {
    float radius = 100;
    for (int i = 0; i < 180; i+=15) {
        float radians = i * PI/180.0;
        draw_line(-radius * cos(radians), -radius * sin(radians), radius * cos(radians), radius * sin(radians));
    }
}

void draw_grid( void ) {
    for (int i = -300; i <= 300; i += 50) {
        draw_line(-300, i, 300, i);
        draw_line(i, -300, i, 300);
    }
}

void draw_turtle( void ) {
    turtle* t = make_turtle();
    koch_fractal(t, 200.0);
}

/*
 * my_drawing
 *
 *    set_color( r, g, b, a );
 *    draw_point( x, y );
 */
void my_drawing( void )
{
    for (int i = 0; i < 1000; i++) {
        set_color(random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0), 0.0);
        draw_point(random_float(-400.0, 400.0), random_float(-400.0, 400.0));
    }
}

/*************************************************************************/
/* GLUT functions                                                        */
/*************************************************************************/
/*
 * display routine
 */
void display(void)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    if( Mojave_WorkAround )
    {
        glutReshapeWindow(2 * window_size,2 * window_size);//Necessary for Mojave. Has to be different dimensions than in glutInitWindowSize();
        Mojave_WorkAround = 0;
    }

    if( draw_one_frame == 0 )
        return;
	
    /*
     * clear color buffer
     */
    glClear(GL_COLOR_BUFFER_BIT );

    bresenham(-200.0, 0.0, 200.0, 10.0);
    xiaolin(-200.0, 0.0, 200.0, 10.0);


    // draw_turtle();
    
    /*
     * show results
     */
    glutSwapBuffers();
    glutPostRedisplay();//Necessary for Mojave.

    draw_one_frame = 0;
}

/*
 * Key routine
 */
static void Key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':       draw_one_frame = 1;     glutPostRedisplay();    break;
        case 'q':       exit(0);                                        break;
        case '\033':    exit(0);                                        break;
    }
}

/*
 * main function
 */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    srand(time(NULL));

    /*
     * create window
     */
    glutInitWindowSize(window_size,window_size);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("My OpenGL Window");

    /*
     * setup display(), Key() funtions
     */
    glutDisplayFunc(display);
    glutKeyboardFunc(Key);

    /*
     * setup OpenGL state
     */
    glClearColor(0.0,0.0,0.0,1.0);
    gluOrtho2D(-window_size,window_size,-window_size,window_size);
    glPointSize(2.0);
    glColor4f(1.0,0.0,0.0,1.0);

    /*
     * start loop that calls display() and Key() routines
     */
    glutMainLoop();

    return 0;
}
