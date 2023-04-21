#include <assert.h>
#include "s21_matrix.h"


void test_create_and_remove_matrix() {
    int rows = 2;
    int cols = 3;
    matrix_t A;
    int status = s21_create_matrix(rows, cols, &A);
    assert(status == OK);
    assert(A.rows == rows);
    assert(A.columns == cols);
    assert(A.matrix != NULL);

    // test accessing matrix elements
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 2.0;
    A.matrix[0][2] = 3.0;
    A.matrix[1][0] = 4.0;
    A.matrix[1][1] = 5.0;
    A.matrix[1][2] = 6.0;

    // test removing matrix
    s21_remove_matrix(&A);
    assert(A.matrix == NULL);
}
