#ifndef _SRC_S21_MATRIX_H_
#define _SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-07  // 0.0000001

enum result_code { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/* Создание матриц */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/* Очистка матриц */
void s21_remove_matrix(matrix_t *A);

/* Сравнение матриц */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/* Сложение матриц */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Вычитание матриц */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Умножение матрицы на число */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/* Умножение двух матриц */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Транспонирование матрицы */
int s21_transpose(matrix_t *A, matrix_t *result);

/* Минор матрицы и матрица алгебраических дополнений */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/* Определитель матрицы */
int s21_determinant(matrix_t *A, double *result);

/* Обратная матрица */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/* Помогаторы */

/* Функция проверяет, является ли матрица валидной для сравнения */
int is_valid(matrix_t *A);

/* Функция сравнивает две матрицы, для определения, имеют ли они одинаковое
 * колличество строк и столбцов */
int is_equal(matrix_t *A, matrix_t *B);

/* Функция получает минор матрицы */
void get_minor(int rows, int columns, matrix_t *A, matrix_t *result);

/* Вспомогательная функция нахождения определителя через рекурсию */
double get_determinant(matrix_t *A);

/* Функция для заполнения матрицы (для тестов) */
void s21_fill(matrix_t *matrix, double value);

#endif