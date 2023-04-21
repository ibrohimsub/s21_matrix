#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int flag = OK;
    
    if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
        flag = ERR_MAT;
        goto END;
    }
    
    int n = A->rows;
    if (n != A->columns) {
        flag = ERR_MAT;
        goto END;
    }
    
    result->rows = n;
    result->columns = n;
    
    result->matrix = calloc(n, sizeof(double *));
    if (result->matrix == NULL) {
        flag = ERR_CAL;
        goto END;
    }
    
    for (int i = 0; i < n; i++) {
        result->matrix[i] = calloc(n, sizeof(double));
        if (result->matrix[i] == NULL) {
            flag = ERR_CAL;
            for (int j = 0; j < i; j++) {
                free(result->matrix[j]);
            }
            free(result->matrix);
            goto END;
        }
        for (int j = 0; j < n; j++) {
            matrix_t minor_matrix;
            minor_matrix.rows = n - 1;
            minor_matrix.columns = n - 1;
            minor_matrix.matrix = calloc(minor_matrix.rows, sizeof(double *));
            if (minor_matrix.matrix == NULL) {
                flag = ERR_CAL;
                goto FREE_MATRIX;
            }
            for (int k = 0; k < minor_matrix.rows; k++) {
                minor_matrix.matrix[k] = calloc(minor_matrix.columns, sizeof(double));
                if (minor_matrix.matrix[k] == NULL) {
                    flag = ERR_CAL;
                    for (int l = 0; l < k; l++) {
                        free(minor_matrix.matrix[l]);
                    }
                    free(minor_matrix.matrix);
                    goto FREE_MATRIX;
                }
            }
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            double minor = 0;
            for (int k = 0; k < n; k++) {
                if (k != i) {
                    for (int l = 0; l < n; l++) {
                        if (l != j) {
                            minor_matrix.matrix[k - (k > i)][l - (l > j)] = A->matrix[k][l];
                        }
                    }
                }
            }
            flag = s21_calc_minor(&minor_matrix, &minor);
            if (flag != OK) {
                for (int k = 0; k < minor_matrix.rows; k++) {
                    free(minor_matrix.matrix[k]);
                }
                free(minor_matrix.matrix);
                goto FREE_MATRIX;
            }
            result->matrix[i][j] = sign * minor;
            for (int k = 0; k < minor_matrix.rows; k++) {
                free(minor_matrix.matrix[k]);
            }
            free(minor_matrix.matrix);
        }
    }
    
END:
    return flag;
    
FREE_MATRIX:
    for (int i = 0; i < n; i++) {
        free(result->matrix[i]);
    }
    free(result->matrix);
    goto END;
}
