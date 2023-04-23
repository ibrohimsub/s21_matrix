#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (!s21_matrix_not_NULL(A) || A->rows != A->columns ||
      !s21_matrix_not_NULL(result) || result->rows != A->rows ||
      result->columns != A->columns) {
    flag = ERR_MAT;
  } else {
    int n = A->rows;

    // Create cofactor matrix
    matrix_t cofactor;
    s21_create_matrix(n - 1, n - 1, &cofactor);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        // Get cofactor of element A[i][j]
        int r = 0;
        int c = 0;
        for (int k = 0; k < n; k++) {
          if (k == i) continue;

          for (int l = 0; l < n; l++) {
            if (l == j) continue;

            cofactor.matrix[r][c] = A->matrix[k][l];
            c++;
          }

          c = 0;
          r++;
        }

        // Calculate determinant of cofactor matrix
        double subdet;
        flag = s21_determinant(&cofactor, &subdet);
        if (flag != OK) {
          s21_remove_matrix(&cofactor);
          return ERR_CAL;
        }

        // Calculate cofactor and assign it to result matrix
        double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
        result->matrix[j][i] = sign * subdet;
      }
    }

    s21_remove_matrix(&cofactor);
  }

  return flag;
}
