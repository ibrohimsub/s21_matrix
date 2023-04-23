#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = FAILURE;
  if (s21_not_NULL(A) && s21_not_NULL(B)) {
    // Check if the matrices have the same dimensions
    if (A->rows == B->rows && A->columns == B->columns) {
      flag = SUCCESS;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          // Check if the corresponding elements are identical up to 7 decimal
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
            flag = FAILURE;
          }
        }
      }
    }
  }
  return flag;
}

int s21_matrix_not_NULL(matrix_t *matrix) {
  int flag = SUCCESS;
  if (matrix != NULL && matrix->matrix != NULL && matrix->rows >= 1 &&
      matrix->columns >= 1) {
    flag = SUCCESS;
  } else {
    flag = FAILURE;
  }
  return flag;
}
