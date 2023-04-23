#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = OK;

  if (s21_matrix_not_NULL(A)) {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (flag == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
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

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (s21_matrix_not_NULL(A) && s21_matrix_not_NULL(B) &&
      A->columns == B->rows) {
    flag = s21_create_matrix(A->rows, B->columns, result);
    if (flag == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          double sum = 0;
          for (int k = 0; k < A->columns; k++) {
            sum += A->matrix[i][k] * B->matrix[k][j];
          }
          result->matrix[i][j] = sum;
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
