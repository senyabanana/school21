#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_strncmp_1) {
  char str1[] = "ya kalendar";
  char str2[] = "ya kalendar";
  ck_assert_int_eq(s21_strncmp(str1, str2, 12) == 0,
                   strncmp(str1, str2, 12) == 0);
}
END_TEST

// START_TEST(test_strncmp_2) {
//   char str1[] = "ya kalendar perevernu";
//   char str2[] = "ya kalendar";
//   ck_assert_int_eq(s21_strncmp(str1, str2, 15) > 0,
//                    strncmp(str1, str2, 15) > 0);
// }
// END_TEST

START_TEST(test_strncmp_3) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, 1) == 0,
                   strncmp(str1, str2, 1) == 0);
}
END_TEST

START_TEST(test_strncmp_4) {
  char str1[] = "abosal";
  char str2[] = "abossal";
  ck_assert_int_eq(s21_strncmp(str1, str2, 7) < 0, strncmp(str1, str2, 7) < 0);
}
END_TEST

// START_TEST(test_strncmp_5) {
//   char str1[] = "\0";
//   char str2[] = "123456";
//   ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
// }
// END_TEST

START_TEST(test_strncmp_6) {
  char str1[] = "chi55ks123";
  char str2[] = "chi55ks124";
  ck_assert_int_eq(s21_strncmp(str1, str2, 11), strncmp(str1, str2, 11));
}
END_TEST

Suite *suite_strncmp(void) {
  Suite *s = suite_create("suite_strncmp");
  TCase *tc = tcase_create("strncmp_tc");
  tcase_add_test(tc, test_strncmp_1);
  // tcase_add_test(tc, test_strncmp_2);
  tcase_add_test(tc, test_strncmp_3);
  tcase_add_test(tc, test_strncmp_4);
  // tcase_add_test(tc, test_strncmp_5);
  tcase_add_test(tc, test_strncmp_6);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_strncmp();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}