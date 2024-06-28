#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL || str == s21_NULL || s21_strlen(src) < start_index) {
    return s21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  char *result = (char *)calloc(src_len + str_len + 1, sizeof(char));

  s21_strncpy(result, (char *)src, start_index);
  s21_strncat(result, str, str_len);
  s21_strncat(result, &src[start_index], src_len - start_index);

  return (void *)result;
}