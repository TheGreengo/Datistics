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

// look into bareiss algorithm
// ! This is probably broken
double mat_det(double ** mat, unsigned int siz){
    int swap = 1;
    double coef = 1;

    for (int i = 0; i < siz; i++) {
        int ind = i;
        while (mat[i][ind] == 0) {
            ind++;
        }
        if (ind != i) {
            // swap the two rows
            swap *= -1;
        }
        // here we loop through the the remaining rows
        for (int j = i + 1; j < siz; j++) {
            // and first get the coefficient
            coef = mat[j][i] / mat[i][i];

            // then update each entry 
            for (int k = i; k < siz; k++ ){
                mat[j][k] -= (coef * mat[i][k]);
            }
        }
    }

    int final = 1;
    for (int i = 0; i < siz; i++) {
        final *= mat[i][i];
    }

    return final * swap;
}

// mat^{-1} = res
void mat_inv(double ** mat, double ** res, unsigned int siz){
    // get determinate
    double det = mat_det(mat, siz);

    // get adjoint
    return;
}

// a' * b = c
void x_prime_y(double ** x, double * y, double * res, unsigned int rows, unsigned int cols) {
    for (int i = 0; i < cols; i++) {
        double num = 0.0;
        for (int j = 0; j < rows; j++) {
            num += (y[j] * x[j][i]);
        }
        res[i] = num;
    }
}

// a * b = c
// ! This is probably broken
void fin_mult(double ** b, double * c, double * beta, unsigned int rows, unsigned int cols) {
    for (int i = 0; i < cols; i++) {
        double num = 0.0;
        for (int j = 0; j < rows; j++) {
            num += (c[j] * b[i][j]);
        }
        beta[i] = num;
    }
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
    for (int i = 0; i < 3; i ++) {
        f[i] = i+1;
    }

    x_prime_x(a, e, 3, 3);
    x_prime_y(a, f, g, 3, 3);

    for (int i = 0; i < 3; i ++) {
        printf("%f \n", g[i]);
    }

    mat_print(e, 3, 3);

    mat_print(a, 3, 3);
    mat_dest(&a, 3);

    mat_dest(&e, 3);
    free(f);
    free(g);
}
