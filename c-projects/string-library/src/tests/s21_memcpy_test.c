#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memcpy_1) {
  const char *src = "This is a test!";
  char dest_s21[50];
  char dest_std[50];
  s21_memcpy(dest_s21, src, 16);
  memcpy(dest_std, src, 16);
  ck_assert_mem_eq(dest_s21, dest_std, 16);
}
END_TEST

START_TEST(test_memcpy_2) {
  const char *src = "a";
  char dest_s21[2];
  char dest_std[2];
  s21_memcpy(dest_s21, src, 2);
  memcpy(dest_std, src, 2);
  ck_assert_mem_eq(dest_s21, dest_std, 2);
}
END_TEST

START_TEST(test_memcpy_3) {
  const char *src = "bbb";
  char dest_s21[10];
  char dest_std[10];
  s21_memcpy(dest_s21, src, 4);
  memcpy(dest_std, src, 4);
  ck_assert_mem_eq(dest_s21, dest_std, 4);
}
END_TEST

START_TEST(test_memcpy_4) {
  const char *src = "Programming in C is fun!";
  char dest_s21[30];
  char dest_std[30];
  s21_memcpy(dest_s21, src, 26);
  memcpy(dest_std, src, 26);
  ck_assert_mem_eq(dest_s21, dest_std, 26);
}
END_TEST

START_TEST(test_memcpy_5) {
  const char *src = "Check is a unit testing library for C.";
  char dest_s21[50];
  char dest_std[50];
  s21_memcpy(dest_s21, src, 41);
  memcpy(dest_std, src, 41);
  ck_assert_mem_eq(dest_s21, dest_std, 41);
}
END_TEST

START_TEST(test_memcpy_6) {
  const char *src = "C";
  char dest_s21[1];
  char dest_std[1];
  s21_memcpy(dest_s21, src, 1);
  memcpy(dest_std, src, 1);
  ck_assert_mem_eq(dest_s21, dest_std, 1);
}
END_TEST

Suite *suite_memcpy(void) {
  Suite *s = suite_create("suite_memcpy");
  TCase *tc = tcase_create("memcpy_tc");
  tcase_add_test(tc, test_memcpy_1);
  tcase_add_test(tc, test_memcpy_2);
  tcase_add_test(tc, test_memcpy_3);
  tcase_add_test(tc, test_memcpy_4);
  tcase_add_test(tc, test_memcpy_5);
  tcase_add_test(tc, test_memcpy_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_memcpy();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}