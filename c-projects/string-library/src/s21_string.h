#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long s21_size_t;

#define s21_NULL ((void *)0)

#define ASSHOLE 512

#define S21_NAN (-(0.0 / 0.0))
#define SPEC_LIST "gGeExXopcdfsui%%n"
#define LEN_LIST "hlL"
#define INT_MAX 9223372036854775807
#define INT_MIN -9223372036854775808

// Functions

// 1) Выполняет поиск первого вхождения символа c (беззнаковый тип)
//    в первых n байтах строки , на которую указывает аргумент str
void *s21_memchr(const void *str, int c, s21_size_t n);

// 2) Сравнивает первые n байтов str1 и str2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

// 3) Копирует n символов из src в dest
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

// 4) Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает аргумент str
void *s21_memset(void *str, int c, s21_size_t n);

// 5) Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длинной до n символов
char *s21_strncat(char *dest, const char *src, s21_size_t n);

// 6) Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке
// на которую указывает аргумент str
char *s21_strchr(const char *str, int c);

// 7) Сравнивает не более первых n байтов str1 и str2
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

// 8) Копирует до n символов из строки, на которую указывает src, в dest
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

// 9) Вычисляет длину начального сегмента str1, который полностью состоит
// из символов str2
s21_size_t s21_strcspn(const char *str1, const char *str2);

// 10) Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив
char *s21_strerror(int errnum);

// 11) Вычисляет длину строки str, не включая завершающий нулевой символ
s21_size_t s21_strlen(const char *str);

// 12) Находит первый символ в строке str1, который соответсвует любому символу
// указанному в str2
char *s21_strpbrk(const char *str1, const char *str2);

// 13) Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке
// на которую указывает аргумент str
char *s21_strrchr(const char *str, int c);

// 14) Находит первое вхождение всей строки needle (не включая завершающий
// нулевой символ) который появляется в строке haystack
char *s21_strstr(const char *haystack, const char *needle);

// 15) Разбивает строку str на ряд токенов, разделенных delim
char *s21_strtok(char *str, const char *delim);

// --------------------------------------------SPRINTF------------------------------------------------

typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool zero;
  bool hash;
  int accuracy;
  int is_accuracy;
  int width;
  char lenght;
  char specifier;
} Spec;

// --------------------------------------------Помогаторы---------------------------------------------

// Функция проверяет, является ли переданный символ десятичной цифрой
int digit(char c);

// Функция преобразует строку в целое число
int str_to_int(const char *str);

//
char *s21_strcat(char *dest, const char *src);

// Функция копирует содержимое исходной строки src в целевую строку dest
char *s21_strcpy(char *dest, const char *src);

//
void *s21_memmove(void *dst, const void *src, s21_size_t n);

// Функция проверяет, является ли символ c указателем на целочисленный тип
bool is_int_specifier(char c);

// Функция добавляет '0x' в начало строки
void prefix_ox(char *buffer, Spec specs);

// Функция добавляет экспоненту в строку, представляющую число в формате научной
// нотации
void prefix_e(char *str, int pow, char sign);

// Функция проверяет, состоит ли функция только из '0'
bool is_zero(char *buffer);

// Функция для верхнего регистра
void upper_case(char *str);

// ----------------------------------------------Парсинг----------------------------------------------

// Функция разбирает флаги из строки формата, возвращая указатель на следующий
// символ после последнего флага
const char *parsing_flags(const char *format, Spec *specs);

// Функция разбирает ширину из строки формата, обновляя структуру флагов и
// возвращая указатель на символ после ширины
const char *parsing_width(const char *format, Spec *specs, va_list arguments);

// Функция проверяет наличие точности в форматной строке
const char *parsing_accuracy(const char *format, Spec *specs,
                             va_list arguments);

// Функция проверяет наличие длины в форматной строке
const char *parsing_length(const char *format, Spec *specs);

// --------------------------------------Обработка
// аргументов-------------------------------------------

// Обработка спецификаторов
void parser(Spec specs, char *buffer, va_list arguments);

