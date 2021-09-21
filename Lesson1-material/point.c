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

/*************************************************************************/
/* defines                                                               */
/*************************************************************************/
#define repeat(x)       for( global_index = 0; global_index < (int)(x); global_index++ )

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
        glVertex2f( x, y );
    glEnd();

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

void points_in_circle( void )
{
    float r = 200;

    for (int i = 0; i < 1000; i++) {
        set_color(random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0), 0.0);
        int x = random_float(-200.0, 200.0);
        int y = random_float(-200.0, 200.0);
        if (x*x + y*y < r*r)
            draw_point(x, y);
    }
}

void fill_window_solid( void )
{
    set_color(random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0), 0.0);
    for (int x = -400; x <= 400; x++) {
        for (int y = -400; y <= 400; y++) {
            draw_point(x, y);
        }
    }
}

void fill_window_static( void )
{
    for (int x = -400; x <= 400; x++) {
        for (int y = -400; y <= 400; y++) {
            set_color(random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0), 0.0);
            draw_point(x, y);
        }
    }
}

void horizontal_gradient( void )
{
    float r1 = random_float(0.0, 1.0), g1 = random_float(0.0, 1.0), b1 = random_float(0.0, 1.0);
    float r2 = random_float(0.0, 1.0), g2 = random_float(0.0, 1.0), b2 = random_float(0.0, 1.0);

    for (int x = -400; x <= 400; x++) {
        float t = (x+400)/800.0;
        set_color(lerp(r1, r2, t), lerp(g1, g2, t), lerp(b1, b2, t), 0.0);
        for (int y = -400; y <= 400; y++) {
            draw_point(x, y);
        }
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

    horizontal_gradient();
    
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
