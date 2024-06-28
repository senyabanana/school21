#include "s21_math.h"

long double s21_ceil(double x) {
  long double res = (long long int)x;
  if (S21_IS_INF(x) || S21_IS_NAN(x) || x == S21_POSZERO || x == S21_NEGZERO)
    res = x;
  if (s21_fabs(x) > 0. && x != res) {
    if (x > 0.) {
      res += 1;
    }
  }
  return res;
}