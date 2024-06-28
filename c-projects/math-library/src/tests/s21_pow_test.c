#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_math.h"

START_TEST(test_pos_1) {
  double num = 134.5;
  double p = 1.4;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_pos_2) {
  double num = 134.5;
  double p = 20.5e-34;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_neg_pow_1) {
  double num = 563.23;
  double p = -42.;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_neg_num_odd_int_pow) {
  double num = -10.1;
  double p = -3.;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_neg_num_int_pow) {
  double num = -10.1;
  double p = 2.;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_neg_num_fract_pow) {
  double num = -10.1;
  double p = -1.5;
  ck_assert_ldouble_nan(s21_pow(num, p));
}
END_TEST

START_TEST(test_fractional_pow) {
  double num = 10.1;
  double p = 0.123;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_fractional_pow_neg_num) {
  double num = -27.45;
  double p = 1.0 / 3.0;
  ck_assert_ldouble_nan(s21_pow(num, p));
}
END_TEST

START_TEST(test_one_power) {
  double num = 12.34;
  double p = 1;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_zero_pos_pow) {
  double num = 0;
  double p = 12;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}

START_TEST(test_fract_num_pos_inf_pow) {
  double num = 0.123;
  double p = S21_INF_POS;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_num_neg_pos_pow) {
  double num = 13;
  double p = S21_INF_NEG;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_fract_num_pos_pow) {
  double num = S21_NEGZERO;
  double p = 12;
  ck_assert_ldouble_eq(pow(num, p), s21_pow(num, p));
}
END_TEST

START_TEST(test_pos_inf_neg_pow) {
  double num = S21_INF_POS;
  double p = -12;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_neg_inf_pos_pow) {
  double num = S21_INF_NEG;
  double p = -13;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

START_TEST(test_neg_inf_neg_pow) {
  double num = S21_INF_NEG;
  double p = -12;
  ck_assert_ldouble_eq_tol(pow(num, p), s21_pow(num, p), 1e-6);
}
END_TEST

Suite *suite_pow(void) {
  Suite *s = suite_create("suite_pow");
  TCase *tc = tcase_create("pow_tc");

  tcase_add_test(tc, test_pos_1);
  tcase_add_test(tc, test_pos_2);
  tcase_add_test(tc, test_neg_pow_1);
  tcase_add_test(tc, test_neg_num_odd_int_pow);
  tcase_add_test(tc, test_neg_num_int_pow);
  tcase_add_test(tc, test_neg_num_fract_pow);
  tcase_add_test(tc, test_fractional_pow);
  tcase_add_test(tc, test_fractional_pow_neg_num);
  tcase_add_test(tc, test_one_power);
  tcase_add_test(tc, test_zero_pos_pow);
  tcase_add_test(tc, test_fract_num_pos_inf_pow);
  tcase_add_test(tc, test_num_neg_pos_pow);
  tcase_add_test(tc, test_fract_num_pos_pow);
  tcase_add_test(tc, test_pos_inf_neg_pow);
  tcase_add_test(tc, test_neg_inf_pos_pow);
  tcase_add_test(tc, test_neg_inf_neg_pow);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_pow();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}