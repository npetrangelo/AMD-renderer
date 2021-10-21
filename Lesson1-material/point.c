#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "vector.h"
#include "point.h"

Point* make_point(float screen[4], float color[4]) {
    Point *p = malloc(sizeof(Point));
    vcopy(screen, p->screen);
    vcopy(color, p->color);
    return p;
}