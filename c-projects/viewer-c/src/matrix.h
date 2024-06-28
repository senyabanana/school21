#ifndef _SRC_MATRIX_H_
#define _SRC_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum result_code { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int is_valid(matrix_t *A);
int is_equal(matrix_t *A, matrix_t *B);
int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int transpose(matrix_t *A, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

#endif