#include "regression.h"
#include <stdlib.h>

// -1  2 -1
//  0 -1  1
//  2 -1  0
// B = (X'X)^{-1}X'Y

// for testing: gcc regression.c -o thing -Wall --std=gnu99 -g3 -Werror -fPIC

// a' * b = c
void x_prime_x(double ** x, double ** res, unsigned int rows, unsigned int cols) {
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            double num = 0.0;
            for (int k = 0; k < rows; k++) {
                num += (x[k][i] * x[k][j]);
            }
            res[i][j] = num;
        }
    }
}

double mat_det(double ** mat){
    return 0.0;
}

// mat^{-1} = res
void mat_inv(double ** mat, double ** res, unsigned int siz){
    return;
}

// a' * b = c
void x_prime_y(double ** x, double * y, double * res, unsigned int rows, unsigned int cols) {
    return;
}

// a * b = c
void fin_mult(double ** b, double * c, double * beta, unsigned int rows, unsigned int cols) {
    return;
}

void mat_print(double ** mat, unsigned int rows, unsigned int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            j + 1 == cols ? printf("%f", mat[i][j]) : printf("%f,", mat[i][j]);
        }
        printf("\n");
    }
}

void mat_init(double *** mat, unsigned int rows, unsigned int cols) {
    (*mat) = (double **) malloc(sizeof(double *) * rows); 
    for (int i = 0; i < rows; i ++) {
        (*mat)[i] = (double *) malloc(sizeof(double) * cols);
    }
}

void mat_dest(double *** mat, unsigned int rows) {
    for (int i = 0; i < rows; i ++) {
        free((*mat)[i]);
    }
    free((*mat));
}

/*
* This function should create a swap matrix and within it
* x and y should be initialized and be the right size
* b should be unitialized
* rows and columns 
* x should be 
* B = (X'X)^{-1}X'Y
*/
void reg(double * y, double ** x, double * beta, unsigned int ents, unsigned int vars) {
    // * initializing and making the swap matrices
    double ** a, ** b;
    double * c;
    mat_init(&a, vars, vars);
    mat_init(&b, vars, vars);
    c = malloc(sizeof(double) * vars);

    // * make the c = X'X
    x_prime_x(x, a, ents, vars);

    // * make a = c^{-1}
    mat_inv(a, b, vars);

    // * make c = X'Y
    x_prime_y(x, y, c, ents, vars);

    // * make b = (X'X)^{-1}X'Y
    fin_mult(b, c, beta, ents, vars);

    // * clean up temps
    mat_dest(&a, vars);
    mat_dest(&b, vars);
    free(c);
}

int main(void) {
    // a and c for swapping, 
    // double ** b, x, y;
    double test_a[3][3] = {
    {1.0, 1.0, 1.0},
    {2.0, 2.0, 1.0},
    {2.0, 3.0, 1.0}
    };

    double ** e;
    double * f, * g;

    mat_init(&e, 3, 3);
    f = malloc(sizeof(double) * 3);
    g = malloc(sizeof(double) * 3);

    reg(f, e, g, 3, 3);

    double ** a;
    mat_init(&a, 3, 3);
    for (int i = 0; i < 3; i ++) {
        a[i][0] = test_a[i][0];
        a[i][1] = test_a[i][1];
        a[i][2] = test_a[i][2];
    }

    x_prime_x(a, e, 3, 3);

    mat_print(e, 3, 3);

    mat_print(a, 3, 3);
    mat_dest(&a, 3);

    mat_dest(&e, 3);
    free(f);
    free(g);
}
