#include <stdlib.h>
#include <math.h>
#include "line.h"
#include "xiaolin.h"

#define ipart(x) ((int) x)
#define fpart(x) (x - ipart(x))

static void plotLineLow(float x0, float y0, float x1, float y1) {
    float slope = (y1 - y0)/(x1 - x0);
    float y = y0;

    for (int x = x0; x < x1; x++) {
        set_color(1.0, 1.0, 1.0, 1.0 - fpart(y));
        draw_point(x, ipart(y));

        set_color(1.0, 1.0, 1.0, fpart(y));
        draw_point(x, ipart(y) + 1);

        y += slope;
    }
}

static void plotLineHigh(float x0, float y0, float x1, float y1) {
    float slope = (x1 - x0)/(y1 - y0);
    float x = x0;

    for (int y = y0; y < y1; y++) {
        set_color(1.0, 1.0, 1.0, 1.0 - fpart(x));
        draw_point(ipart(x), y);

        set_color(1.0, 1.0, 1.0, fpart(x));
        draw_point(ipart(x) + 1, y);

        x += slope;
    }
}

void xiaolin(float x0, float y0, float x1, float y1) {
    if (fabs(y1 - y0) < fabs(x1 - x0)) {
        if (x0 > x1) {
            plotLineLow(x1, y1, x0, y0);
        } else {
            plotLineLow(x0, y0, x1, y1);
        }
    } else {
        if (y0 > y1) {
            plotLineHigh(x1, y1, x0, y0);
        } else {
            plotLineHigh(x0, y0, x1, y1);
        }
    }
}