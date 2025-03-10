#include "s21_math.h"

long double s21_acos(double x) {
  long double res = S21_NAN;
  if (S21_IS_NAN(x) || S21_IS_INF(x)) {
    res = S21_NAN;
  } else {
    if (x < 1 && x >= 0) {
      res = s21_atan(s21_sqrt(1 - x * x) / x);
    }
    if (x < 0 && x > -1) {
      res = S21_PI + s21_atan(s21_sqrt(1 - x * x) / x);
    }
    if (x == 1) {
      res = 0;
    }
    if (x == -1) {
      res = S21_PI;
    }
  }
  return res;
}