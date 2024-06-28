#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(trim_1) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(trim_2) {
  const char *src = "   \t   Trim \t Test   \t   ";
  const char *trim_chars = " \t";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Trim \t Test");
  free(result);
}
END_TEST

START_TEST(trim_3) {
  const char *src = "Hello, World!";
  const char *trim_chars = "";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(trim_4) {
  const char *src = "  Hello, World!  ";
  const char *trim_chars = s21_NULL;
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(trim_5) {
  const char *src = NULL;
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_ptr_null(result);
}
END_TEST

Suite *suite_trim(void) {
  Suite *s = suite_create("suite_trim");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, trim_1);
  tcase_add_test(tc, trim_2);
  tcase_add_test(tc, trim_3);
  tcase_add_test(tc, trim_4);
  tcase_add_test(tc, trim_5);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_trim();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}