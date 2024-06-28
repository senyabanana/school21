#include "s21_math.h"

long double s21_atan(double x) {
  long double res = 0;
  if (S21_IS_NAN(x)) {
    res = S21_NAN;
  } else if (x == S21_POSZERO) {
    res = S21_POSZERO;
  } else if (x == S21_INF_POS) {
    res = S21_PI_2;
  } else if (x == S21_INF_NEG) {
    res = -S21_PI_2;
  } else if (x == -1) {
    res = -S21_PI_4;
  } else {
    if (res == 0) {
      if (x > -1. && x < 1.) {
        for (int i = 0; i < 2000; i++) {
          res += s21_pow(-1, i) * s21_pow(x, 1 + (2 * i)) / (1 + 2 * i);
        }
      } else {
        for (int i = 0; i < 2000; i++) {
          res += s21_pow(-1, i) * s21_pow(x, -(1 + (2 * i))) / (1 + 2 * i);
        }
        res = S21_PI * s21_sqrt(x * x) / (2 * x) - res;
      }
    }
  }
  return res;
}