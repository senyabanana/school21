#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *chr_str = (const unsigned char *)str;
  const unsigned char chr_c = (const unsigned char)c;
  void *result = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (chr_str[i] == chr_c) {
      result = (void *)(chr_str + i);
      break;
    }
  }
  return result;
}