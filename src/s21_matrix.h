#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

#define OK 0       // OK
#define ERR_MAT 1  // Error, incorrect matrix
#define ERR_CAL 2  // Calculation error (memory allocation failed)

// Matrix structure
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

// Matrix creation and removal
int s21_create_matrix(int rows, int columns, matrix_t* result); // done
void s21_remove_matrix(matrix_t* A); // done

// Matrix comparison
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t* A, matrix_t* B); // done

// Matrix addition and subtraction
int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result); // done
int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result); // done

// Matrix multiplication by scalar and matrix multiplication
int s21_mult_number(matrix_t* A, double number, matrix_t* result); // done
int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result); // done

// Matrix transpose
int s21_transpose(matrix_t* A, matrix_t* result); // done

// Matrix of minors and matrix of cofactors
int s21_calc_complements(matrix_t* A, matrix_t* result); // done

// Matrix determinant
int s21_determinant(matrix_t* A, double* result); // done

// Matrix inverse
int s21_inverse_matrix(matrix_t* A, matrix_t* result); // done

#endif /* S21_MATRIX_H */
