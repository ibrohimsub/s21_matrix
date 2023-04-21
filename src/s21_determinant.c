#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
    int flag = OK;
    
    if (A == NULL || A->rows != A->columns || A->rows <= 0) {
        flag = ERR_MAT;
        goto END;
    }
    
    if (A->rows == 1) {
        *result = A->matrix[0][0];
        goto END;
    }
    
    double det = 0.0;
    
    matrix_t minor;
    minor.rows = A->rows - 1;
    minor.columns = A->columns - 1;
    minor.matrix = calloc(minor.rows, sizeof(double *));
    if (minor.matrix == NULL) {
        flag = ERR_CAL;
        goto END;
    }
    
    for (int i = 0; i < minor.rows; i++) {
        minor.matrix[i] = calloc(minor.columns, sizeof(double));
        if (minor.matrix[i] == NULL) {
            flag = ERR_CAL;
            for (int j = 0; j < i; j++) {
                free(minor.matrix[j]);
            }
            free(minor.matrix);
            goto END;
        }
    }
    
    for (int j = 0; j < A->columns; j++) {
        int sign = (j % 2 == 0) ? 1 : -1;
        flag = s21_get_minor(A, &minor, 0, j);
        if (flag != OK) {
            goto CLEANUP;
        }
        double minor_det;
        flag = s21_determinant(&minor, &minor_det);
        if (flag != OK) {
            goto CLEANUP;
        }
        det += sign * A->matrix[0][j] * minor_det;
    }
    
    *result = det;
    
CLEANUP:
    for (int i = 0; i < minor.rows; i++) {
        free(minor.matrix[i]);
    }
    free(minor.matrix);
    
END:
    return flag;
}
