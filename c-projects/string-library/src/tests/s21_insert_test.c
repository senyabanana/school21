#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_insert_1) {
  const char *src = "Hello, world!";
  const char *str = "beautiful ";
  s21_size_t start_index = 7;
  void *result = s21_insert(src, str, start_index);

  char *inserted_str = (char *)result;
  ck_assert_str_eq(inserted_str, "Hello, beautiful world!");

  free(inserted_str);
}
END_TEST

START_TEST(test_insert_2) {
  const char *src = "Testing";
  const char *str = "!!!";
  s21_size_t start_index = 20;
  void *result = s21_insert(src, str, start_index);

  free(result);
}
END_TEST

START_TEST(test_insert_3) {
  const char *src = NULL;
  const char *str = "Hello";
  s21_size_t start_index = 0;
  void *result = s21_insert(src, str, start_index);

  free(result);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("Test of s21_string");
  TCase *tc = tcase_create("Core of s21_string");

  tcase_add_test(tc, test_insert_1);
  tcase_add_test(tc, test_insert_2);
  tcase_add_test(tc, test_insert_3);

  suite_add_tcase(s, tc);
  return s;
}

int main() {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suite_insert();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
