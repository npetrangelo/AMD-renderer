#include <stdlib.h>
#include "line.h"
#include "bresenham.h"

void plotLineLow(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x < x1; x++) {
        draw_point(x, y);
        if (D > 0) {
            y = y + yi;
            D += 2*(dy - dx);
        } else {
            D += 2*dy;
        }
    }
}

void plotLineHigh(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;

    for (int y = y0; y < y1; y++) {
        draw_point(x, y);
        if (D > 0) {
            x += xi;
            D += 2*(dx - dy);
        } else {
            D += 2*dx;
        }
    }
}

void plotLine(int x0, int y0, int x1, int y1) {
    if (abs(y1 - y0) < abs(x1 - x0)) {
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

void bresenham(float x0, float y0, float x1, float y1) {
    plotLine((int) x0, (int) y0, (int) x1, (int) y1);
}