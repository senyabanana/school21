#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_math.h"

START_TEST(fmod_test1) {
  double x = 12.0;
  double y = 4.0;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), 1e-6);
}
END_TEST

START_TEST(fmod_test2) {
  double x = 0.0;
  double y = 5.5;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), 1e-6);
}
END_TEST

START_TEST(fmod_test3) {
  double x = S21_INF_POS;
  double y = 5.5;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(fmod_test4) {
  double x = S21_INF_NEG;
  double y = 5.5;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(fmod_test5) {
  double x = 5.8;
  double y = 0.0;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(fmod_test6) {
  double x = 5.8;
  double y = S21_NEGZERO;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(fmod_test7) {
  double x = 5.8;
  double y = S21_INF_POS;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), S21_EPS);
}
END_TEST

START_TEST(fmod_test8) {
  double x = 5.8;
  double y = S21_INF_NEG;
  ck_assert_ldouble_eq_tol(s21_fmod(x, y), fmod(x, y), S21_EPS);
}
END_TEST

START_TEST(fmod_test9) {
  double x = S21_NAN;
  double y = 12.6;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

START_TEST(fmod_test10) {
  double x = 5.5;
  double y = S21_NAN;
  ck_assert_ldouble_nan(s21_fmod(x, y));
}
END_TEST

Suite *suite_fmod(void) {
  Suite *s = suite_create("suite_fmod");
  TCase *tc = tcase_create("fmod_tc");

  tcase_add_test(tc, fmod_test1);
  tcase_add_test(tc, fmod_test2);
  tcase_add_test(tc, fmod_test3);
  tcase_add_test(tc, fmod_test4);
  tcase_add_test(tc, fmod_test5);
  tcase_add_test(tc, fmod_test6);
  tcase_add_test(tc, fmod_test7);
  tcase_add_test(tc, fmod_test8);
  tcase_add_test(tc, fmod_test9);
  tcase_add_test(tc, fmod_test10);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_fmod();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}