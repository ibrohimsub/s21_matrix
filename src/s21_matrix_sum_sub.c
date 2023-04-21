#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int flag = OK;

    // Check if the matrices have the same dimensions
    if (A->rows != B->rows || A->columns != B->columns) {
        flag = ERR_MAT;
        goto END;
    }

    // Allocate memory for the result matrix
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
        flag = ERR_CAL;
        goto END;
    }

    // Compute the sum of the matrices
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }

END:
    return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int flag = OK;

    // Check if the matrices have the same dimensions
    if (A->rows != B->rows || A->columns != B->columns) {
        flag = ERR_MAT;
        goto END;
    }

    // Allocate memory for the result matrix
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
        flag = ERR_CAL;
        goto END;
    }

    // Compute the difference of the matrices
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
    }

END:
    return flag;
}
