#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include "utility.h"

void console_log(Log_Level log_level, char *format, ...) {
    if (log_level >= print_logs) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

/*
 * flerp()
 */
float flerp(float a, float b, float t)
{
    return a*(1.0-t) + b*t;
}

float flerp_inv(float a, float b, float x) {
    return (a - x) / (a - b);
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

int signum(float x) {
    return (x > 0.0) - (x < 0.0);
}

/**
 * Valid between -pi and pi radians
 */
float half_angle_cos(float cosx) {
    return sqrt((1+cosx)/2.0);
}

/**
 * Valid between -pi and pi radians
 */
float half_angle_sin(float cosx, float sinx) {
    return copysignf(sqrt((1-cosx)/2.0), sinx);
}