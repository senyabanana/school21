#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_to_upper_1) {
  char str1[] = "school";
  ck_assert_str_eq(s21_to_upper(str1), "SCHOOL");
}
END_TEST

START_TEST(test_to_upper_2) {
  char str2[] = "school_21/";
  ck_assert_str_eq(s21_to_upper(str2), "SCHOOL_21/");
}
END_TEST

START_TEST(test_to_upper_3) {
  char str3[] = "";
  ck_assert_str_eq(s21_to_upper(str3), "");
}
END_TEST

START_TEST(test_to_upper_4) {
  char str4[] = "12345";
  ck_assert_str_eq(s21_to_upper(str4), "12345");
}
END_TEST

START_TEST(test_to_upper_5) {
  char str5[] = "aBcDeFgH";
  ck_assert_str_eq(s21_to_upper(str5), "ABCDEFGH");
}
END_TEST

START_TEST(test_to_upper_6) {
  char str6[] = "Hello World!";
  ck_assert_str_eq(s21_to_upper(str6), "HELLO WORLD!");
}
END_TEST

START_TEST(test_to_upper_7) {
  const char *str7 = NULL;
  ck_assert_ptr_null(s21_to_upper(str7));
}
END_TEST

Suite *suite_to_upper(void) {
  Suite *s = suite_create("suite_to_upper");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, test_to_upper_1);
  tcase_add_test(tc, test_to_upper_2);
  tcase_add_test(tc, test_to_upper_3);
  tcase_add_test(tc, test_to_upper_4);
  tcase_add_test(tc, test_to_upper_5);
  tcase_add_test(tc, test_to_upper_6);
  tcase_add_test(tc, test_to_upper_7);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_to_upper();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
