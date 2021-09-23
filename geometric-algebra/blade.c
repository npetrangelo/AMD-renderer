#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "vector.h"
#include "blade.h"

static blade* alloc_blade(int n) {
    blade *b = malloc(sizeof(blade));
    b->len = n;
    b->arr = malloc(sizeof(vector) * n);
    return b;
}

void free_blade(blade *b) {
    if (!b) return;
    for (int i = 0; i < b->len; i++) {
        free_vector(b->arr[i]);
    }
    free(b->arr);
    free(b);
}

blade* make_blade(int count, ...) {
    if (count < 1 || count > 3) return NULL;

    blade *b = alloc_blade(count);

    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        b->arr[i] = va_arg(ap, vector*);
        if (b->arr[0]->len != b->arr[i]->len) {
            printf("Cannot make trivector: Incompatible vector lengths");
            free_blade(b);
            return NULL;
        }
    }
    va_end(ap);
    return b;
}

blade* univector(vector* v) { return make_blade(1, v); }
blade* bivector(vector* v1, vector* v2) { return make_blade(2, v1, v2); }
blade* trivector(vector* v1, vector* v2, vector* v3) { return make_blade(3, v1, v2, v3); }

blade* badd(blade* b1, blade* b2) {
    if (b1->len != b2->len) {
        printf("Cannot add: Incompatible blade lengths %d != %d\n", b1->len, b2->len);
        return NULL;
    }
    blade *b = alloc_blade(b1->len);
    for (int i = 0; i<b1->len; i++) {
        b->arr[i] = vadd(b1->arr[i], b2->arr[i]);
    }
    return b;
}

blade* bmultiply(blade* b1, blade* b2) {
    if (b1->arr[0]->len != b2->arr[0]->len) {
        printf("Cannot multiply: Incompatible dimensions %d != %d\n", b1->arr[0]->len, b2->arr[0]->len);
        return NULL;
    }
    blade *b = alloc_blade(b1->len + b2->len);
    for (int i = 0; i<b1->len; i++) {
        b->arr[i] = b1->arr[i];
    }
    for (int i = 0; i<b1->len; i++) {
        b->arr[i+b1->len] = b2->arr[i];
    }
    return b;
    // TODO
    // Append vector arrays in order
    // Internal vectors must be of equal dimension; compare first vector in each array
}