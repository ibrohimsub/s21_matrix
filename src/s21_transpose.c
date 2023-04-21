#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
    int flag = OK;

    if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
        flag = ERR_MAT;
        goto END;
    }

    int rows = A->columns;
    int columns = A->rows;

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
            result->matrix[i][j] = A->matrix[j][i];
        }
    }

END:
    return flag;
}
