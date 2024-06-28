#ifndef SRC_S21_MATH_H
#define SRC_S21_MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define S21_PI 3.141592653589793    // pi
#define S21_PI_2 1.570796326794896  // pi/2
#define S21_PI_4 0.785398163397448  // pi/4
#define S21_E 2.718281828459045     // e
#define S21_EPS 1e-17               // epsilon
#define S21_NAN 0.0 / 0.0
#define S21_POSZERO 0.0
#define S21_NEGZERO -0.0
#define S21_INF_POS +1.0 / 0.0
#define S21_INF_NEG -1.0 / 0.0
#define S21_IS_NAN(x) (x != x)
#define S21_IS_INF(x) (x == S21_INF_POS || x == S21_INF_NEG)

// 1) вычисляет абслолютное значение целого числа
int s21_abs(int x);

// 2) вычисляет арккосинус
long double s21_acos(double x);

// 3) вычисляет арксинус
long double s21_asin(double x);

// 4) вычисляет арктангенс
long double s21_atan(double x);

// 5) возвращает ближайшее целое число, не меньшее заданного значения
long double s21_ceil(double x);

// 6) вычисляет косинус
long double s21_cos(double x);

// 7) возвращает значение e, возведенное в заданную степень
long double s21_exp(double x);

// 8) вычисляет абсолютное значение числа с плавающей точкой
long double s21_fabs(double x);

// 9) возвращает ближайщее целое число, не превышающее заданного значения
long double s21_floor(double x);

// 10) остаток операции деления с плавающей точкой
long double s21_fmod(double x, double y);

// 11) вычисляет натуральный логарифм
long double s21_log(double x);

// 12) возводит число в заданную степень
long double s21_pow(double base, double exp);

// 13) вычисляет синус
long double s21_sin(double x);

// 14) вычисляет квадратный корень
long double s21_sqrt(double x);

// 15) вычисляет тангенс
long double s21_tan(double x);

#endif