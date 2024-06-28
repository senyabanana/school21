#include "s21_math.h"

long double s21_sqrt(double x) {
  long double res = 0;
  if (S21_IS_NAN(x) || x < 0) {
    res = S21_NAN;
  } else if (x == S21_POSZERO) {
    res = S21_POSZERO;
  } else if (x == S21_INF_POS) {
    res = S21_INF_POS;
  } else {
    res = s21_pow(x, 0.5);
  }
  return res;
}