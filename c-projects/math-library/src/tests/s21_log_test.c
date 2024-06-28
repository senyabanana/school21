#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_math.h"

START_TEST(test_pos) {
  double x = 2.523;
  ck_assert_ldouble_eq_tol(log(x), s21_log(x), 1e-6);
}
START_TEST(test_neg) {
  double x = -3432.12;
  ck_assert_ldouble_nan(s21_log(x));
}

START_TEST(test_one) {
  double x = 1;
  ck_assert_ldouble_eq_tol(log(x), s21_log(x), 1e-6);
}

START_TEST(test_nan_pos) {
  double x = S21_NAN;
  ck_assert_ldouble_nan(s21_log(x));
}

START_TEST(test_nan_neg) {
  double x = -S21_NAN;
  ck_assert_ldouble_nan(s21_log(x));
}

START_TEST(test_inf_neg) {
  double x = S21_INF_NEG;
  ck_assert_ldouble_nan(s21_log(x));
}

Suite *suite_log(void) {
  Suite *s = suite_create("suite_log");
  TCase *tc = tcase_create("log_tc");

  tcase_add_test(tc, test_pos);
  tcase_add_test(tc, test_neg);
  tcase_add_test(tc, test_one);
  tcase_add_test(tc, test_nan_pos);
  tcase_add_test(tc, test_nan_neg);
  tcase_add_test(tc, test_inf_neg);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_log();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}