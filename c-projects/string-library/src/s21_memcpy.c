#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *cpy_dest = (unsigned char *)dest;
  const unsigned char *cpy_src = (const unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    cpy_dest[i] = cpy_src[i];
  }
  return dest;
}