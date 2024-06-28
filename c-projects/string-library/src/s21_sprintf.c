#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  Spec specs = {0};
  va_list argumenst;
  va_start(argumenst, format);
  char *src = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&specs, 0, sizeof(Spec));
    }
    format = parsing_flags(format, &specs);
    format = parsing_width(format, &specs, argumenst);
    format = parsing_accuracy(format, &specs, argumenst);
    format = parsing_length(format, &specs);

    specs.specifier = *format;
    format++;

    char buffer[ASSHOLE] = {'\0'};
    parser(specs, buffer, argumenst);
    for (int i = 0; buffer[i]; i++, str++) *str = buffer[i];

    if (specs.specifier == 'n') {
      int *ret = va_arg(argumenst, int *);
      *ret = str - src;
    }
  }
  *str = '\0';
  va_end(argumenst);
  return str - src;
}

const char *parsing_flags(const char *format, Spec *specs) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    switch (*format) {
      case '-':
        specs->minus = 1;
        break;
      case '+':
        specs->plus = 1;
        break;
      case ' ':
        specs->space = 1;
        break;
      case '0':
        specs->zero = 1;
        break;
      case '#':
        specs->hash = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *parsing_width(const char *format, Spec *specs, va_list arguments) {
  if (*format == '*') {
    format++;
    specs->width = va_arg(arguments, int);
  } else if (digit(*format)) {
    char tmp_buff[ASSHOLE] = {'\0'};
    for (int i = 0; digit(*format); i++, format++) {
      tmp_buff[i] = *format;
    }
    specs->width = str_to_int(tmp_buff);
  }
  return format;
}

const char *parsing_accuracy(const char *format, Spec *specs,
                             va_list arguments) {
  if (*format == '.') {
    specs->is_accuracy = 1;
    format++;
  }
  if (*format == '*') {
    format++;
    specs->accuracy = va_arg(arguments, int);
  }
  if (digit(*format)) {
    char tmp_buff[ASSHOLE] = {'\0'};
    for (int i = 0; digit(*format); i++, format++) {
      tmp_buff[i] = *format;
    }
    specs->accuracy = str_to_int(tmp_buff);
  }
  return format;
}

const char *parsing_length(const char *format, Spec *specs) {
  switch (*format) {
    case 'l':
      specs->lenght = 'l';
      format++;
      break;
    case 'L':
      specs->lenght = 'L';
      format++;
      break;
    case 'h':
      specs->lenght = 'h';
      format++;
      break;
  }
  return format;
}

void parser(Spec specs, char *buffer, va_list arguments) {
  switch (specs.specifier) {
    case 'd':
    case 'i':
      parse_int(specs, buffer, arguments);
      break;
    case 'u':
      parse_unsigned(specs, buffer, arguments);
      break;
    case 'o':
      parse_octal(specs, buffer, arguments);
      break;
    case 'x':
    case 'X':
      parse_hex(specs, buffer, arguments);
      break;
    case 'c':
      parse_char(specs, buffer, arguments);
      break;
    case 's':
      parse_string(specs, buffer, arguments);
      break;
    case 'p':
      parse_ptr(specs, buffer, arguments);
      break;
    case 'f':
      parse_float(specs, buffer, arguments);
      break;
    case 'e':
    case 'E':
      parse_double(specs, buffer, arguments);
      break;
    case 'g':
    case 'G':
      parse_g(specs, buffer, arguments);
      break;
    case '%':
      buffer[0] = '%';
      break;
  }
  if (specs.specifier == 'X' || specs.specifier == 'E' ||
      specs.specifier == 'G') {
    upper_case(buffer);
  }
}

void parse_int(Spec specs, char *buffer, va_list arguments) {
  int64_t num = va_arg(arguments, int64_t);
  switch (specs.lenght) {
    case 0:
      num = (int32_t)num;
      break;
    case 'h':
      num = (int16_t)num;
      break;
  }
  convert_int_to_string(num, buffer, 10);
  format_accuracy(buffer, specs);
  format_flags(buffer, specs);
}

void parse_unsigned(Spec specs, char *buffer, va_list arguments) {
  uint64_t num = va_arg(arguments, uint64_t);
  switch (specs.lenght) {
    case 0:
      num = (uint32_t)num;
      break;
    case 'h':
      num = (uint16_t)num;
      break;
    case 'l':
      num = (uint64_t)num;
      break;
  }
  convert_unsigned_int_string(num, buffer, 10);
  format_accuracy(buffer, specs);
  format_flags(buffer, specs);
}

void parse_octal(Spec specs, char *buffer, va_list arguments) {
  buffer[0] = '0';
  convert_int_to_string(va_arg(arguments, int64_t), buffer + specs.hash, 8);
  format_accuracy(buffer, specs);
  format_flags(buffer, specs);
}

void parse_hex(Spec specs, char *buffer, va_list arguments) {
  uint64_t num = va_arg(arguments, uint64_t);
  switch (specs.lenght) {
    case 0:
      num = (uint32_t)num;
      break;
    case 'h':
      num = (uint16_t)num;
      break;
    case 'l':
      num = (uint64_t)num;
      break;
  }
  convert_unsigned_int_string(num, buffer, 16);
  format_accuracy(buffer, specs);
  if (specs.hash) {
    prefix_ox(buffer, specs);
  }
  format_flags(buffer, specs);
}

void parse_char(Spec specs, char *buffer, va_list arguments) {
  if (specs.lenght == 'l') {
    wchar_t w_c;
    w_c = va_arg(arguments, wchar_t);
    format_wchar(specs, buffer, w_c);
  } else {
    char ch;
    ch = va_arg(arguments, int);
    format_char(specs, buffer, ch);
  }
}

void parse_string(Spec specs, char *buffer, va_list arguments) {
  if (specs.lenght == 'l') {
    wchar_t *w_str = va_arg(arguments, wchar_t *);
    format_w_string(specs, buffer, w_str);
  } else {
    char *str = va_arg(arguments, char *);
    format_string(specs, buffer, str);
  }
}

void parse_ptr(Spec specs, char *buffer, va_list arguments) {
  convert_int_to_string(va_arg(arguments, int64_t), buffer, 16);
  format_accuracy(buffer, specs);
  prefix_ox(buffer, specs);
  format_flags(buffer, specs);
}

void parse_float(Spec specs, char *buffer, va_list arguments) {
  long double num = 0;
  if (specs.lenght == 'L') {
    num = va_arg(arguments, long double);
  } else {
    num = va_arg(arguments, double);
  }
  if (!specs.is_accuracy) {
    specs.accuracy = 6;
  }
  convert_double_to_string(num, buffer, specs);
  format_flags(buffer, specs);
}

void parse_double(Spec specs, char *buffer, va_list arguments) {
  long double num = 0;
  if (specs.lenght == 'L') {
    num = va_arg(arguments, long double);
  } else {
    num = va_arg(arguments, double);
  }
  int pow = 0;
  // Если число не является целым, знак равен "-", иначе "+"
  char sign = (int)num == 0 ? '-' : '+';

  if ((int)num - num) {
    while ((int)num == 0) {
      pow++;
      num *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)num / 10 != 0) {
    pow++;
    num /= 10;
  }
  if (!specs.is_accuracy) {
    specs.accuracy = 6;
  }
  convert_double_to_string(num, buffer, specs);
  prefix_e(buffer, pow, sign);
  format_flags(buffer, specs);
}

void parse_g(Spec specs, char *buffer, va_list arguments) {
  long double num = 0;
  if (specs.lenght == 'L') {
    num = va_arg(arguments, long double);
  } else {
    num = va_arg(arguments, double);
  }
  if (!specs.is_accuracy) {
    specs.accuracy = 6;
  }
  if (specs.accuracy == 0) {
    specs.accuracy = 1;
  }
  int accuracy = specs.accuracy;
  long double copy_num = num;
  int pow = 0;
  if ((int)num - num) {
    while ((int)copy_num == 0) {
      pow++;
      copy_num *= 10;
    }
  }
  if (pow > 4) {
    specs.accuracy = 0;
    convert_double_to_string(copy_num, buffer, specs);
  } else {
    specs.accuracy = 10;
    convert_double_to_string(num, buffer, specs);
  }
  format_g_accuracy(buffer, accuracy);
  if (pow > 4) {
    prefix_e(buffer, pow, '-');
  }
  remove_zeros(buffer);
  format_flags(buffer, specs);
}

void convert_int_to_string(int64_t num, char *ret, int base) {
  char tmp_buff[ASSHOLE] = {'\0'};
  int index = ASSHOLE - 2;

  bool neg_num = num < 0 ? 1 : 0;
  num = neg_num ? -num : num;

  if (num == 0) tmp_buff[index] = '0';

  while (num > 0) {
    index--;
    tmp_buff[index] = "0123456789abcdef"[num % base];
    num /= base;
  }
  for (int j = 0; tmp_buff[index]; index++, j++) {
    if (neg_num && j == 0) {
      ret[j++] = '-';
    }
    ret[j] = tmp_buff[index];
  }
}

void convert_unsigned_int_string(uint64_t num, char *ret, int base) {
  char tmp_buff[ASSHOLE + 1] = {'\0'};
  int index = ASSHOLE - 1;
  if (num == 0) {
    tmp_buff[index] = '0';
    index--;
  }
  for (; num && index; --index, num /= base) {
    tmp_buff[index] = "0123456789abcdef"[num % base];
  }
  for (int j = 0; tmp_buff[index + 1]; index++, j++) {
    ret[j] = tmp_buff[index + 1];
  }
}

void convert_double_to_string(long double num, char *ret, Spec specs) {
  char tmp_buff[ASSHOLE] = {'\0'};
  int index = ASSHOLE - 2;
  // Обработка отрицательных чисел
  bool neg_num = num < 0 ? 1 : 0;
  num = neg_num ? num * -1 : num;
  long double int_part = 0;
  long double fract_part = modfl(num, &int_part);
  if (specs.accuracy == 0) {
    int_part = roundl(num);
    fract_part = 0;
  }
  // Преобразование дробной части в строку
  char fract_str[ASSHOLE] = {'\0'};
  for (int i = 0; i < specs.accuracy; i++) {
    fract_part = fract_part * 10;
    fract_str[i] = (int)fract_part + '0';
  }
  // Производим округление дробной и целой частей
  long long fract_round = roundl(fract_part);
  long long int_round = int_part;
  // Если дробная часть равна нулю, заполняем ее нулями
  if (!fract_round) {
    for (int i = 0; i < specs.accuracy; index--, i++) {
      tmp_buff[index] = '0';
    }
  } else {
    for (int i = s21_strlen(fract_str); fract_round || i > 0;
         fract_round /= 10, index--, i--) {
      tmp_buff[index] = (int)(fract_round % 10 + 0.05) + '0';
    }
  }
  // Добавляем десятичную точку, если установлен флаг точности или если дробная
  // часть не равна нулю
  if ((specs.is_accuracy && specs.accuracy != 0) || (int)fract_part ||
      (!specs.is_accuracy && num == 0) || s21_strlen(fract_str)) {
    tmp_buff[index--] = '.';
  }
  // Добавляем целую часть числа в буфер
  if (!int_round) {
    tmp_buff[index] = '0';
    index--;
  } else {
    for (; int_round; int_round /= 10, index--) {
      tmp_buff[index] = (int)(int_round % 10) + '0';
    }
  }
  // Копируем буфер в итоговую строку, учитывая знак числа
  for (int i = 0; tmp_buff[index + 1]; index++, i++) {
    if (neg_num && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = tmp_buff[index + 1];
  }
}

void format_accuracy(char *buffer, Spec specs) {
  char tmp_buff[ASSHOLE] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buffer);

  if (buffer[0] == '-') {
    tmp_buff[0] = '-';
    len--;
    sign = 1;
  }

  if (specs.accuracy > len) {
    int index;
    for (index = sign; index < specs.accuracy - len + sign; index++) {
      tmp_buff[index] = '0';
    }
    for (int i = sign; buffer[i]; i++, index++) {
      tmp_buff[index] = buffer[i];
    }
    s21_strcpy(buffer, tmp_buff);
  }
  if (specs.is_accuracy && specs.accuracy == 0 &&
      is_int_specifier(specs.specifier) && buffer[0] == '0') {
    buffer[0] = '\0';
  }
}

void format_flags(char *buffer, Spec specs) {
  char tmp_buff[ASSHOLE] = {'\0'};
  if (specs.plus && specs.specifier != 'u') {
    tmp_buff[0] = buffer[0] == '-' ? buffer[0] : '+';
    s21_strcpy(tmp_buff + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    s21_strcpy(buffer, tmp_buff);
  } else if (specs.space && buffer[0] != '-' && specs.specifier != 'u') {
    tmp_buff[0] = ' ';
    s21_strcpy(tmp_buff + 1, buffer);
    s21_strcpy(buffer, tmp_buff);
  }
  if (specs.width > (int)s21_strlen(buffer)) {
    int index = specs.width - s21_strlen(buffer);
    if (!specs.minus) {
      s21_memset(tmp_buff, specs.zero ? '0' : ' ', index);
      s21_strcpy(tmp_buff + index, buffer);
    } else {
      s21_strcpy(tmp_buff, buffer);
      s21_memset(tmp_buff + s21_strlen(tmp_buff), ' ', index);
    }
    s21_strcpy(buffer, tmp_buff);
  }
}

void format_wchar(Spec specs, char *buffer, wchar_t w_c) {
  if (!specs.minus && specs.width) {
    char tmp_buff[ASSHOLE] = {'\0'};
    wcstombs(tmp_buff, &w_c, ASSHOLE);
    for (s21_size_t i = 0; i < specs.width - s21_strlen(tmp_buff); i++) {
      tmp_buff[i] = ' ';
    }
    s21_strcat(buffer, tmp_buff);
  } else if (specs.width) {
    wcstombs(buffer, &w_c, ASSHOLE);
    for (int i = s21_strlen(buffer); i < specs.width; i++) {
      buffer[i] = ' ';
    }
  } else {
    wcstombs(buffer, &w_c, ASSHOLE);
  }
}

void format_char(Spec specs, char *buffer, char ch) {
  if (!specs.minus && specs.width) {
    for (int i = 0; i < specs.width; i++) {
      buffer[i] = ' ';
      if (i == specs.width - 1) {
        buffer[i] = ch;
      }
    }
  } else if (specs.width) {
    buffer[0] = ch;
    for (int i = 1; i < specs.width; i++) {
      buffer[i] = ' ';
    }
  } else {
    buffer[0] = ch;
  }
}

void format_string(Spec specs, char *buffer, char *str) {
  char tmp_buff[ASSHOLE] = {'\0'};
  s21_strcpy(tmp_buff, str);
  if (specs.is_accuracy) {
    tmp_buff[specs.accuracy] = '\0';
  }
  int space_shift =
      specs.width -
      s21_strlen(tmp_buff);  // Вычисляется количество пробелов, которые нужно
                             // добавить перед или после строки
  int len = s21_strlen(
      tmp_buff);  // Вычисляется длина строки после применения точности

  if (specs.minus && space_shift > 0) {
    s21_strcpy(buffer, tmp_buff);
    s21_memset(buffer + len, ' ', space_shift);
  } else if (space_shift > 0) {
    s21_memset(buffer, ' ', space_shift);
    s21_strcpy(buffer + space_shift, tmp_buff);
  } else {
    s21_strcpy(buffer, tmp_buff);
  }
}

void format_w_string(Spec specs, char *buffer, wchar_t *w_str) {
  char tmp_buff[ASSHOLE] = {'\0'};
  char str[ASSHOLE] = {'\0'};

  wcstombs(str, w_str, ASSHOLE);
  s21_strcpy(tmp_buff, str);
  if (specs.is_accuracy) {
    tmp_buff[specs.accuracy] = '\0';
  }
  int space_shift = specs.width - s21_strlen(tmp_buff);
  int len = s21_strlen(tmp_buff);

  if (specs.minus && space_shift > 0) {
    s21_strcpy(buffer, tmp_buff);
    s21_memset(buffer + len, ' ', space_shift);
  } else if (space_shift > 0) {
    s21_memset(buffer, ' ', space_shift);
    s21_strcpy(buffer + space_shift, tmp_buff);
  } else {
    s21_strcpy(buffer, tmp_buff);
  }
}

void format_g_accuracy(char *buffer, int accuracy) {
  int sig_nums = 0;  // значимые числа
  s21_size_t len = s21_strlen(buffer);
  int flag_to_zero = 0;  // флаг отслеживания нуля
  for (s21_size_t i = 0; i < s21_strlen(buffer); i++) {
    if ((buffer[i] == '0' && !flag_to_zero) || buffer[i] == '.') {
      continue;
    } else {
      flag_to_zero = 1;
    }
    if (digit(buffer[i]) && flag_to_zero) {
      sig_nums++;
    }
    if (sig_nums == accuracy && i + 1 < len) {
      int next_i = buffer[i + 1] == '.' ? 2 : 1;
      buffer[i] =
          buffer[i + next_i] - '0' > 5 ? (char)(buffer[i] + 1) : buffer[i];
      buffer[i + 1] = '\0';
      break;
    }
  }
}

void remove_zeros(char *buffer) {
  int len = s21_strlen(buffer);
  char *dot = s21_strchr(buffer, '.');
  if (dot) {
    for (int i = len - 1; buffer[i] != '.'; i--) {
      if (buffer[i] == '0') {
        buffer[i] = '\0';
      } else {
        break;
      }
    }
    if (dot[1] == '\0') {
      dot[0] = '\0';
    }
  }
}

int digit(char c) { return (c >= '0' && c <= '9'); }

int str_to_int(const char *str) {
  int res = 0;
  int sign = 1;       // Знак числа
  int flag_over = 0;  // Флаг переполнения
  while (*str == ' ') str++;
  if (*str == '-') {
    str++;
    sign = -1;
  }
  if (*str == '+') str++;
  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      flag_over = 1;
      break;
    }
    str++;
  }
  // Если произошло переполнение, возвращаем максимально возможное или
  // минимально возможное число, в зависимости от знака
  if (flag_over)
    res = sign > 0 ? INT32_MAX : INT32_MIN;
  else
    res *= sign;
  return res;
}

