#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strpbrk_1) {
  char str1[] = "Phantom Assasin";
  char str2[] = "Ass";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_2) {
  char str1[] = "Need For Speed";
  char str2[] = "For";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_3) {
  char str1[] = "Fruit-tella";
  char str2[] = "";
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str1, str2),
                    (unsigned long)strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_4) {
  char str1[] = "salam verter";
  char str2[] = "v";
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str1, str2),
                    (unsigned long)strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_5) {
  char str1[] = "123454321";
  char str2[] = "531";
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str1, str2),
                    (unsigned long)strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_6) {
  char str1[] = "123454321";
  char str2[] = "\0";
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str1, str2),
                    (unsigned long)strpbrk(str1, str2));
}
END_TEST

Suite *suite_strpbrk(void) {
  Suite *s = suite_create("suite_strpbrk");
  TCase *tc = tcase_create("strpbrk_tc");
  tcase_add_test(tc, test_strpbrk_1);
  tcase_add_test(tc, test_strpbrk_2);
  tcase_add_test(tc, test_strpbrk_3);
  tcase_add_test(tc, test_strpbrk_4);
  tcase_add_test(tc, test_strpbrk_5);
  tcase_add_test(tc, test_strpbrk_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_strpbrk();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}