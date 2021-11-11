#pragma once

typedef enum {Debug=0, Info=1, Warn=2, Error=3, Fatal=4} Log_Level;
extern Log_Level print_logs;

void console_log(Log_Level log_level, char *format, ...);

float flerp(float a, float b, float t);
float random_float( float low, float high );
float random_int( int low, int high );
float randomGL( int m );
double sign( double a );
double dabs( double a );
int signum(float x);
float half_angle_cos(float cosx);
float half_angle_sin(float cosx, float sinx);