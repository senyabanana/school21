#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memchr_1) {
  const char *str = "Hello, World!";
  void *result_s21 = s21_memchr(str, 'o', strlen(str));
  void *result_std = memchr(str, 'o', strlen(str));
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_memchr_2) {
  const char *str = "";
  void *result_s21 = s21_memchr(str, 'a', strlen(str));
  void *result_std = memchr(str, 'a', strlen(str));
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_memchr_3) {
  const char *str = "aaaaaaa";
  void *result_s21 = s21_memchr(str, 'a', strlen(str));
  void *result_std = memchr(str, 'a', strlen(str));
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_memchr_4) {
  const char *str =
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod "
      "tempor incididunt ut labore et dolore magna aliqua.";
  void *result_s21 = s21_memchr(str, 'u', strlen(str));
  void *result_std = memchr(str, 'u', strlen(str));
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_memchr_5) {
  const char *str = "abcdef";
  void *result_s21 = s21_memchr(str, 'f', strlen(str));
  void *result_std = memchr(str, 'f', strlen(str));
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

START_TEST(test_memchr_6) {
  const char *str = "abcdef";
  void *result_s21 = s21_memchr(str, 'a', 0);
  void *result_std = memchr(str, 'a', 0);
  ck_assert_ptr_eq(result_s21, result_std);
}
END_TEST

Suite *suite_memchr(void) {
  Suite *s = suite_create("suite_memchr");
  TCase *tc = tcase_create("memchr_tc");
  tcase_add_test(tc, test_memchr_1);
  tcase_add_test(tc, test_memchr_2);
  tcase_add_test(tc, test_memchr_3);
  tcase_add_test(tc, test_memchr_4);
  tcase_add_test(tc, test_memchr_5);
  tcase_add_test(tc, test_memchr_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_memchr();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}