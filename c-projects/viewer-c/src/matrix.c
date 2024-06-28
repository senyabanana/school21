#include "matrix.h"

int is_valid(matrix_t *A) {
  int res = 0;
  if (A->rows > 0 && A->columns > 0 && A != NULL && A->matrix != NULL) {
    res = 1;
  }
  return res;
}

int is_equal(matrix_t *A, matrix_t *B) {
  int res = 0;
  if (A->rows == B->rows && A->columns == B->columns) {
    res = 1;
  }
  return res;
}

int create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    double **matrix = (double **)calloc(rows, sizeof(double *));
    double *values = (double *)calloc(rows * columns, sizeof(double));
    for (int i = 0; i < rows; i++) {
      matrix[i] = values + columns * i;
    }
    result->matrix = matrix;
  } else {
    res = INCORRECT_MATRIX;
    result->matrix = NULL;
  }
  return res;
}

void remove_matrix(matrix_t *A) {
  if (A->matrix) {
    if (A->matrix[0]) free(A->matrix[0]);
    free(A->matrix);
    if (A->rows) {
      A->rows = 0;
    }
    if (A->columns) {
      A->columns = 0;
    }
    A->matrix = NULL;
  }
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;
  if (is_valid(A) && is_valid(B) && is_equal(A, B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          res = 0;
        }
      }
    }
  }
  return res;
}

int transpose(matrix_t *A, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (is_valid(A)) {
    res = OK;
    create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (is_valid(A) && is_valid(B)) {
    res = OK;
    create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] =
              result->matrix[i][j] + A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}