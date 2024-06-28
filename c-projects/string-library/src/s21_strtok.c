#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last;

  char *token;
  char *ref;
  int is_initialized = 1;

  if ((ref = str) == s21_NULL && (ref = last) == s21_NULL) {
    is_initialized = 0;
  }

  for (int i = 0; is_initialized && *ref && delim[i]; i++) {
    if (*ref == delim[i]) {
      ref++;
      i = -1;
    }
  }

  if (is_initialized && *ref == '\0') {
    ref = s21_NULL;
    last = s21_NULL;
    is_initialized = 0;
  }
  token = ref;

  while (is_initialized && *ref) {
    for (size_t i = 0; delim[i]; i++) {
      if (*ref == delim[i]) {
        is_initialized = 0;
        *ref = '\0';
        ref++;
        if (*ref == '\0') {
          ref = s21_NULL;
        }
        last = ref;
        break;
      }
    }

    if (is_initialized) {
      ref++;

      if (*ref == '\0') {
        last = s21_NULL;
      }
    }
  }

  return token;
}