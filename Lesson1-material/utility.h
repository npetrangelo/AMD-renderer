#pragma once

extern int print_logs;

void console_log(char *format, ...);

float flerp(float a, float b, float t);
float random_float( float low, float high );
float random_int( int low, int high );
float randomGL( int m );
double sign( double a );
double dabs( double a );