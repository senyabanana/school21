#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  unsigned char chr_c = (unsigned char)c;
  char *result = s21_NULL;
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == chr_c) {
      result = (char *)(str + i);
    }
    i++;
  }
  if (chr_c == '\0') {
    result = (char *)(str + i);
  }
  return result;
}
