#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "vector.h"
#include "blade.h"
#include "matrix.h"

static matrix* alloc_matrix(int rows, int cols) {
    matrix *m = malloc(sizeof(matrix));
    m->rows = rows;
    m->cols = cols;
    m->arr = malloc(sizeof(double*) * cols);
    for (int i = 0; i < cols; i++) {
        m->arr[i] = malloc(sizeof(double) * rows);
    }
    return m;
}

void free_matrix(matrix* m) {
    for (int i = 0; i < m->cols; i++) {
        free(m->arr[i]);
    }
    free(m->arr);
    free(m);
}

matrix* to_matrix(blade* b) {
    matrix* m = alloc_matrix(b->arr[0]->len, b->len);
    for (int i = 0; i < m->cols; i++) {
        for (int j = 0; j < m->rows; j++) {
            m->arr[i][j] = b->arr[i]->arr[j];
        }
    }
    return m;
}

int is_square(matrix* m) {
    return (m->rows == m->cols);
}

/**
 * Generates a submatrix skipping the specified row and column.
 * Used for calculating determinants.
 * 
 * Doesn't skip if given negative number
 */
matrix* msub(matrix* m, int col, int row) {
    matrix* sub;
    if (row < 0 && col < 0) {
        sub = alloc_matrix(m->rows, m->cols);
    } else if (row < 0) {
        row = m->rows;
        sub = alloc_matrix(m->rows, m->cols - 1);
    } else if (col < 0) {
        col = m->cols;
        sub = alloc_matrix(m->rows - 1, m->cols);
    } else {
        sub = alloc_matrix(m->rows - 1, m->cols - 1);
    }

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            sub->arr[i][j] = m->arr[i][j];
        }
        for (int j = row+1; j < m->rows; j++) {
            sub->arr[i][j-1] = m->arr[i][j];
        }
    }

    for (int i = col+1; i < m->cols; i++) {
        for (int j = 0; j < row; j++) {
            sub->arr[i-1][j] = m->arr[i][j];
        }
        for (int j = row+1; j < m->rows; j++) {
            sub->arr[i-1][j-1] = m->arr[i][j];
        }
    }

    return sub;
}

int mdet(matrix* m, double* result) {
    // Fail if matrix isn't square
    if (!is_square(m) || result == NULL) {
        printf("Matrix isn't square: %dx%d\n", m->cols, m->rows);
        return 0;
    }

    if (m->rows == 1) {
        *result = m->arr[0][0];
        return 1;
    }

    *result = 0;
    for (int i = 0; i < m->cols; i++) {
        matrix* sub = msub(m, i, 0);
        double subdet = 0;
        if (!mdet(sub, &subdet)) {
            return 0;
        }
        *result += m->arr[i][0] * ((i%2) ? -subdet : subdet);
    }
    return 1;
}

void mprint(matrix* m) {
    for (int j = 0; j < m->rows; j++) {
        for (int i = 0; i < m->cols; i++) {
            printf("%f  ", m->arr[i][j]);
        }
        printf("\n");
    }
}