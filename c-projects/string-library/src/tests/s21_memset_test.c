#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_memset_1) {
  char dest_s21[50] = "Hello, World!";
  char dest_std[50] = "Hello, World!";
  s21_memset(dest_s21, 'A', 5);
  memset(dest_std, 'A', 5);
  ck_assert_mem_eq(dest_s21, dest_std, 50);
}
END_TEST

START_TEST(test_memset_2) {
  char dest_s21[50] = "";
  char dest_std[50] = "";
  s21_memset(dest_s21, 'B', 5);
  memset(dest_std, 'B', 5);
  ck_assert_mem_eq(dest_s21, dest_std, 50);
}
END_TEST

START_TEST(test_memset_3) {
  char dest_s21[50] = "AAAAAAAAAA";
  char dest_std[50] = "AAAAAAAAAA";
  s21_memset(dest_s21, 'B', 10);
  memset(dest_std, 'B', 10);
  ck_assert_mem_eq(dest_s21, dest_std, 50);
}
END_TEST

START_TEST(test_memset_4) {
  char dest_s21[50] = "Hello, World!";
  char dest_std[50] = "Hello, World!";
  s21_memset(dest_s21, 'Z', 0);
  memset(dest_std, 'Z', (0));
  ck_assert_mem_eq(dest_s21, dest_std, 50);
}
END_TEST

START_TEST(test_memset_5) {
  char dest_s21[1] = "";
  char dest_std[1] = "";
  s21_memset(dest_s21, 'Z', 1);
  memset(dest_std, 'Z', 1);
  ck_assert_mem_eq(dest_s21, dest_std, 1);
}
END_TEST

START_TEST(test_memset_6) {
  char dest_s21[5] = "ABCD";
  char dest_std[5] = "ABCD";
  s21_memset(dest_s21, '\0', 5);
  memset(dest_std, '\0', 5);
  ck_assert_mem_eq(dest_s21, dest_std, 5);
}
END_TEST

Suite *suite_memset(void) {
  Suite *s = suite_create("suite_memset");
  TCase *tc = tcase_create("memset_tc");
  tcase_add_test(tc, test_memset_1);
  tcase_add_test(tc, test_memset_2);
  tcase_add_test(tc, test_memset_3);
  tcase_add_test(tc, test_memset_4);
  tcase_add_test(tc, test_memset_5);
  tcase_add_test(tc, test_memset_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_memset();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
