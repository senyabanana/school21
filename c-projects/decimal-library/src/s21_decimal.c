#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_long_decimal zerol = {{0, 0, 0, 0, 0, 0, 0}};
  *result = (zero);
  int res = 0, exp_1 = get_exp(value_1), exp_2 = get_exp(value_2);
  exp_1 > 28 ? round_exp(&value_1, exp_1, 28), exp_1 = 28 : 0;
  exp_2 > 28 ? round_exp(&value_2, exp_2, 28), exp_2 = 28 : 0;
  int exp = exp_1 > exp_2 ? exp_1 : exp_2;
  unsigned int sign_1 = check_bit(value_1.bits[3], 31),
               sign_2 = check_bit(value_2.bits[3], 31);
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  s21_long_decimal temp = zerol, a = zerol, b = zerol;
  copy_structs(&value_1, &a, 0);
  copy_structs(&value_2, &b, 0);
  normalize_exp_long(&a, &b, exp_1, exp_2);
  if (sign_1 != sign_2) {
    if (greater_long_decimal(a, b)) {
      sub_long_decimal(a, b, &temp);
    } else {
      sub_long_decimal(b, a, &temp);
      sign_1 = !sign_1;
    }
  } else {
    res = add_long_decimal(a, b, &temp);
  }
  while (!check_long_decimal(temp) && exp) {
    round_exp_long(&temp, exp, exp - 1);
    exp--;
  }
  if (!res && check_long_decimal(temp)) {
    copy_structs(result, &temp, 1);
    result->bits[3] = ((exp << 16) + (sign_1 << 31));
  } else {
    res = 1 + sign_1;
  }
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_long_decimal zerol = {{0, 0, 0, 0, 0, 0, 0}};
  *result = zero;
  int res = 0, exp_1 = get_exp(value_1), exp_2 = get_exp(value_2);
  exp_1 > 28 ? round_exp(&value_1, exp_1, 28), exp_1 = 28 : 0;
  exp_2 > 28 ? round_exp(&value_2, exp_2, 28), exp_2 = 28 : 0;
  int exp = exp_1 > exp_2 ? exp_1 : exp_2;
  unsigned int sign_1 = check_bit(value_1.bits[3], 31),
               sign_2 = check_bit(value_2.bits[3], 31);
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  s21_long_decimal temp = zerol, a = zerol, b = zerol;
  copy_structs(&value_1, &a, 0);
  copy_structs(&value_2, &b, 0);
  normalize_exp_long(&a, &b, exp_1, exp_2);
  if (sign_1 != sign_2) {
    add_long_decimal(a, b, &temp);
  } else {
    if (greater_long_decimal(a, b)) {
      sub_long_decimal(a, b, &temp);
    } else {
      sub_long_decimal(b, a, &temp);
      sign_1 = !sign_1;
    }
  }
  while (!check_long_decimal(temp) && exp) {
    round_exp_long(&temp, exp, exp - 1);
    exp--;
  }
  if (check_long_decimal(temp)) {
    copy_structs(result, &temp, 1);
    result->bits[3] = ((exp << 16) + (sign_1 << 31));
  } else {
    res = 1 + sign_1;
  }
  return res;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_long_decimal zerol = {{0, 0, 0, 0, 0, 0, 0}};
  *result = zero;
  int exp_1 = get_exp(value_1), exp_2 = get_exp(value_2);
  exp_1 > 28 ? round_exp(&value_1, exp_1, 28), exp_1 = 28 : 0;
  exp_2 > 28 ? round_exp(&value_2, exp_2, 28), exp_2 = 28 : 0;
  int exp = exp_1 + exp_2;
  int sign_1 = check_bit(value_1.bits[3], 31),
      sign_2 = check_bit(value_2.bits[3], 31);
  sign_1 = sign_1 && sign_2 ? 0 : sign_1 || sign_2;
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  s21_long_decimal temp = zerol, a = zerol, b = zerol;
  copy_structs(&value_1, &a, 0);
  copy_structs(&value_2, &b, 0);
  int check =
          zeros_equal_decimal(value_1, 3) || zeros_equal_decimal(value_2, 3),
      res = 0;
  for (int i = search_bits(a); i >= 0 && !check && !res; i--) {
    check_bit(a.bits[i / 32], i % 32) ? add_long_decimal(b, temp, &temp) : 0;
    res = !res && temp.bits[3] > 0 && !exp;
    i ? shift_left_long(&temp, 1) : 0;
  }
  if (!check && !res && exp > 28) {
    round_exp_long(&temp, exp, 28);
    exp = 28;
    check = zeros_equal_long_decimal(temp);
  }
  while (!check_long_decimal(temp) && exp) {
    round_exp_long(&temp, exp, exp - 1);
    exp--;
  }
  if (!check && check_long_decimal(temp)) {
    copy_structs(result, &temp, 1);
    result->bits[3] = exp << 16;
    set_bit(&result->bits[3], 31, sign_1);
  } else if (!check) {
    res = 1 + sign_1;
  }
  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero = {{0, 0, 0, 0}};
  *result = zero;
  int res = zeros_equal_decimal(value_2, 3) ? 3 : 0;  // деление на 0
  if (!res) {
    res = div_decimal(value_1, value_2, result);
  }
  return res;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2) ? !s21_is_greater(value_1, value_2)
                                         : 0;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_long_decimal zerol = {{0, 0, 0, 0, 0, 0, 0}};
  int result = !s21_is_equal(value_1, value_2), check = 0;
  int sign_1 = check_bit(value_1.bits[3], 31),
      sign_2 = check_bit(value_2.bits[3], 31);
  sign_1 > sign_2 ? result = 0 : sign_1 < sign_2 ? check = 1 : 0;
  int exp_1 = get_exp(value_1), exp_2 = get_exp(value_2);
  exp_1 > 28 ? round_exp(&value_1, exp_1, 28), exp_1 = 28 : 0;
  exp_2 > 28 ? round_exp(&value_2, exp_2, 28), exp_2 = 28 : 0;
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  s21_long_decimal a = zerol, b = zerol;
  copy_structs(&value_1, &a, 0);
  copy_structs(&value_2, &b, 0);
  normalize_exp_long(&a, &b, exp_1, exp_2);
  if (result && !check) {
    check = sign_1 && sign_2 ? !greater_long_decimal(a, b)
                             : greater_long_decimal(a, b);
  }
  return check && result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  for (int i = 127; i >= 0 && result; i--) {
    result = equal_bit(value_1.bits[i / 32], value_2.bits[i / 32], i % 32);
  }
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_decimal zero = {{0, 0, 0, 0}};
  *dst = zero;
  int sign = 0;
  src < 0 ? sign = 1, src *= -1 : 0;
  unsigned int binary_src =
      *((unsigned int *)&src);  // преобразование в битовое представление
  set_bit(&dst->bits[3], 31, sign);
  for (int i = 0; i < 31; i++) {
    set_bit(&dst->bits[0], i, check_bit(binary_src, i));
  }
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_decimal zero = {{0, 0, 0, 0}};
  *dst = zero;
  int sign = 0;
  src < 0 ? sign = 1, src *= -1 : 0;
  unsigned int binary_src_1 = *((unsigned int *)&src),
               binary_src_2 = *((unsigned int *)&src);
  unsigned int exp_set = 0, exp = binary_src_1 & EXP1_MASK;
  int check = src < 1e-28f || src > powf(2, 96) ||
              exp == EXP1_MASK;  // проверки, если число слишком малое, слишком
                                 // большое или NAN
  src >= MAX_FLOAT && !check ? float_nonexp(binary_src_2, dst)
  : !check                   ? float_exp(&exp_set, dst, src)
                             : 0;
  exp_set <<= 16;
  set_bit(&exp_set, 31, sign);
  dst->bits[3] = exp_set * (unsigned int)!check;
  return check;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int sign = check_bit(src.bits[3], 31) ? -1 : 1;
  long double mantiss = 0, exp = get_exp(src);
  for (int i = 0; i < 96; i++) {
    mantiss += (long double)check_bit(src.bits[i / 32], i % 32) * pow(2, i);
  }
  mantiss *= powl(10.l, -exp);
  int res = mantiss > ~MAX_BIT;  // проверка на переполнение
  *dst = (int)(mantiss * sign * !res);
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int sign = check_bit(src.bits[3], 31) ? -1 : 1;
  long double mantiss = 0, exp = get_exp(src);
  for (int i = 0; i < 96; i++) {
    mantiss += (long double)check_bit(src.bits[i / 32], i % 32) * pow(2, i);
  }
  *dst = (float)(mantiss * sign * powl(10.f, -exp));
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int sign = !!(value.bits[3] & MAX_BIT);
  s21_truncate(value, result);
  s21_decimal temp = {{sign, 0, 0, 0}};
  add_decimal(*result, temp, result, 96);
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int exp = get_exp(value);
  s21_truncate(value, result);
  s21_decimal temp_1 = *result;
  mul_ten_decimal(&temp_1, 3, exp);
  sub_decimal(value, temp_1, &value, 96);
  div_ten_decimal(&value, 95, exp - 1);
  s21_decimal temp_2 = {{value.bits[0] > 4, 0, 0, 0}};
  add_decimal(*result, temp_2, result, 96);
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int exp = get_exp(value);
  clear_exp(&value);
  div_ten_decimal(&value, 95, exp);
  copy_decimal(value, result);
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  set_bit(&result->bits[3], 31, !check_bit(result->bits[3], 31));
  return 0;
}