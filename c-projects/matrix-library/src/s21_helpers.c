#include "s21_matrix.h"

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

void get_minor(int rows, int columns, matrix_t *A, matrix_t *result) {
  int index_rows = 0, index_columns = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == rows) {
      continue;
    }
    index_columns = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == columns) {
        continue;
      }
      result->matrix[index_rows][index_columns] = A->matrix[i][j];
      index_columns++;
    }
    index_rows++;
  }
}

double get_determinant(matrix_t *A) {
  double res = 0;
  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else {
    matrix_t minor;
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
    for (int i = 0; i < A->columns; i++) {
      get_minor(0, i, A, &minor);
      if (i % 2) {
        res -= A->matrix[0][i] * get_determinant(&minor);
      } else {
        res += A->matrix[0][i] * get_determinant(&minor);
      }
    }
    s21_remove_matrix(&minor);
  }
  return res;
}

void s21_fill(matrix_t *matrix, double value) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = value;
    }
  }
}