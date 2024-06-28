#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strrchr_1) {
  char str[] = "Hell World!";
  int c = 'l';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_2) {
  char str[] = "dagi v abu dabi";
  int c = 'd';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_3) {
  char str[] = "testtest";
  int c = 'e';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_4) {
  char str[] = "1234321";
  int c = '3';
  ck_assert_str_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_5) {
  char str[] = "hesoyam";
  int c = 'i';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_6) {
  char str[] = "FireFox";
  int c = '\0';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

Suite *suite_strchr(void) {
  Suite *s = suite_create("suite_strchr");
  TCase *tc = tcase_create("strchr_tc");
  tcase_add_test(tc, test_strrchr_1);
  tcase_add_test(tc, test_strrchr_2);
  tcase_add_test(tc, test_strrchr_3);
  tcase_add_test(tc, test_strrchr_4);
  tcase_add_test(tc, test_strrchr_5);
  tcase_add_test(tc, test_strrchr_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_strchr();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}