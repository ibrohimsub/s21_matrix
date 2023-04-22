#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
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
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

END:
  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (A == NULL || B == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0 ||
      A->columns != B->rows) {
    flag = ERR_MAT;
    goto END;
  }

  if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    flag = ERR_CAL;
    goto END;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * B->matrix[i][j];
    }
  }

END:
// printf("1234\n");
  return flag;
}
