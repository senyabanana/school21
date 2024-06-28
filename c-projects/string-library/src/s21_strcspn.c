#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  while (str1[i] != '\0') {
    s21_size_t j = 0;
    while (str2[j] != '\0' && str2[j] != str1[i]) {
      j++;
    }
    if (str2[j] == '\0') {
      i++;
    } else {
      break;
    }
  }
  return i;
}
