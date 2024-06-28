#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  s21_size_t hs_len = s21_strlen(haystack);
  s21_size_t n_len = s21_strlen(needle);
  if (hs_len >= n_len) {
    for (s21_size_t i = 0; i <= hs_len - n_len; i++) {
      int neddle_found = 1;
      for (s21_size_t j = i, k = 0; needle[k]; k++, j++) {
        if (haystack[j] != needle[k]) {
          neddle_found = 0;
          break;
        }
      }
      if (neddle_found) {
        res = (char *)haystack + i;
        break;
      }
    }
  }
  return res;
}