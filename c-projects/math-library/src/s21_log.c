#include "s21_math.h"

long double s21_log(double x) {
  long double res = 0;
  long double z = 0;
  long double term = 0;
  long double current_term = 0;
  int n = 0;
  if (S21_IS_NAN(x) || x < 0 || x == S21_INF_NEG) {
    res = S21_NAN;
  } else if (x == 1) {
    res = S21_POSZERO;
  } else {
    z = (x - 1) / (x + 1);
    current_term = z;
    term = current_term / (2 * n + 1);
    while (s21_fabs((double)current_term) > S21_EPS) {
      res += term;
      current_term *= z * z;
      n++;
      term = current_term / (2 * n + 1);
    }
    res *= 2;
  }
  return res;
}