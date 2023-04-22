#include "s21_matrix.h"

// Function to calculate the complement matrix of a given matrix
int s21_calc_complements(matrix_t* A, matrix_t* result) {
  int flag = OK;  // set initial flag to OK

  // Check if the matrix is square
  if (A->rows != A->columns) {
    flag = ERR_MAT;
    goto END;
  }

  // Create the matrix of minors
  matrix_t matrix_of_minors;
  flag = s21_create_matrix(A->rows, A->columns, &matrix_of_minors);
  if (flag != OK) {
    goto END;
  }
  flag = s21_matrix_of_minors(A, &matrix_of_minors);
  if (flag != OK) {
    s21_remove_matrix(&matrix_of_minors);
    goto END;
  }

  // Calculate the matrix of cofactors
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = pow(-1.0, i + j) * matrix_of_minors.matrix[i][j];
    }
  }

  // Free memory for the matrix of minors
  s21_remove_matrix(&matrix_of_minors);

  //   // Transpose the matrix of cofactors to get the adjugate matrix
  //   matrix_t transpose;
  //   flag = s21_create_matrix(A->rows, A->columns, &transpose);
  //   if (flag != OK) {
  //     goto END;
  //   }
  //   for (int i = 0; i < A->rows; i++) {
  //     for (int j = 0; j < A->columns; j++) {
  //       transpose.matrix[j][i] = result->matrix[i][j];
  //     }
  //   }

  //   // Copy the transposed matrix to the result
  //   for (int i = 0; i < A->rows; i++) {
  //     for (int j = 0; j < A->columns; j++) {
  //       result->matrix[i][j] = transpose.matrix[i][j];
  //     }
  //   }

  //   // Free memory for the transposed matrix
  //   s21_remove_matrix(&transpose);

END:
  return flag;
}

// Function to calculate the matrix of minors of a given matrix
int s21_matrix_of_minors(matrix_t* A, matrix_t* result) {
  int flag = OK;  // set initial flag to OK

  // Check if the matrix is square
  if (A->rows != A->columns) {
    flag = ERR_MAT;
    goto END;
  }

  // Create the matrix of minors
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      // Create the submatrix
      matrix_t submatrix;
      s21_create_matrix(A->rows - 1, A->columns - 1, &submatrix);
      for (int m = 0; m < A->rows; m++) {
        if (m == i) {
          continue;
        }
        int k = 0;
        for (int n = 0; n < A->columns; n++) {
          if (n == j) {
            continue;
          }
          submatrix.matrix[m < i ? m : m - 1][k] = A->matrix[m][n];
          k++;
        }
      }
      // Calculate the determinant of the submatrix
      double det = 0.0;
      flag = s21_determinant(&submatrix, &det);
      if (flag != OK) {
        s21_remove_matrix(&submatrix);
        s21_remove_matrix(result);
        goto END;
      }
      // Set the element in the matrix of minors
      result->matrix[i][j] = det;
      // Free memory for the submatrix
      s21_remove_matrix(&submatrix);
    }
  }

END:
  return flag;
}
