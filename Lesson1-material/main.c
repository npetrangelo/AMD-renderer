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
#include "utility.h"
#include "point.h"
#include "buffer.h"
#include "mesh.h"
#include "camera.h"

/*************************************************************************/
/* defines                                                               */
/*************************************************************************/
#define repeat(x)       for( global_index = 0; global_index < (int)(x); global_index++ )
#define PI 3.14159

/*************************************************************************/
/* global variables                                                      */
/*************************************************************************/
int window_size = 800;
int Mojave_WorkAround = 0;
int draw_one_frame = 1;
int global_index;

/*
 * set_color()
 */
void set_color( float r, float g, float b, float a )
{
    glColor4f( r, g, b, a );
}

void random_lines( void ) {
    for (int i = 0; i < 20; i++) {
        float color[4] = {random_float(0.0, 1.0), random_float(0.0, 1.0), random_float(0.0, 1.0), 0.0};
        float screen0[4] = {random_float(-400.0, 400.0), random_float(-400.0, 400.0), 0.0, 0.0};
        float screen1[4] = {random_float(-400.0, 400.0), random_float(-400.0, 400.0), 0.0, 0.0};
        Point *p0 = make_point(screen0, color);
        Point *p1 = make_point(screen1, color);
        draw_line(p0, p1);
    }
}

void draw_fan( float color[4] ) {
    float radius = 100;
    for (int i = 0; i < 180; i+=15) {
        float radians = i * PI/180.0;
        float screen0[4] = {-radius * cos(radians), -radius * sin(radians), 0.0, 0.0};
        float screen1[4] = {radius * cos(radians), radius * sin(radians), 0.0, 0.0};
        Point *p0 = make_point(screen0, color);
        Point *p1 = make_point(screen1, color);
        draw_line(p0, p1);
    }
}

void draw_grid( float color[4] ) {
    for (int i = -300; i <= 300; i += 50) {
        float screen0[4] = {-300.0, i, 0.0, 0.0};
        float screen1[4] = {300.0, i, 0.0, 0.0};
        Point *p0 = make_point(screen0, color);
        Point *p1 = make_point(screen1, color);
        draw_line(p0, p1);
        free(p0);
        free(p1);
        screen0[0] = -300.0; screen0[1] = i;
        screen1[0] = 300.0; screen1[1] = i;
        p0 = make_point(screen0, color);
        p1 = make_point(screen1, color);
        draw_line(p0, p1);
    }
}

void draw_cube(float color[4]) {
    float pos[4] = {-1.0, -1.0, -1.0};
    Camera *cam = make_camera(200.0, pos);
    printf("Make cube\n");
    Mesh *cube = make_cube(color);
    printf("Transform\n");
    transform(cam, cube);
    printf("Ortho\n");
    ortho(cam, cube);
    printf("Wireframe\n");
    wireframe(cam, cube);
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

    float color[4] = {1.0, 1.0, 1.0, 1.0};
    draw_cube(color);
    
    render_to_screen();
    
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
