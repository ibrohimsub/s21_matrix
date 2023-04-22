#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  // Check if the matrices have the same dimensions
  if (A->rows != B->rows || A->columns != B->columns) {
    flag = FAILURE;
  } else {
    // Check if the corresponding elements are identical up to 7 decimal places
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double diff = A->matrix[i][j] - B->matrix[i][j];
        if (diff < 0) {
          diff = -diff;
        }
        if (diff >= 1e-7) {
          flag = FAILURE;
          goto END;  // jump to end of function
        }
      }
    }
  }
END:
  return flag;
}
