#ifndef SRC_TESTS_S21_MATRIX_H_
#define SRC_TESTS_S21_MATRIX_H_

#include <check.h>
#include <time.h>
#include <unistd.h>

#include "../s21_matrix.h"

#define MAX_DOUBLE 1.79769e+308
#define MIN_DOUBLE 2.22507e-308

Suite *suite_matrix_gather(void);
Suite *suite_create_matrix(void);
Suite *suite_transpose_matrix(void);
Suite *suite_eq_matrix(void);
Suite *suite_sum_matrix(void);
Suite *suite_sub_matrix(void);
Suite *suite_mult_matrix(void);
Suite *suite_mult_number_matrix(void);

Suite *suite_calc_complements(void);
Suite *suite_determinant(void);
Suite *suite_inverse_matrix(void);

void testcases(Suite *testcase);
double get_rand(double min, double max);

#endif // SRC_TESTS_S21_MATRIX_H_