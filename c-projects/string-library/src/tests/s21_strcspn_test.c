#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strcspn_1) {
  char str1[] = "SalamArturchik";
  char str2[] = "Salam";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_strcspn_2) {
  char str1[] = "Senya Baza";
  char str2[] = "baza";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_strcspn_3) {
  char str1[] = "krasniy kandibober";
  char str2[] = "\0";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_strcspn_4) {
  char str1[] = "ya lomal steklo";
  char str2[] = "//#";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_strcspn_5) {
  char str1[] = "parovozik tr tr tr";
  char str2[] = " ";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_strcspn_6) {
  char str1[] = "0987654321";
  char str2[] = "1";
  ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite *suite_strcspn(void) {
  Suite *s = suite_create("suite_strcspn");
  TCase *tc = tcase_create("strcspn_tc");
  tcase_add_test(tc, test_strcspn_1);
  tcase_add_test(tc, test_strcspn_2);
  tcase_add_test(tc, test_strcspn_3);
  tcase_add_test(tc, test_strcspn_4);
  tcase_add_test(tc, test_strcspn_5);
  tcase_add_test(tc, test_strcspn_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_strcspn();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}