// Обработка d/i
void parse_int(Spec specs, char *buffer, va_list arguments);

// Обработка u
void parse_unsigned(Spec specs, char *buffer, va_list arguments);

// Обработка o
void parse_octal(Spec specs, char *buffer, va_list arguments);

// Обработка x/X
void parse_hex(Spec specs, char *buffer, va_list arguments);

// Обработка c
void parse_char(Spec specs, char *buffer, va_list arguments);

// Обработка s
void parse_string(Spec specs, char *buffer, va_list arguments);

// Обработка p
void parse_ptr(Spec specs, char *buffer, va_list arguments);

// Обработка f
void parse_float(Spec specs, char *buffer, va_list arguments);

// Обработка e/E
void parse_double(Spec specs, char *buffer, va_list arguments);

// Обработка g/G
void parse_g(Spec specs, char *buffer, va_list arguments);

// ------------------------------------------Конвертация---------------------------------------------

// Функция преобразует число в строку
void convert_int_to_string(int64_t num, char *ret, int base);

// Функция преобразует число (беззнаковый тип) в строку
void convert_unsigned_int_string(uint64_t num, char *ret, int base);

// Функция преобразует число с плавающей точкой в строку
void convert_double_to_string(long double num, char *ret, Spec specs);

// ----------------------------------------Обработка
// формата-------------------------------------------

// Обработка ширины
void format_accuracy(char *buffer, Spec specs);

// Обработка флагов
void format_flags(char *buffer, Spec specs);

// Функция форматирует широкий символ w_c
void format_wchar(Spec specs, char *buffer, wchar_t w_c);

// Функция форматирует обычный символ ch
void format_char(Spec specs, char *buffer, char ch);

// Функция форматирует обычную строку в соответствии с указанными флагами
void format_string(Spec specs, char *buffer, char *str);

// Функция форматирует широкую строку в соответствии с  указанными флагами
// форматирования
void format_w_string(Spec specs, char *buffer, wchar_t *w_str);

// Функция форматирует точность числа
void format_g_accuracy(char *buffer, int accuracy);

// Функция удаляет незначащие нули из дробной части числа
void remove_zeros(char *buffer);

// ----------------------------------------------------------------------------------------------------

int s21_sprintf(char *str, const char *format, ...);

// --------------------------------------------SSCANF--------------------------------------------------

typedef struct {
  int star;
  int weight;
  char lenght;
  char d_lenght;
  char spec;
  int n;
  char *str;
  short int over;
  short int finish;
  int n_count;
  int some_read;
} specifier;

int s21_sscanf(const char *str, const char *format, ...);
const char *parsing(const char *format, specifier *spec);
int write_var(specifier *spec, const char *str, va_list ap, const char *start);
int setS(specifier *spec, const char *str, va_list ap);
int setC(specifier *spec, const char *str, va_list ap);
int setD(specifier *spec, const char *str, va_list ap, int minus);
int setI(specifier *spec, const char *str, va_list ap);
int setE(specifier *spec, const char *str, va_list ap);
int setO(specifier *spec, const char *str, va_list ap, int minus);
int setX(specifier *spec, const char *str, va_list ap, int minus);
int setN(specifier *spec, const char *str, va_list ap);
void spec_zero(specifier *spec);

// ----------------------------------------------------------------------------------------------------

// Special functions

// 1) Возвращает копию строки (str), преобразованной в верхний регистр
void *s21_to_upper(const char *str);

// 2) Возвращает копию строки (str), преобразованной в нижний регистр
void *s21_to_lower(const char *str);

// 3) Возвращает новую строку, в которой указанная строка (str) вставлена
// в указанную позицию (start_index) в данной строке (src)
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

// 4) Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src)
void *s21_trim(const char *src, const char *trim_chars);
int s21_start_i(const char *trim_src, const char *trim_chars_minor,
                s21_size_t src_len, s21_size_t trim_chars_len);
int s21_end_i(const char *trim_src, const char *trim_chars_minor,
              s21_size_t src_len, s21_size_t trim_chars_len);

#endif