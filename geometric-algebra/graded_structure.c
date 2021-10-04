#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "graded_structure.h"

static unsigned int len(gradedStructure *g) {
    return pow(2, g->space);
}

static short map[0b1<<3][0b1<<3] = {{1,1,1,1,1,1,1,1},
                                    {1,1,1,1,0,0,1,1},
                                    {1,0,1,0,1,1,1,1},
                                    {1,0,1,0,1,1,0,0},
                                    {1,1,0,1,1,1,0,1},
                                    {1,1,1,0,0,0,1,0},
                                    {1,1,0,1,1,0,0,1},
                                    {1,1,1,0,1,0,0,0}};

static gradedStructure* alloc_gradedStructure(unsigned int space) {
    gradedStructure *g = malloc(sizeof(gradedStructure));
    g->space = space;
    g->arr = malloc(sizeof(double) * pow(2, space));
    for (unsigned int i = 0; i < len(g); i++) {
        g->arr[i] = 0;
    }
    return g;
}

void free_multivector(gradedStructure *g) {
    if (!g) return;
    free(g->arr);
    free(g);
}

gradedStructure* make_vector(unsigned int space, ...) {
    gradedStructure *g = alloc_gradedStructure(space);

    va_list ap;
    va_start(ap, space);
    for (unsigned int i = 0; i < space; i++) {
        g->arr[0b1<<i] = va_arg(ap, double);
    }
    va_end(ap);
    return g;
}

gradedStructure* vector2(double x, double y) { return make_vector(2, x, y); }
gradedStructure* vector3(double x, double y, double z) { return make_vector(3, x, y, z); }
gradedStructure* vector4(double x, double y, double z, double w) { return make_vector(4, x, y, z, w); }

gradedStructure* gadd(gradedStructure* g1, gradedStructure* g2) {
    gradedStructure *g = alloc_gradedStructure(max(g1->space, g2->space);
    int minLength = pow(2, min(g1->space, g2->space));

    for (int i = 0; i < minLength; i++) {
        g->arr[i] = g1->arr[i] + g2->arr[i];
    }

    if (g1->space == g2->space) return g;

    gradedStructure* gmax = (g1->space > g2->space) ? g1 : g2;
    for (int i = minLength; i < len(g); i++) {
        g->arr[i] = gmax->arr[i];
    }

    return g;
}

gradedStructure* wedge(gradedStructure* g1, gradedStructure* g2) {
    gradedStructure *g = alloc_gradedStructure(max(g1->space, g2->space);

    // Scale g1 by g2 scalar
    for (unsigned int i = 1; i < len(g1); i++) {
        g[i] += g2[0]*g1[i];
    }

    // Scale g2 by g1 scalar
    for (unsigned int j = 1; j < len(g2); j++) {
        g[j] += g1[0]*g2[j];
    }

    for (unsigned int i = 1; i < len(g1); i++) {
        for (unsigned int j = 1; j < len(g2); j++) {
            if (i <= g1->space && j <= g2->space) {
                g[(i)^(j)] += g1[i]*g2[j];
            }
            if (i <= g2->space && j <= g1->space) {
                g[(i)^(j)] -= g2[i]*g1[j];
            }
        }
    }

    return g;
}

double gdot(gradedStructure* g1, gradedStructure* g2) {
    double sum = 0;

    for (unsigned int i = 0; i < min(g1->space, g2->space); i++) {
        double sum = g1[i]*g2[i]*map[i][i];
    }

    return sum;
}