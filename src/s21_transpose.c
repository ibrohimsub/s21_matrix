#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (s21_matrix_not_NULL(A)) {
    flag = s21_create_matrix(A->columns, A->rows, result);
    if (flag == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      flag = ERR_CAL;
    }
  } else {
    flag = ERR_MAT;
  }

  return flag;
}