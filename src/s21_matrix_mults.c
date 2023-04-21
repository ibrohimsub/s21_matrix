#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int flag = OK;

    if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
        flag = ERR_MAT;
        goto END;
    }

    int rows = A->rows;
    int columns = A->columns;

    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
        flag = ERR_CAL;
        goto END;
    }

    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
            flag = ERR_CAL;
            for (int j = 0; j < i; j++) {
                free(result->matrix[j]);
            }
            free(result->matrix);
            goto END;
        }
        for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
        }
    }

END:
    return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int flag = OK;

    if (A == NULL || B == NULL || result == NULL ||
        A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
        B->columns <= 0 || A->columns != B->rows) {
        flag = ERR_MAT;
        goto END;
    }

    int rows = A->rows;
    int columns = B->columns;

    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
        flag = ERR_CAL;
        goto END;
    }

    for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
            flag = ERR_CAL;
            for (int j = 0; j < i; j++) {
                free(result->matrix[j]);
            }
            free(result->matrix);
            goto END;
        }
        for (int j = 0; j < columns; j++) {
            double sum = 0;
            for (int k = 0; k < A->columns; k++) {
                sum += A->matrix[i][k] * B->matrix[k][j];
            }
            result->matrix[i][j] = sum;
        }
    }

END:
    return flag;
}
