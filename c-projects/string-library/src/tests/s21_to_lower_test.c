#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_to_lower_1) {
  char str1[] = "SCHOOL";
  ck_assert_str_eq(s21_to_lower(str1), "school");
}
END_TEST

START_TEST(test_to_lower_2) {
  char str2[] = "SCHOOL_21/";
  ck_assert_str_eq(s21_to_lower(str2), "school_21/");
}
END_TEST

START_TEST(test_to_lower_3) {
  char str3[] = "";
  ck_assert_str_eq(s21_to_lower(str3), "");
}
END_TEST

START_TEST(test_to_lower_4) {
  const char *str5 = s21_NULL;
  ck_assert_ptr_null(s21_to_lower(str5));
}
END_TEST

Suite *suite_to_lower(void) {
  Suite *s = suite_create("suite_to_lower");
  TCase *tc = tcase_create("to_lower_tc");

  tcase_add_test(tc, test_to_lower_1);
  tcase_add_test(tc, test_to_lower_2);
  tcase_add_test(tc, test_to_lower_3);
  tcase_add_test(tc, test_to_lower_4);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_to_lower();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}