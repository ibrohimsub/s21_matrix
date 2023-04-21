#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int flag = OK;

    // Check if the matrix is square
    if (A->rows != A->columns) {
        flag = ERR_MAT;
        goto END;
    }
    
    // Check if the matrix has an inverse
    double det;
    int det_status = s21_determinant(A, &det);
    if (det_status != OK || det == 0) {
        flag = ERR_CAL;
        goto END;
    }
    
    // Allocate memory for the minor matrix and matrix of algebraic complements
    matrix_t minor, adj;
    minor.rows = minor.columns = adj.rows = adj.columns = A->rows;
    minor.matrix = (double **) calloc(minor.rows, sizeof(double *));
    adj.matrix = (double **) calloc(adj.rows, sizeof(double *));
    for (int i = 0; i < A->rows; i++) {
        minor.matrix[i] = (double *) calloc(minor.columns, sizeof(double));
        adj.matrix[i] = (double *) calloc(adj.columns, sizeof(double));
    }
    
    // Calculate the minor matrix and matrix of algebraic complements
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            s21_minor(A, &minor, i, j);
            adj.matrix[i][j] = sign * det * minor.matrix[j][i];
            sign = -sign;
        }
        sign = -sign;
    }
    
    // Calculate the transpose of matrix of algebraic complements
    matrix_t adj_t;
    adj_t.rows = adj.columns;
    adj_t.columns = adj.rows;
    adj_t.matrix = (double **) calloc(adj_t.rows, sizeof(double *));
    for (int i = 0; i < adj_t.rows; i++) {
        adj_t.matrix[i] = (double *) calloc(adj_t.columns, sizeof(double));
    }
    for (int i = 0; i < adj_t.rows; i++) {
        for (int j = 0; j < adj_t.columns; j++) {
            adj_t.matrix[i][j] = adj.matrix[j][i];
        }
    }
    
    // Calculate the inverse matrix
    result->rows = A->rows;
    result->columns = A->columns;
    result->matrix = (double **) calloc(result->rows, sizeof(double *));
    for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = (double *) calloc(result->columns, sizeof(double));
    }
    double inv_det = 1 / det;
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = inv_det * adj_t.matrix[i][j];
        }
    }
    
    // Free memory
    for (int i = 0; i < minor.rows; i++) {
        free(minor.matrix[i]);
    }
    free(minor.matrix);
    for (int i = 0; i < adj.rows; i++) {
        free(adj.matrix[i]);
    }
    free(adj.matrix);
    for (int i = 0; i < adj_t.rows; i++) {
        free(adj_t.matrix[i]);
    }
    free(adj_t.matrix);
    
END:
    return flag;
}
