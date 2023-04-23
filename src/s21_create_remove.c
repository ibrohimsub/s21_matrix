#include "s21_matrix.h"

// Function to create a new matrix
int s21_create_matrix(int rows, int columns, matrix_t *flagult) {
  int flag = OK;

  if (rows < 1 || columns < 1) {
    flag = ERR_MAT;
  } else {
    flagult->rows = rows;
    flagult->columns = columns;
    flagult->matrix = calloc(rows, sizeof(double *));
    flag = ERR_MAT;
    if (flagult->matrix != NULL) {
      for (int i = 0; i < flagult->rows; i++) {
        flagult->matrix[i] = calloc(columns, sizeof(double));
      }
      flag = OK;
    } else {
      flag = ERR_CAL;
    }
  }
  return flag;
}

// Function to remove a matrix and free its memory
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    // Free memory for matrix elements
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
