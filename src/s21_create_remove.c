#include "s21_matrix.h"

// Function to create a new matrix
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = OK;  // set initial flag to OK
  // Check input parameters
  if (rows <= 0 || columns <= 0) {
    flag = ERR_MAT;  // set flag to ERR_MAT
    goto END;        // jump to the end
  }
  // Allocate memory for matrix
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    flag = ERR_CAL;  // set flag to ERR_CAL
    goto END;        // jump to the end
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      // Free previously allocated memory
      s21_remove_matrix(result);
      flag = ERR_CAL;  // set flag to ERR_CAL
      goto END;        // jump to the end
    }
  }
  // Set matrix dimensions
  result->rows = rows;
  result->columns = columns;
  // Initialize matrix elements to zero
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = 0.0;
    }
  }
END:
  return flag;  // return the flag
}

// Function to remove a matrix and free its memory
void s21_remove_matrix(matrix_t* A) {
  // Free memory for matrix elements
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  // Free memory for matrix struct
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}
