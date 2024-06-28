#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  specifier spec = {0};
  const char *start;
  start = str;
  va_list ap;
  va_start(ap, format);
  while (*str == ' ') str++;
  if (isspace(*format)) {
    while (isspace(*str)) str++;
    while (isspace(*format)) format++;
  }
  if (!*format && *str) spec.some_read++;
  while ((*str && *format) || (!*str && *format == '%')) {
    if ((*str == *format) && *format != '%') {
      str++, format++;
    } else if (*format == '%') {
      format = parsing(format, &spec);
      if ((spec.weight != 1024 && spec.star) || !spec.spec ||
          (!*str && spec.spec != 'n')) {
        spec.some_read++;
        break;
      }
      write_var(&spec, str, ap, start);

      if (spec.finish) break;
      str = spec.str;
    } else {
      break;
    }
    while (*str == ' ') str++;
    if (isspace(*format)) {
      while (isspace(*str)) str++;
      while (isspace(*format)) format++;
    }
  }
  va_end(ap);
  if (spec.some_read == 0) spec.n = -1;
  return spec.n;
}

const char *parsing(const char *format, specifier *spec) {
  int n = spec->n;
  spec_zero(spec);
  spec->n = n;
  spec->weight = 1024;
  format++;

  if (*format == '*') {
    spec->star = 1;
    format++;
  }
  if (*format >= '0' && *format <= '9') {
    spec->weight = 0;
    while (*format >= '0' && *format <= '9') {
      spec->weight = (spec->weight * 10 + (*format - '0'));
      format++;
    }
  }
  if (s21_strchr(LEN_LIST, *format)) {  // change to s21_strchr!!
    spec->lenght = *format;
    format++;
  }
  if (spec->lenght == *format) {  // change to s21_strchr!!
    format++;
    spec->d_lenght = 1;
  }
  if (s21_strchr(SPEC_LIST, *format)) {  // change to s21_strchr!!
    spec->spec = *format;
    if (*format) format++;
  }

  return format;
}

int write_var(specifier *spec, const char *str, va_list ap, const char *start) {
  switch (spec->spec) {
    case 'g':
    case 'G':
    case 'e':
    case 'E':
    case 'f':
      setE(spec, str, ap);
      break;
    case 'o':
    case 'x':
    case 'X':
    case 'p':
    case 'd':
    case 'i':
      setI(spec, str, ap);
      break;
    case 'c':
      setC(spec, str, ap);
      break;
    case 's':
      setS(spec, str, ap);
      break;
    case 'u':
      break;
    case '%':
      if (*str != '%') {
        spec->finish = 1;
      } else {
        str++;
      }
      if (str) spec->str = (char *)str;
      break;
    case 'n':
      spec->n_count = (int)(str - start);
      setN(spec, str, ap);
      break;
    default:
      break;
  }
  return 0;
}

int setS(specifier *spec, const char *str, va_list ap) {
  while (isspace(*str)) str++;
  int count = 0;

  char tmp[100] = {0};
  char *ptmp = tmp, *s = NULL;
  while (!isspace(*str) && 0 < spec->weight-- && *str) {
    spec->some_read++;
    count++;
    *(ptmp++) = *(str++);
  }
  if (spec->star == 0 && count) {
    s = va_arg(ap, char *);
    s21_strcpy(s, tmp);
    spec->n++;
  }

  if (str) spec->str = (char *)str;
  return 0;
}

int setD(specifier *spec, const char *str, va_list ap, int minus) {
  long long int tmp = 0;
  int count = 0;
  long long int over = 0;

  while (*str && !isspace(*str) && 0 < spec->weight--) {
    spec->some_read++;
    if (!isdigit(*str)) {
      spec->finish = 1;
      break;
    }

    over = tmp;
    tmp = tmp * 10 + ((*str++) - '0');
    if (tmp < over) spec->over = 1;
    count++;
  }

  if (spec->star == 0 && count) {
    if (spec->lenght == 'h') {
      if (spec->over) {
        tmp = -1;
        if (minus == -1) tmp++;
      }
      short int *s = va_arg(ap, short int *);
      *s = tmp * minus;
    }

    if (spec->lenght == 'l') {
      if (spec->over) {
        tmp = INT_MAX;
        if (minus == -1) tmp = tmp * minus - 1;
      }
      long int *s = va_arg(ap, long int *);
      *s = tmp * minus;
    }

    if (spec->lenght == 0) {
      if (spec->over) {
        tmp = -1;
        if (minus == -1) tmp++;
      }
      int *s = va_arg(ap, int *);
      *s = tmp * minus;
    }

    spec->n++;
  }

  if (str) spec->str = (char *)str;
  return 0;
}

