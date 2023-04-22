#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = OK;  // set initial flag to OK
  double det = 0.0;

  // Check if the matrix is square
  if (A->rows != A->columns) {
    flag = ERR_MAT;
    goto END;
  }

  // Calculate the determinant
  flag = s21_determinant(A, &det);
  if (flag != OK) {
    goto END;
  }

  // Check if the determinant is zero
  if (det == 0.0) {
    flag = ERR_MAT;
    goto END;
  }

  // Calculate the adjugate matrix
  flag = s21_calc_complements(A, result);
  if (flag != OK) {
    goto END;
  }

  // Divide by the determinant
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] /= det;
    }
  }

END:
  return flag;
}
