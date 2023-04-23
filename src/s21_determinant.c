#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;

  if (!s21_matrix_not_NULL(A)) {
    flag = ERR_MAT;
  } else if (A->rows != A->columns) {
    flag = ERR_CAL;
  } else {
    int n = A->rows;
    double det = 0;
    matrix_t B;

    // Check for the base case of 1x1 matrix
    if (n == 1) {
      det = A->matrix[0][0];
    } else {
      // Allocate memory for the submatrix
      s21_create_matrix(n - 1, n - 1, &B);

      for (int i = 0; i < n; i++) {
        // Construct the submatrix by removing the i-th row and the 0-th column
        for (int j = 1; j < n; j++) {
          for (int k = 0; k < n; k++) {
            if (k < i) {
              B.matrix[j - 1][k] = A->matrix[j][k];
            } else if (k > i) {
              B.matrix[j - 1][k - 1] = A->matrix[j][k];
            }
          }
        }

        // Calculate the determinant recursively by multiplying the element with
        // its cofactor
        double sign = (i % 2 == 0) ? 1.0 : -1.0;
        double cofactor;
        flag = s21_determinant(&B, &cofactor);
        if (flag == OK) {
          det += sign * A->matrix[0][i] * cofactor;
        }
      }

      // Free memory for the submatrix
      s21_remove_matrix(&B);
    }

    *result = det;
  }

  return flag;
}
