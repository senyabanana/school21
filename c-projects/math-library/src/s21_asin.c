#include "s21_math.h"

long double s21_asin(double x) {
  long double res = 0;
  if (S21_IS_NAN(x) || (x > 1 || x < -1)) {
    res = S21_NAN;
  } else if (x == S21_POSZERO) {
    res = S21_POSZERO;
  } else {
    if (x == 1 || x == -1) {
      res = S21_PI / (2 * x);
    }
    if (x > -1 && x < 1) {
      res = S21_PI_2 - s21_acos(x);
    }
  }
  return res;
}