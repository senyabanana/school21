#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  s21_size_t i;
  for (i = 0; str1[i] != '\0'; i++) {
    if (s21_strchr(str2, str1[i])) {
      res = (char *)(str1 + i);
      break;
    }
  }
  return res;
}