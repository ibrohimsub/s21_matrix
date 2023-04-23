#include "s21_matrix.h"

// Function to calculate the minor of a matrix element
double s21_minor(matrix_t *A, int i, int j) {
  int n = A->rows;
  double minor;
  matrix_t B;

  // Check for the base case of 1x1 matrix
  if (n == 1) {
    minor = A->matrix[0][0];
  } else {
    // Allocate memory for the submatrix
    s21_create_matrix(n - 1, n - 1, &B);

    // Construct the submatrix by removing the i-th row and the j-th column
    for (int k = 0; k < n; k++) {
      if (k < i) {
        for (int l = 0; l < j; l++) {
          B.matrix[k][l] = A->matrix[k][l];
        }
        for (int l = j + 1; l < n; l++) {
          B.matrix[k][l - 1] = A->matrix[k][l];
        }
      } else if (k > i) {
        for (int l = 0; l < j; l++) {
          B.matrix[k - 1][l] = A->matrix[k][l];
        }
        for (int l = j + 1; l < n; l++) {
          B.matrix[k - 1][l - 1] = A->matrix[k][l];
        }
      }
    }

    // Calculate the determinant of the submatrix
    s21_determinant(&B, &minor);

    // Free memory for the submatrix
    s21_remove_matrix(&B);
  }

  return minor;
}

// Function to calculate the matrix of algebraic complements
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (!s21_matrix_not_NULL(A)) {
    flag = ERR_MAT;
  } else if (A->rows != A->columns) {
    flag = ERR_CAL;
  } else {
    int n = A->rows;

    // Create a new matrix for the result
    flag = s21_create_matrix(n, n, result);
    if (flag == OK) {
      // Calculate the algebraic complement for each element
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          double minor = s21_minor(A, i, j);
          double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
          result->matrix[i][j] = sign * minor;
        }
      }
    }
  }

  return flag;
}
