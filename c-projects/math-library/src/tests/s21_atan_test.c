#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_math.h"

START_TEST(test_atan_positive) {
  double x = 0.4;
  ck_assert_ldouble_eq_tol(atan(x), s21_atan(x), 1e-6);
}
END_TEST

START_TEST(test_atan_negative) {
  double x = -0.4;
  ck_assert_ldouble_eq_tol(atan(x), s21_atan(x), 1e-6);
}
END_TEST

START_TEST(test_atan_zero) {
  double x = 0;
  ck_assert_ldouble_eq_tol(atan(x), s21_atan(x), 1e-6);
}
END_TEST

START_TEST(test_atan_one) {
  double x = -0.0;
  ck_assert_ldouble_eq_tol(atan(x), s21_atan(x), 1e-6);
}
END_TEST

START_TEST(test_atan_one_negative) {
  double x = -1;
  ck_assert_ldouble_eq_tol(atan(x), s21_atan(x), 1e-6);
}
END_TEST

START_TEST(test_atan_nan) {
  double x = S21_NAN;
  ck_assert_ldouble_nan(s21_atan(x));
}
END_TEST

START_TEST(test_atan_inf) {
  double x = S21_INF_POS;
  ck_assert_ldouble_eq_tol(atan(x), s21_atan(x), 1e-6);
}
END_TEST

START_TEST(test_atan_neg_inf) {
  double x = S21_INF_NEG;
  ck_assert_ldouble_eq_tol(atan(x), s21_atan(x), 1e-6);
}
END_TEST

Suite *suite_atan(void) {
  Suite *s = suite_create("suite_atan");
  TCase *tc = tcase_create("atan_tc");

  tcase_add_test(tc, test_atan_positive);
  tcase_add_test(tc, test_atan_negative);
  tcase_add_test(tc, test_atan_zero);
  tcase_add_test(tc, test_atan_one);
  tcase_add_test(tc, test_atan_negative);
  tcase_add_test(tc, test_atan_one_negative);
  tcase_add_test(tc, test_atan_nan);
  tcase_add_test(tc, test_atan_inf);
  tcase_add_test(tc, test_atan_neg_inf);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_atan();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}