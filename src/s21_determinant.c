#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;

  if (!s21_matrix_not_NULL(A) || A->rows != A->columns) {
    flag = ERR_MAT;
  } else {
    int n = A->rows;

    // Base case: 2x2 matrix
    if (n == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      double det = 0.0;
      int sign = 1;

      // Create cofactor matrix
      matrix_t cofactor;
      s21_create_matrix(n - 1, n - 1, &cofactor);

      for (int i = 0; i < n; i++) {
        // Get cofactor of element A[0][i]
        int r = 0;
        for (int j = 0; j < n; j++) {
          if (j == i) continue;

          for (int k = 1; k < n; k++) {
            cofactor.matrix[r][k - 1] = A->matrix[j][k];
          }

          r++;
        }

        // Add the cofactor times the sign to the determinant
        double subdet;
        flag = s21_determinant(&cofactor, &subdet);
        if (flag != OK) {
          s21_remove_matrix(&cofactor);
          return ERR_CAL;
        }

        det += sign * A->matrix[0][i] * subdet;
        sign *= -1;
      }

      *result = det;
      s21_remove_matrix(&cofactor);
    }
  }

  return flag;
}
