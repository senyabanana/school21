#include "s21_math.h"

long double s21_floor(double x) {
  long double res = (long long int)x;
  if (S21_IS_INF(x) || S21_IS_NAN(x) || x == S21_POSZERO || x == S21_NEGZERO) {
    res = x;
  } else {
    if (s21_fabs(x - res) > 0. && s21_fabs(x) > 0.) {
      if (x < 0.) {
        res -= 1;
      }
    }
  }
  return res;
}