int setO(specifier *spec, const char *str, va_list ap, int minus) {
  long long tmp = 0;
  int count = 0;

  while (*str && !isspace(*str) && 0 < spec->weight--) {
    if (!isdigit(*str) || *str >= '8') {
      if (!count && spec->spec != 'i') spec->finish = 1;
      break;
    }
    spec->some_read++;
    count++;

    long long over = tmp;
    tmp = tmp * 8 + ((*str++) - '0');
    if (tmp < over) spec->over = 1;
  }

  if (spec->star == 0 && (count || spec->spec == 'i')) {
    spec->n++;
    if (spec->lenght == 'h') {
      if (spec->over) {
        tmp = -1;
        if (minus == -1) tmp++;
      }
      short int *s = va_arg(ap, short int *);
      *s = tmp * minus;
    }

    if (spec->lenght == 'l') {
      if (spec->over) {
        tmp = INT_MAX;
        if (minus == -1) tmp = tmp * minus - 1;
      }
      long int *s = va_arg(ap, long int *);
      *s = tmp * minus;
    }

    if (spec->lenght == 0) {
      if (spec->over) {
        tmp = -1;
        if (minus == -1) tmp++;
      }
      int *s = va_arg(ap, int *);
      *s = tmp * minus;
    }
  }

  if (str) spec->str = (char *)str;
  return 0;
}

int setX(specifier *spec, const char *str, va_list ap, int minus) {
  long long tmp = 0;
  int count = 0;
  if ((*(str) == '0') && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
    spec->weight -= 2;
    count++;
    spec->some_read++;
  }

  while (*str && !isspace(*str) && 0 < spec->weight--) {
    if (!isxdigit(*str)) {
      if (!count && spec->spec != 'i') spec->finish = 1;
      break;
    }
    spec->some_read++;
    long long over = tmp;
    if (isdigit(*str))
      tmp = tmp * 16 + ((*str++) - '0');
    else if (*str <= 'F' && *str >= 'A')
      tmp = tmp * 16 + ((*str++) - '7');
    else if (*str <= 'f' && *str >= 'a')
      tmp = tmp * 16 + ((*str++) - 'W');
    if (tmp < over) spec->over = 1;
    count++;
  }
  if (spec->over) {
    tmp = -1;
    if (minus == -1) tmp++;
  }
  if (spec->star == 0 && (count || spec->spec == 'i' || spec->spec == 'p')) {
    if (spec->lenght == 'h') {
      if (spec->over) {
        tmp = -1;
        if (minus == -1) tmp++;
      }
      short int *s = va_arg(ap, short int *);

      *s = (short int)tmp * minus;
    }

    if (spec->lenght == 'l' || spec->spec == 'p') {
      if (spec->over) {
        tmp = INT_MAX;
        if (minus == -1) tmp = tmp * minus - 1;
      }
      long *s = va_arg(ap, long *);
      *s = (long)tmp * minus;
    }

    if (spec->lenght == 0 && spec->spec != 'p') {
      if (spec->over) {
        tmp = -1;
        if (minus == -1) tmp++;
      }
      int *s = va_arg(ap, int *);
      *s = (int)tmp * minus;
    }
    spec->n++;
  }

  spec->str = (char *)str;
  return 0;
}

int setI(specifier *spec, const char *str, va_list ap) {
  int finish = 0;
  while (isspace(*str)) str++;
  int minus = 1, convert = 10;
  if ((*str == '-' || *str == '+') && spec->weight != 1) {
    if (*str == '-') minus = -1;
    str++;
    spec->weight--;
    spec->some_read++;
  }

  if (spec->spec == 'd') {
    if (setD(spec, str, ap, minus)) {
      finish = 1;
    }
  } else if (spec->spec == 'p') {
    if ((*(str) == '0') && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
      str += 2;
      spec->weight -= 2;
      spec->some_read++;
    }
    setX(spec, str, ap, minus);
  } else if (spec->spec == 'o')
    setO(spec, str, ap, minus);
  else if (spec->spec == 'x' || spec->spec == 'X')
    setX(spec, str, ap, minus);
  else {
    if (*str == '0') {
      convert = 8;
      if (spec->weight > 0) {
        str++;
        spec->weight--;
        spec->some_read++;
      }

      if (*str == 'x' || *str == 'X') {
        convert = 16;
        if (spec->weight > 0) {
          str++;
          spec->weight--;
        }
      }
    }

    if (convert == 10) {
      setD(spec, str, ap, minus);
    } else if (convert == 8) {
      setO(spec, str, ap, minus);
    } else if (convert == 16)
      setX(spec, str, ap, minus);
  }
  return finish;
}

