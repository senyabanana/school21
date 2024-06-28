#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *set_str = (unsigned char *)str;
  unsigned char set_c = (unsigned char)c;
  for (s21_size_t i = 0; i < n; i++) {
    set_str[i] = set_c;
  }
  return str;
}