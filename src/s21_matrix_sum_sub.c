#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (s21_matrix_not_NULL(A) && s21_matrix_not_NULL(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      flag = s21_create_matrix(A->rows, A->columns, result);
      if (flag == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
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

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (s21_matrix_not_NULL(A) && s21_matrix_not_NULL(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      flag = s21_create_matrix(A->rows, A->columns, result);
      if (flag == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
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