int setC(specifier *spec, const char *str, va_list ap) {
  if (spec->star == 0) {
    char *tmp = va_arg(ap, char *);
    *tmp = *str;
    spec->n++;
    spec->some_read++;
  } else {
  };
  if (str) str++;
  spec->str = (char *)str;
  return 0;
}

int setE(specifier *spec, const char *str, va_list ap) {
  char minus = 1;
  long double tmp = 0, tmp_i = 0, tmp_f = 0, tmp_e = 0;
  int count = 0;
  if (*str) spec->some_read++;
  while (isspace(*str)) str++;
  if (*str == '-' || *str == '+') {
    if (*str == '-') minus = -1;
    str++;
    spec->weight--;
  }

  while (*str != '.' && *str != 'e' && *str != 'E' && 0 < spec->weight--) {
    if (!isdigit(*str)) {
      if (!count) spec->finish = 1;
      break;
    }
    spec->some_read++;
    tmp_i = tmp_i * 10 + ((*str++) - '0');
    tmp = tmp_i;
    count++;
  }

  if (*str == '.' && 0 < spec->weight) {
    str++, spec->weight--;
    int i = 0;
    while (!isspace(*str) && *str != 'e' && *str != 'E' && isdigit(*str) &&
           0 < spec->weight--) {
      i++;
      tmp_f = tmp_f * 10 + ((*str++) - '0');
    }
    tmp += (tmp_f / pow(10.0, (double)i));
    count++;
  }

  if ((*str == 'e' || *str == 'E') && 0 < spec->weight) {
    int e = 0;
    str++;
    int minus = 1;
    if ((*str == '-' || *str == '+') && spec->weight > 0) {
      if (*str == '-') minus = -1;
      str++;
      spec->weight--;
    }
    while (!isspace(*str) && *str && 0 < spec->weight--) {
      if (!isdigit(*str)) {
        break;
      }
      e++;
      tmp_e = tmp_e * 10 + ((*str++) - '0');
      count++;
    }
    tmp *= pow(10.0, (tmp_e * minus));
  }

  if (spec->star == 0 && count) {
    if (spec->lenght == 'l' || spec->lenght == 'h') {
      double *s = va_arg(ap, double *);
      *s = tmp * minus;
    }

    if (spec->lenght == 'L') {
      long double *s = va_arg(ap, long double *);
      *s = tmp * minus;
    }

    if (spec->lenght == 0) {
      float *s = va_arg(ap, float *);
      *s = tmp * minus;
    }
    spec->n++;
  }
  spec->str = (char *)str;
  return 0;
}

int setN(specifier *spec, const char *str, va_list ap) {
  spec->some_read++;
  if (spec->star == 0) {
    if (spec->lenght == 0) {
      int *tmp = va_arg(ap, int *);
      *tmp = spec->n_count;

    } else if (spec->lenght == 'h') {
      if (spec->d_lenght == 0) {
        short *tmp = va_arg(ap, short *);
        *tmp = (short)spec->n_count;
      } else {
        char *tmp = va_arg(ap, char *);
        *tmp = (char)spec->n_count;
      }
    } else if (spec->lenght == 'l') {
      if (spec->d_lenght == 0) {
        long *tmp = va_arg(ap, long *);
        *tmp = (short)spec->n_count;
      } else {
        long long *tmp = va_arg(ap, long long *);
        *tmp = (char)spec->n_count;
      }
    }
  }

  spec->str = (char *)str;
  return 0;
}

void spec_zero(specifier *spec) {
  spec->star = 0;
  spec->weight = 0;
  spec->lenght = 0;
  spec->d_lenght = 0;
  spec->spec = 0;
  spec->over = 0;
}