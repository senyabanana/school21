#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strncat_1) {
  char str1[20] = "Vertel";
  char str2[555] = " verter";
  ck_assert_str_eq(s21_strncat(str1, str2, 9), strncat(str1, str2, 9));
}
END_TEST

START_TEST(test_strncat_2) {
  char str1[100] = "Privet";
  char str2[555] = " dushnila";
  ck_assert_str_eq(s21_strncat(str1, str2, 55), strncat(str1, str2, 55));
}
END_TEST

START_TEST(test_strncat_3) {
  char str1[] = "777";
  char str2[] = "";
  ck_assert_str_eq(s21_strncat(str1, str2, 0), strncat(str1, str2, 0));
}
END_TEST

START_TEST(test_strncat_4) {
  char str1[] = "qwertyuiopasdfghjkl";
  char str2[555] = "zxcvbnm";
  ck_assert_str_eq(s21_strncat(str1, str2, 10), strncat(str1, str2, 10));
}
END_TEST

START_TEST(test_strncat_5) {
  char str1[] = "\0";
  char str2[] = "abosal";
  ck_assert_str_eq(s21_strncat(str1, str2, 1), strncat(str1, str2, 1));
}
END_TEST

START_TEST(test_strncat_6) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_str_eq(s21_strncat(str1, str2, 0), strncat(str1, str2, 0));
}
END_TEST

Suite *suite_strncat(void) {
  Suite *s = suite_create("suite_strncat");
  TCase *tc = tcase_create("strncat_tc");
  tcase_add_test(tc, test_strncat_1);
  tcase_add_test(tc, test_strncat_2);
  tcase_add_test(tc, test_strncat_3);
  tcase_add_test(tc, test_strncat_4);
  tcase_add_test(tc, test_strncat_5);
  tcase_add_test(tc, test_strncat_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_strncat();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}