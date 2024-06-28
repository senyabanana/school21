#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
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

void s21_remove_matrix(matrix_t *A) {
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

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (is_valid(A) && is_valid(B) && is_equal(A, B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (is_valid(A) && is_valid(B)) {
    res = OK;
    if (is_equal(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      res = CALCULATION_ERROR;
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (is_valid(A) && is_valid(B)) {
    res = OK;
    if (is_equal(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      res = CALCULATION_ERROR;
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (is_valid(A)) {
    res = OK;
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (is_valid(A) && is_valid(B)) {
    res = OK;
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] =
                result->matrix[i][j] + A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      res = CALCULATION_ERROR;
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = INCORRECT_MATRIX;
  if (is_valid(A)) {
    res = OK;
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_valid(A)) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor;
          double determinant = 0;
          s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
          get_minor(i, j, A, &minor);
          s21_determinant(&minor, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&minor);
        }
      }
    } else {
      res = CALCULATION_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (is_valid(A)) {
    if (A->rows == A->columns) {
      *result = get_determinant(A);
    } else {
      res = CALCULATION_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_valid(A)) {
    if (A->rows == A->columns) {
      double determinant = 0;
      s21_determinant(A, &determinant);
      if (determinant != 0 && fabs(determinant) > EPS) {
        matrix_t temp1, temp2;
        s21_calc_complements(A, &temp1);
        s21_transpose(&temp1, &temp2);
        s21_mult_number(&temp2, 1. / determinant, result);
        s21_remove_matrix(&temp1);
        s21_remove_matrix(&temp2);
      } else {
        res = CALCULATION_ERROR;
      }
    } else {
      res = CALCULATION_ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}