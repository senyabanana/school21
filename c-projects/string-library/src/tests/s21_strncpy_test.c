#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strncpy_1) {
  char str[] = "utka plavaet v ozere";
  char dest[22] = "";
  s21_size_t n = 5;
  ck_assert_str_eq(s21_strncpy(dest, str, n), strncpy(dest, str, n));
}
END_TEST

START_TEST(test_strncpy_2) {
  char str[] = "PingPong \0";
  char dest[15] = "";
  s21_size_t n = 15;
  ck_assert_str_eq(s21_strncpy(dest, str, n), strncpy(dest, str, n));
}
END_TEST

START_TEST(test_strncpy_3) {
  char str[] = " ";
  char dest[2] = "";
  s21_size_t n = 1;
  ck_assert_str_eq(s21_strncpy(dest, str, n), strncpy(dest, str, n));
}
END_TEST

START_TEST(test_strncpy_4) {
  char str[] = " ";
  char dest[12] = "PingPong";
  s21_size_t n = 10;
  ck_assert_str_eq(s21_strncpy(dest, str, n), strncpy(dest, str, n));
}
END_TEST

START_TEST(test_strncpy_5) {
  char str[] = "PingPong";
  char dest[12] = "PingPong";
  s21_size_t n = 10;
  ck_assert_str_eq(s21_strncpy(dest, str, n), strncpy(dest, str, n));
}
END_TEST

START_TEST(test_strncpy_6) {
  char str[] = "    \0";
  char dest[22] = "";
  s21_size_t n = 10;
  ck_assert_str_eq(s21_strncpy(dest, str, n), strncpy(dest, str, n));
}
END_TEST

Suite *suite_strncpy(void) {
  Suite *s = suite_create("suite_strncpy");
  TCase *tc = tcase_create("strncpy_tc");
  tcase_add_test(tc, test_strncpy_1);
  tcase_add_test(tc, test_strncpy_2);
  tcase_add_test(tc, test_strncpy_3);
  tcase_add_test(tc, test_strncpy_4);
  tcase_add_test(tc, test_strncpy_5);
  tcase_add_test(tc, test_strncpy_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_strncpy();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}