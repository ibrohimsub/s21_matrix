#include "s21_matrix.h"

// Function to create a new matrix
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = OK;

  if (rows < 1 || columns < 1) {
    flag = ERR_MAT;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    flag = ERR_MAT;
    if (result->matrix != NULL) {
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
      flag = OK;
    }
  }
  return flag;
}

// Function to remove a matrix and free its memory
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

// void print_matrix(matrix_t *matrix) {
//   // printf("ma1");
//   for (int i = 0; i < matrix->rows; i++) {
//     for (int j = 0; j < matrix->columns; j++) {
//       printf("%.2f ", matrix->matrix[i][j]);
//     }
//     printf("\n");
//   }
// }
