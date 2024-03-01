#include "regression.h"
#include <stdlib.h>

// -1  2 -1
//  0 -1  1
//  2 -1  0
// B = (X'X)^{-1}X'Y

// x is ents by vars
// y is ents by 1
// x'x is vars by vars
// x'y is vars by 1
// b is vars by 1

/*
* This function should create a swap matrix and within it
* x and y should be initialized and be the right size
* b should be unitialized
* rows and columns 
* x should be 
* B = (X'X)^{-1}X'Y
*/
void reg(double * y, double ** x, double * b, unsigned int ents, unsigned int vars) {
    // * initializing and making the swap matrices
    double ** a, c;
    mat_init(&a, vars, vars);
    mat_init(&c, vars, 1);

    // * make the c = X'X
    mat_t_mult(&x, &x, &c);

    // * make a = c^{-1}
    mat_inv(&c, &a);

    // * make c = X'Y
    mat_t_mult(&x, &y, &c);

    // * make b = (X'X)^{-1}X'Y
    mat_mult(&a, &c, &b);

    // * clean up temps
    mat_dest(&a, vars);
    mat_dest(&c, vars);
    // we need to mult(inv(mult(tran(x),x))mat_mult(tran(x),y))
}

// a * b = c
void mat_mult(double *** a, double *** b, double *** c) {
    return a;
}

// a' * b = c
void mat_t_mult(double *** a, double *** b, double *** c) {
    return a;
}

// mat' = res
void mat_tran(double *** mat, double *** res){
    return mat;
}


double mat_det(double *** mat){
    return 3;
}

// mat^{-1} = res
int mat_inv(double *** mat, double *** res){
    return 3;
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

int main(void) {
    // a and c for swapping, 
    double ** b, x, y;
    double test_a[3][3] = {
    {1.0, 1.0, 1.0},
    {2.0, 2.0, 1.0},
    {2.0, 3.0, 1.0}
    };

    double ** a;
    mat_init(&a, 3, 3);
    for (int i = 0; i < 3; i ++) {
        a[i][0] = test_a[i][0];
        a[i][1] = test_a[i][1];
        a[i][2] = test_a[i][2];
    }
    mat_print(a, 3, 3);
    mat_dest(&a, 3);
}
