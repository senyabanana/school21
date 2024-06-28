#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res = 0;
  if (S21_IS_NAN(x) || S21_IS_NAN(y) || S21_IS_INF(x) || y == 0) {
    res = S21_NAN;
  } else if (S21_IS_INF(y)) {
    res = x;
  } else if (x == S21_POSZERO && y != 0) {
    res = S21_POSZERO;
  } else {
    if (x < 0 || y < 0) {
      res = -s21_abs(x / y);
    } else {
      res = s21_abs(x / y);
    }
    res = x - res * y;
  }
  return res;
}