char *s21_strcat(char *dest, const char *src) {
  s21_size_t i, j;
  for (i = 0; dest[i] != '\0'; i++) {
    ;
  }
  for (j = 0; src[j] != '\0'; j++) {
    dest[i + j] = src[j];
  }
  dest[i + j] = '\0';
  return dest;
}

char *s21_strcpy(char *dest, const char *src) {
  char *flag;
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  flag = dest;
  return flag;
}

void *s21_memmove(void *dst, const void *src, s21_size_t n) {
  unsigned char buffer[n];
  for (s21_size_t i = 0; i < n; i++) {
    buffer[i] = *((unsigned char *)(src) + i);
  }

  for (s21_size_t i = 0; i < n; i++) {
    *((unsigned char *)(dst) + i) = buffer[i];
  }
  return dst;
}

bool is_int_specifier(char c) {
  char specifiers[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  bool res = 0;
  for (s21_size_t i = 0; i < sizeof(specifiers); i++) {
    if (specifiers[i] == c) {
      res = 1;
      break;
    }
  }
  return res;
}

void prefix_ox(char *buffer, Spec specs) {
  if (!is_zero(buffer) || specs.specifier == 'p') {
    s21_memmove(buffer + 2, buffer, s21_strlen(buffer));
    buffer[0] = '0';
    buffer[1] = 'x';
  }
}

void prefix_e(char *str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'e';
  str[len + 1] = sign;
  str[len + 3] = pow % 10 + '0';
  pow /= 10;
  str[len + 2] = pow % 10 + '0';
  str[len + 4] = '\0';
}

bool is_zero(char *buffer) {
  for (int i = 0; buffer[i]; i++) {
    if (buffer[i] != '0') {
      return 0;
    }
  }
  return 1;
}

void upper_case(char *str) {
  while (*str) {
    if (*str >= 'a' && *str <= 'z') {
      *str = *str - 'a' + 'A';
    }
    str++;
  }
}