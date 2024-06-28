#include "s21_math.h"

long double s21_fabs(double x) {
  long double res = 0;
  if (S21_IS_NAN(x)) {
    res = S21_NAN;
  } else if (x == S21_NEGZERO) {
    res = S21_POSZERO;
  } else if (S21_IS_INF(x)) {
    res = S21_INF_POS;
  } else {
    res = x < 0 ? (long double)(x *= -1) : (long double)x;
  }
  return res;
}