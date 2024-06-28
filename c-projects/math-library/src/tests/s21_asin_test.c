#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_math.h"

START_TEST(test_asin_positive) {
  double x = 0.4;
  ck_assert_ldouble_eq_tol(asin(x), s21_asin(x), 1e-6);
}
END_TEST

START_TEST(test_asin_negative) {
  double x = -0.4;
  ck_assert_ldouble_eq_tol(asin(x), s21_asin(x), 1e-6);
}
END_TEST

START_TEST(test_asin_zero) {
  double x = S21_POSZERO;
  ck_assert_ldouble_eq_tol(asin(x), s21_asin(x), 1e-6);
}
END_TEST

START_TEST(test_asin_one_negative) {
  double x = -1;
  ck_assert_ldouble_eq_tol(asin(x), s21_asin(x), 1e-6);
}
END_TEST

START_TEST(test_asin_huge_positive) {
  double x = 5;
  ck_assert_ldouble_nan(s21_asin(x));
}
END_TEST

START_TEST(test_asin_huge_negative) {
  double x = -5;
  ck_assert_ldouble_nan(s21_asin(x));
}
END_TEST

START_TEST(test_asin_big_mantissa) {
  double x = 0.123456789012345678901234567890;
  ck_assert_ldouble_eq_tol(asin(x), s21_asin(x), 1e-6);
}
END_TEST

START_TEST(test_eps_positive) {
  double x = 1 + S21_EPS;
  ck_assert_ldouble_eq_tol(asin(x), s21_asin(x), 1e-6);
}
END_TEST

START_TEST(test_eps_negative) {
  double x = -1 - S21_EPS;
  ck_assert_ldouble_eq_tol(asin(x), s21_asin(x), 1e-6);
}
END_TEST

START_TEST(test_asin_nan) {
  double x = S21_NAN;
  ck_assert_ldouble_nan(s21_asin(x));
}
END_TEST

START_TEST(test_asin_inf) {
  double x = S21_INF_POS;
  ck_assert_ldouble_nan(s21_asin(x));
}
END_TEST

Suite *suite_asin(void) {
  Suite *s = suite_create("suite_asin");
  TCase *tc = tcase_create("asin_tc");

  tcase_add_test(tc, test_asin_positive);
  tcase_add_test(tc, test_asin_negative);
  tcase_add_test(tc, test_asin_zero);
  tcase_add_test(tc, test_asin_negative);
  tcase_add_test(tc, test_asin_one_negative);
  tcase_add_test(tc, test_asin_huge_positive);
  tcase_add_test(tc, test_asin_huge_negative);
  tcase_add_test(tc, test_asin_big_mantissa);
  tcase_add_test(tc, test_eps_positive);
  tcase_add_test(tc, test_eps_negative);
  tcase_add_test(tc, test_asin_nan);
  tcase_add_test(tc, test_asin_inf);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_asin();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}