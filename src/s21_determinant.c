#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;  // set initial flag to OK
  double det = 0.0;

  // Check if the matrix is square
  if (A->rows != A->columns) {
    flag = ERR_MAT;
    goto END;
  }

  // Base case: 2x2 matrix
  if (A->rows == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  }
  // Recursive case: use Laplace expansion
  else {
    for (int j = 0; j < A->columns; j++) {
      // Create the submatrix
      matrix_t submatrix;
      s21_create_matrix(A->rows - 1, A->columns - 1, &submatrix);
      for (int i = 1; i < A->rows; i++) {
        int k = 0;
        for (int m = 0; m < A->columns; m++) {
          if (m != j) {
            submatrix.matrix[i - 1][k] = A->matrix[i][m];
            k++;
          }
        }
      }
      // Calculate the cofactor
      double cofactor = 1.0;
      if (j % 2 == 1) {
        cofactor = -1.0;
      }
      // Recursively calculate the determinant of the submatrix
      double subdet = 0.0;
      flag = s21_determinant(&submatrix, &subdet);
      if (flag != OK) {
        s21_remove_matrix(&submatrix);
        goto END;
      }
      // Add the term to the determinant
      det += cofactor * A->matrix[0][j] * subdet;
      // Free memory for the submatrix
      s21_remove_matrix(&submatrix);
    }
  }

  // Set the result
  *result = det;

END:
  return flag;
}
