#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0) {
    flag = ERR_MAT;
    goto END;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    flag = ERR_CAL;
    goto END;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }

END:
// printf("cddc\n");
  return flag;
}
