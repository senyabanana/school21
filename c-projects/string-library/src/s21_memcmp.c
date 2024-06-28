#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *cmp_str1 = (const unsigned char *)str1;
  const unsigned char *cmp_str2 = (const unsigned char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (cmp_str1[i] != cmp_str2[i]) {
      result = (int)(cmp_str1[i] - cmp_str2[i]);
      break;
    }
  }
  return result;
}