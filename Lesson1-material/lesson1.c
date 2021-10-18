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

void sierpinski( void )
{
    set_color(1.0, 1.0, 1.0, 0.0);
    int xs[3] = {random_int(-400, 400), random_int(-400, 400), random_int(-400, 400)};
    int ys[3] = {random_int(-400, 400), random_int(-400, 400), random_int(-400, 400)};

    int index = randomGL(3);
    int x = xs[index];
    int y = ys[index];
    draw_point(x, y);
    for (int i = 0; i < 100000; i++) {
        int index = randomGL(3);
        x = (x + xs[index])/2;
        y = (y + ys[index])/2;
        draw_point(x, y);
    }
}

void hopalong( void )
{
    double x        = 0;
    double y        = 0;
    double A        = random_float(-20,20);
    double B        = (random_float(-1,1));
    double C        = (random_float(-1,1));
    double scale    = 10.0;
    double newx;
    double newy;
    float  r, g, b;
    
    /*
     * draw hopalog orbit discovered by Barry Martin
     *
     * interesting values to try:
     *
     *        a = 73, b = 2.6, c = 25
     *        a = -200, b = .1, c = -80
     *        a = .4, b = 1, c = 0 (try a scale of 100 
     *        a = -3.14, b = .3, c = .3
     */
    for( int i = 0; i < 20000; i++ )
    {
        newx    = y - sign(x) * dabs( B * x - C );
        newy    = A - x;
        x       = newx;
        y       = newy;
        
        draw_point( scale * x, scale * y );
        
        if( !(i % 1000) )
        {
            r = random_float( 0, 1);
            g = random_float( 0, 1);
            b = random_float( 0, 1);
            
            set_color( r, g, b, 1.0 );
        }
    }
}

void bifurcate( void )
{
    set_color(1.0, 1.0, 1.0, 0.0);
	double x;
	double y = 0;	
	double r = 2;
	double inc = 0.004;
	
	/*
	 *	calculate bifurcation plot
	 */			
	for( int i = 0; i < 800; i++ ) {
		x = 0.5;
		r += inc;
		
		for( int j = 0; j < 200; j++ ) {
			x = r * x * (1 - x);
			draw_point( x*800 - 400, y - 400 );
		}	
	
		y = y + 1;
	}
}

void mandelbrot( float acorner, float bcorner, float xside, float yside )
{
	float a, b;
	float x, y, next_x, next_y;
	float shade;
	float xinc = xside/800;
	float yinc = yside/800;
	int count, j, k;
	
	a = acorner;
	for( j = -400; j < 400; j++ )
	{
		b = bcorner;
		for( k = -400; k < 400; k++ )
		{
			x = 0.0;
			y = 0.0;
			count = 0;
			
			while(count < 50 && (x * x + y * y) < 4)
			{
				next_x = x * x - y * y + a;
				next_y = 2 * x * y + b;
				
				x = next_x;
				y = next_y;
				
				count = count + 1;
			}
			
			shade = count/50.0;
		    set_color(shade, shade, shade, 1.0);
			draw_point(j+0.5, k+0.5);
			
			b -= yinc;
		}
		a +=  xinc;
	}
}

void draw_mandelbrot( void )
{
	mandelbrot( -2, 1.5, 3 , 3 );   // whole Mandelbrot set
	//mandelbrot( -2 + 1.5/2, 1.5 - 1.5/2.0, 1.5/2, 1.5/2 );
	//mandelbrot( -1.0, 0, 0.35 , 0.25 );
	//mandelbrot( -1.30, -0.25, 0.35 , 0.25 );
	//mandelbrot( -1.30, -0.25, 0.35/2 , 0.25/2 );
}

void julia( float acorner, float bcorner, float a_constant, float b_constant, float xside, float yside )
{
	float a, b;
	float x, y, next_x, next_y;
	float shade;
	float xinc = xside/800;
	float yinc = yside/800;
	int count, j, k;
	
	b = bcorner;
	for(k = -400; k < 400; k++)
	{
		a = acorner;
		for(j = -400; j < 400; j++)
		{	
			x = a;
			y = b;
			count = 0;
			while(count < 50 && (x * x + y * y) < 4)
			{
				next_x = x * x - y * y + a_constant;
				next_y = 2 * x * y + b_constant;
				
				x = next_x;
				y = next_y;
				
				count = count + 1;
			}
			
			shade = count/50.0;
	        set_color(shade, shade, shade, 1.0);
			draw_point(j+0.5, k+0.5);
			
			a += xinc;
		}
		b -= yinc;
	}
}

void draw_julia( void )
{
	julia( -1.5, 1.8, 1.14, 0.25, 3, 3.6 );
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
