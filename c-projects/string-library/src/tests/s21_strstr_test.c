#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strstr_1) {
  char haystack[] = "Assassin's Creed";
  char needle[] = "Ass";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_2) {
  char haystack[] = "skipssskipskiiiiiip";
  char needle[] = "skip";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_3) {
  char haystack[] = "1112131415";
  char needle[] = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_4) {
  char haystack[] = "4567";
  char needle[] = "7456745674567";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_5) {
  char haystack[] = "123";
  char needle[] = "123";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_6) {
  char haystack[] = "123";
  char needle[] = "456";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *suite_strstr(void) {
  Suite *s = suite_create("suite_strchr");
  TCase *tc = tcase_create("strchr_tc");
  tcase_add_test(tc, test_strstr_1);
  tcase_add_test(tc, test_strstr_2);
  tcase_add_test(tc, test_strstr_3);
  tcase_add_test(tc, test_strstr_4);
  tcase_add_test(tc, test_strstr_5);
  tcase_add_test(tc, test_strstr_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_strstr();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}