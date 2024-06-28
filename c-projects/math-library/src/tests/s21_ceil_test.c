#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_math.h"

START_TEST(ceil_test1) {
  double x = 1.0;
  ck_assert_ldouble_eq_tol(s21_ceil(x), ceil(x), 6);
}
END_TEST

START_TEST(ceil_test2) {
  double x = 0.0;
  ck_assert_ldouble_eq_tol(s21_ceil(x), ceil(x), 6);
}
END_TEST

START_TEST(ceil_test3) {
  double x = S21_NEGZERO;
  ck_assert_ldouble_eq_tol(s21_ceil(x), ceil(x), 6);
}
END_TEST

START_TEST(ceil_test4) {
  double x = S21_INF_POS;
  ck_assert_ldouble_eq(s21_ceil(x), ceil(x));
}
END_TEST

START_TEST(ceil_test5) {
  double x = S21_INF_NEG;
  ck_assert_ldouble_eq(s21_ceil(x), ceil(x));
}
END_TEST

START_TEST(ceil_test6) {
  double x = S21_NAN;
  ck_assert_ldouble_nan(s21_ceil(x));
}
END_TEST

START_TEST(ceil_test7) {
  double x = 4.7;
  ck_assert_ldouble_eq_tol(s21_ceil(x), ceil(x), 6);
}
END_TEST

START_TEST(test_nan) {
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
  ck_assert_ldouble_nan(ceil(S21_NAN));
}
END_TEST

START_TEST(test_y_zero) { ck_assert_ldouble_eq(s21_ceil(0), ceil(0)); }
END_TEST

START_TEST(test_x_inf_y_zero) {
  double x = 8743517471375471154.34143134134134;
  ck_assert_ldouble_eq(s21_ceil(x), ceil(x));
}

START_TEST(test_x_inf_y_zero1) {
  double x = -8743517471375471154.34143134134134;
  ck_assert_ldouble_eq(s21_ceil(x), ceil(x));
}

START_TEST(test_zero) { ck_assert_ldouble_eq(ceil(0), s21_ceil(0)); }
END_TEST

START_TEST(test_neg) { ck_assert_ldouble_eq(ceil(-1234), s21_ceil(-1234)); }
END_TEST

START_TEST(test_pos) { ck_assert_ldouble_eq(ceil(1234), s21_ceil(1234)); }
END_TEST

START_TEST(test_pos_1) { ck_assert_ldouble_eq(ceil(1), s21_ceil(1)); }
END_TEST

START_TEST(test_normal) { ck_assert_ldouble_eq(ceil(1.7), s21_ceil(1.7)); }
END_TEST

START_TEST(test_normal_negative) {
  ck_assert_int_eq(ceil(-1.7), s21_ceil(-1.7));
}
END_TEST

START_TEST(test_normal_above_1) {
  ck_assert_ldouble_eq(ceil(14.7), s21_ceil(14.7));
}
END_TEST
START_TEST(test_lesser_than_1) {
  ck_assert_ldouble_eq(ceil(0.7), s21_ceil(0.7));
}
END_TEST
START_TEST(test_positive_inf) {
  ck_assert_ldouble_eq(ceil(S21_INF_POS), s21_ceil(S21_INF_POS));
}
END_TEST
START_TEST(test_negative_inf) {
  ck_assert_ldouble_eq(ceil(S21_INF_NEG), s21_ceil(S21_INF_NEG));
}
END_TEST

START_TEST(test_tolerance_pos) {
  double a = 0.1;
  int i = _i;
  ck_assert_ldouble_eq_tol(ceil(a * i), s21_ceil(a * i), S21_EPS);
}
END_TEST

START_TEST(test_tolerance_neg) {
  double a = 0.1;
  int i = _i;
  ck_assert_ldouble_eq_tol(ceil(-a * i), s21_ceil(-a * i), S21_EPS);
}

Suite *suite_ceil(void) {
  Suite *s = suite_create("suite_ceil");
  TCase *tc = tcase_create("ceil_tc");

  tcase_add_test(tc, ceil_test1);
  tcase_add_test(tc, ceil_test2);
  tcase_add_test(tc, ceil_test3);
  tcase_add_test(tc, ceil_test4);
  tcase_add_test(tc, ceil_test5);
  tcase_add_test(tc, ceil_test6);
  tcase_add_test(tc, ceil_test7);
  tcase_add_test(tc, test_nan);
  tcase_add_test(tc, test_y_zero);
  tcase_add_test(tc, test_x_inf_y_zero);
  tcase_add_test(tc, test_x_inf_y_zero1);
  tcase_add_test(tc, test_zero);
  tcase_add_test(tc, test_neg);
  tcase_add_test(tc, test_pos);
  tcase_add_test(tc, test_pos_1);
  tcase_add_test(tc, test_normal);
  tcase_add_test(tc, test_normal_negative);
  tcase_add_test(tc, test_normal_above_1);
  tcase_add_test(tc, test_negative_inf);
  tcase_add_test(tc, test_lesser_than_1);
  tcase_add_test(tc, test_positive_inf);
  tcase_add_loop_test(tc, test_tolerance_pos, 0, 100);
  tcase_add_loop_test(tc, test_tolerance_neg, 0, 100);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_ceil();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}