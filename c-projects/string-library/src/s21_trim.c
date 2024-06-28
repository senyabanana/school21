#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *trim_src = (char *)src;  // Приведение указателя на src к типу `char *`
  char *trim_chars_minor =
      (char *)trim_chars;  // Приведение указателя на trim_chars к типу `char *`
  char *arr;  // Объявление указателя на char
  int error = 1;  // Инициализация переменной error значением 1

  if (trim_chars_minor ==
      s21_NULL) {  // Проверка, если trim_chars_minor равно NULL
    trim_chars = " ";  // Присвоение trim_chars значения " "
    trim_chars_minor = (char *)
        trim_chars;  // Приведение указателя на trim_chars к типу `char *`
  }

  if (trim_src == s21_NULL) {  // Проверка, если trim_src равно NULL
    error = 0;  // Присвоение переменной error значения 0
  }

  if (error) {  // Проверка, если error равно 1
    s21_size_t src_len = s21_strlen(src);  // Вычисление длины строки src
    s21_size_t trim_chars_len =
        s21_strlen(trim_chars);  // Вычисление длины строки trim_chars
    arr = (char *)malloc((src_len + 1) *
                         sizeof(char));  // Выделение памяти для массива arr
    int arr_i = 0;  // Инициализация переменной arr_i значением 0
    int st_i = s21_start_i(trim_src, trim_chars_minor, src_len,
                           trim_chars_len);  // Вызов функции s21_start_i
    int en_i = s21_end_i(trim_src, trim_chars_minor, src_len,
                         trim_chars_len);  // Вызов функции s21_end_i
    for (int i = st_i; i < en_i; i++) {    // Цикл от st_i до en_i
      arr[arr_i] = src[i];  // Присвоение элемента массива src[i] элементу
                            // массива arr[arr_i]
      arr_i++;  // Увеличение значения переменной arr_i на 1
    }
    arr[arr_i] = '\0';  // Установка завершающего символа '\0' для массива arr
  }
  return error == 0 ? s21_NULL
                    : (char *)arr;  // Возврат s21_NULL, если error равно 0,
                                    // иначе возврат указателя на arr
}

// Функция для определения индекса начала обрезки
int s21_start_i(const char *trim_src, const char *trim_chars_minor,
                s21_size_t src_len, s21_size_t trim_chars_len) {
  int start_i = 0;  // Инициализация переменной start_i значением 0
  for (s21_size_t i = 0; i < src_len; i++) {  // Цикл от 0 до src_len
    int flag1 = 0;  // Инициализация переменной flag1 значением 0
    for (s21_size_t j = 0; j < trim_chars_len;
         j++) {  // Вложенный цикл от 0 до trim_chars_len
      if (trim_src[i] == trim_chars_minor[j]) {  // Проверка, если trim_src[i]
                                                 // равно trim_chars_minor[j]
        flag1 = 1;  // Установка flag1 в 1, если trim_src[i] равно
                    // trim_chars_minor[j]
        break;  // Выход из вложенного цикла
      }
    }
    if (flag1 == 1) {  // Проверка, если flag1 равно 1
      start_i++;  // Увеличение значения переменной start_i на 1
    } else {
      break;  // Выход из цикла
    }
  }
  return start_i;  // Возврат значения переменной start_i
}

// Функция для определения индекса конца обрезки
int s21_end_i(const char *trim_src, const char *trim_chars_minor,
              s21_size_t src_len, s21_size_t trim_chars_len) {
  int end_i = src_len;  // Инициализация переменной end_i значением src_len
  for (int i = src_len - 1; i > -1; i--) {  // Цикл от src_len - 1 до -1
    int flag2 = 0;  // Инициализация переменной flag2 значением 0
    for (s21_size_t j = 0; j < trim_chars_len;
         j++) {  // Вложенный цикл от 0 до trim_chars_len
      if (trim_src[i] == trim_chars_minor[j]) {  // Проверка, если trim_src[i]
                                                 // равно trim_chars_minor[j]
        flag2 = 1;  // Установка flag2 в 1, если trim_src[i] равно
                    // trim_chars_minor[j]
        break;  // Выход из вложенного цикла
      }
    }
    if (flag2 == 1) {  // Проверка, если flag2 равно 1
      end_i--;  // Уменьшение значения переменной end_i на 1
    } else {
      break;  // Выход из цикла
    }
  }
  return end_i;  // Возврат значения переменной end_i
}