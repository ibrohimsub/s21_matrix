#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (s21_matrix_not_NULL(A)) {
    double det;

    s21_determinant(A, &det);

    if (det != 0) {
      matrix_t tmp_calc;

      flag = s21_calc_complements(A, &tmp_calc);

      if (flag == OK) {
        matrix_t tmp_trans;

        flag = s21_transpose(&tmp_calc, &tmp_trans);
        if (flag == OK) {
          s21_mult_number(&tmp_trans, 1 / det, result);
        }
        s21_remove_matrix(&tmp_trans);
      }
      s21_remove_matrix(&tmp_calc);
    } else {
      flag = ERR_CAL;
    }
  } else {
    flag = ERR_MAT;
  }

  return flag;
}