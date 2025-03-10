#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_math.h"

START_TEST(sqrt_test2) {
  double x = 1;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test5) {
  double x = 0.123456;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test7) {
  double x = 0.0;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test8) {
  double x = S21_NEGZERO;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test27) {
  double x = 987565.9874641213656;
  ck_assert_ldouble_eq_tol(s21_sqrt(x), sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test36) {
  double x = S21_PI / 3;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test37) {
  double x = S21_PI / 6;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test42) {
  double x = S21_PI / 2;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test43) {
  double x = 2 * S21_PI / 3;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test44) {
  double x = 5 * S21_PI / 6;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test45) {
  double x = S21_PI;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(sqrt_test41) {
  double x = -1.234567;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

START_TEST(test_pos_int_1) {
  double x = 64.;
  ck_assert_ldouble_eq_tol(sqrt(x), s21_sqrt(x), 1e-6);
}
END_TEST

START_TEST(test_neg_int) {
  double x = -121.;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

START_TEST(test_neg_real) {
  double x = -2.89;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

START_TEST(test_nan) {
  double x = S21_NAN;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

START_TEST(test_pos_inf) {
  double x = S21_INF_POS;
  ck_assert_ldouble_eq(sqrt(x), s21_sqrt(x));
}
END_TEST

START_TEST(test_neg_inf) {
  double x = S21_INF_NEG;
  ck_assert_ldouble_nan(s21_sqrt(x));
}
END_TEST

Suite *suite_sqrt(void) {
  Suite *s = suite_create("suite_sqrt");
  TCase *tc = tcase_create("sqrt_tc");

  tcase_add_test(tc, sqrt_test2);
  tcase_add_test(tc, sqrt_test5);
  tcase_add_test(tc, sqrt_test7);
  tcase_add_test(tc, sqrt_test8);
  tcase_add_test(tc, sqrt_test27);
  tcase_add_test(tc, sqrt_test36);
  tcase_add_test(tc, sqrt_test37);
  tcase_add_test(tc, sqrt_test41);
  tcase_add_test(tc, sqrt_test42);
  tcase_add_test(tc, sqrt_test43);
  tcase_add_test(tc, sqrt_test44);
  tcase_add_test(tc, sqrt_test45);
  tcase_add_test(tc, test_pos_int_1);
  tcase_add_test(tc, test_neg_int);
  tcase_add_test(tc, test_neg_real);
  tcase_add_test(tc, test_nan);
  tcase_add_test(tc, test_pos_inf);
  tcase_add_test(tc, test_neg_inf);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_sqrt();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}