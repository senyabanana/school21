#include "s21_decimal.h"

const unsigned int SD[32] = {
    0x80000000, 0xc0000000, 0xe0000000, 0xf0000000, 0xf8000000, 0xfc000000,
    0xfe000000, 0xff000000, 0xff800000, 0xffc00000, 0xffe00000, 0xfff00000,
    0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000, 0xffff8000, 0xffffc000,
    0xffffe000, 0xfffff000, 0xfffff800, 0xfffffc00, 0xfffffe00, 0xffffff00,
    0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0, 0xfffffff8, 0xfffffffc,
    0xfffffffe, 0xffffffff};

// Узнать какой бит на позиции начиная с 0
int check_bit(const int value, const int index) {
  return (value & (1 << index)) != 0;
}

// Установить нужный бит на нужную позицию начиная с 0
void set_bit(unsigned int *value, const int index, const int bit) {
  *value = bit ? (*value | (1 << index)) : (*value & ~(1 << index));
}

// Сравнение 2 битов на указанной позиции
int equal_bit(unsigned int value_1, unsigned int value_2, int index) {
  return check_bit(value_1, index) == check_bit(value_2, index) ? 1 : 0;
}

// Сдвинуть влево указанное колличество битов на указанный шаг
void shift_left(s21_decimal *value, const int cells, const int shift) {
  unsigned int temp1 = 0, temp2 = 0;
  for (int i = 0; i < cells; i++) {
    if (!(i % 2)) {
      temp1 = (value->bits[i] & SD[shift - 1]) >> (32 - shift);
      value->bits[i] <<= shift;
      value->bits[i] += temp2;
    } else {
      temp2 = (value->bits[i] & SD[shift - 1]) >> (32 - shift);
      value->bits[i] <<= shift;
      value->bits[i] += temp1;
    }
  }
}

// Сдвинуть указанное колличество битов на указанный шаг в long decimal
void shift_left_long(s21_long_decimal *value, const int shift) {
  unsigned int temp1 = 0, temp2 = 0;
  for (int i = 0; i < MAX_LONG_BITS; i++) {
    if (!(i % 2)) {
      temp1 = (value->bits[i] & SD[shift - 1]) >> (32 - shift);
      value->bits[i] <<= shift;
      value->bits[i] += temp2;
    } else {
      temp2 = (value->bits[i] & SD[shift - 1]) >> (32 - shift);
      value->bits[i] <<= shift;
      value->bits[i] += temp1;
    }
  }
}

int greater_decimal(s21_decimal value_1, s21_decimal value_2, int max_bits) {
  int check = 0;
  for (int i = max_bits - 1; i >= 0 && !check; i--) {
    int value_1_bit = check_bit(value_1.bits[i / 32], i % 32);
    int value_2_bit = check_bit(value_2.bits[i / 32], i % 32);
    if (value_1_bit > value_2_bit) {
      check = 1;
    } else if (value_1_bit < value_2_bit) {
      check = -1;
    }
  }
  return check > 0;
}

int greater_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2) {
  int check = 0, value_1_bit = 0, value_2_bit = 0;
  for (int i = MAX_LONG; i >= 0 && !check; i--) {
    value_1_bit = check_bit(value_1.bits[i / 32], i % 32);
    value_2_bit = check_bit(value_2.bits[i / 32], i % 32);
    if (value_1_bit > value_2_bit) {
      check = 1;
    } else if (value_1_bit < value_2_bit) {
      check = -1;
    }
  }
  return check > 0;
}

int zeros_equal_decimal(s21_decimal value, int max_bits) {
  int result = 0;
  set_bit(&value.bits[3], 31, 0);
  for (int i = 0; i < max_bits; i++) {
    result += value.bits[i];
  }
  return !result;
}

int zeros_equal_long_decimal(s21_long_decimal value) {
  int result = 0;
  for (int i = 0; i < MAX_LONG_BITS; i++) {
    result += value.bits[i];
  }
  return !result;
}

int check_long_decimal(s21_long_decimal value) {
  return !value.bits[3] && !value.bits[4] && !value.bits[5] && !value.bits[6];
}

int is_equal_long_decimal(const s21_long_decimal value_1,
                          const s21_long_decimal value_2) {
  int result = 1;
  for (int i = MAX_LONG; i >= 0 && result; i--) {
    result = equal_bit(value_1.bits[i / 32], value_2.bits[i / 32], i % 32);
  }
  return result;
}

void copy_decimal(s21_decimal value_1, s21_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
  value_2->bits[3] = value_1.bits[3];
}

void copy_long_decimal(s21_long_decimal value_1, s21_long_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
  value_2->bits[3] = value_1.bits[3];
  value_2->bits[4] = value_1.bits[4];
  value_2->bits[5] = value_1.bits[5];
  value_2->bits[6] = value_1.bits[6];
}

void copy_structs(s21_decimal *value_1, s21_long_decimal *value_2, int shift) {
  if (shift == 1) {
    value_1->bits[0] = value_2->bits[0];
    value_1->bits[1] = value_2->bits[1];
    value_1->bits[2] = value_2->bits[2];
    value_1->bits[3] = value_2->bits[3];
  } else {
    value_2->bits[0] = value_1->bits[0];
    value_2->bits[1] = value_1->bits[1];
    value_2->bits[2] = value_1->bits[2];
    value_2->bits[3] = value_1->bits[3];
  }
}

int search_bits(s21_long_decimal value) {
  int result = 0, i = MAX_LONG;
  for (; i >= 0 && !result; i -= !result) {
    result = check_bit(value.bits[i / 32], i % 32);
  }
  return i;
}

void float_exp(unsigned int *scale_amount, s21_decimal *dst, float src) {
  set_bit(&dst->bits[0], 0, 1);
  for (*scale_amount = 0;
       *scale_amount <= 28 &&
       (int)src != src;) {  // цикл определяет, сколько раз нужно умножить src,
                            // чтобы избавиться от дробной части
    if ((int)src != src) {  // проверяем, является ли src целым числом (не имеет
                            // дробной части)
      *scale_amount += 1;
      src *= 10;
    }
  }
  unsigned int get_int = (int)src;
  for (int i = 0; i < 31;
       i++) {  // устанавливаем биты в массиве bits на основе get_int
    set_bit(&dst->bits[0], i,
            check_bit(get_int, i));  // проверяем бит в значении get_int т
                                     // устанавливаем его в массиве
  }
}

void float_nonexp(unsigned int binary_scale, s21_decimal *dst) {
  unsigned int bit = 30, scale = 0;
  for (int i = 7; i >= 0;
       bit--, i--) {  // копирует 8 бит экспоненты в переменную scale
    set_bit(&scale, i, check_bit(binary_scale, bit));
  }
  scale -= 127;  // выполняем выравнивание и преобразуем экспоненту из формата
                 // IEEE 754 в децимал
  if (scale < 96) {  // если число меньше 96, значит оно находится в диапазоне
                     // допустимых значений для децимал
    set_bit(&dst->bits[scale / 32], scale % 32, 1);
    scale--;
    for (int j = 22; j >= 0; scale--, j--) {
      set_bit(&dst->bits[scale / 32], scale % 32, check_bit(binary_scale, j));
    }
  }
}

unsigned int get_exp(s21_decimal value) {
  return (value.bits[3] & EXP2_MASK) >> 16;
}

void clear_exp(s21_decimal *value) { value->bits[3] &= SD[0]; }

void normalize_exp_long(s21_long_decimal *value_1, s21_long_decimal *value_2,
                        unsigned int exp_1, unsigned int exp_2) {
  if (exp_1 > exp_2) {
    mul_ten_long_decimal(value_2, exp_1 - exp_2);
  } else if (exp_1 < exp_2) {
    mul_ten_long_decimal(value_1, exp_2 - exp_1);
  }
}

void round_exp(s21_decimal *value, int exp, int needed) {
  s21_decimal ones = {{1, 0, 0, 0}};
  s21_decimal copy1_value = *value;
  div_ten_decimal(value, 127, needed - exp);
  s21_decimal copy2_value = *value;
  mul_ten_decimal(&copy2_value, 4, needed - exp);
  sub_decimal(copy1_value, copy2_value, &copy1_value, 127);
  div_ten_decimal(&copy1_value, 127, needed - exp - 1);
  copy1_value.bits[0] > 4 ? add_decimal(*value, ones, value, 127) : 0;
}

void round_exp_long(s21_long_decimal *value, int exp, int needed) {
  s21_long_decimal onesl = {{1, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal copy1_value = *value;
  div_ten_long_decimal(value, exp - needed);
  s21_long_decimal copy2_value = *value;
  mul_ten_long_decimal(&copy2_value, exp - needed);
  sub_long_decimal(copy1_value, copy2_value, &copy1_value);
  div_ten_long_decimal(&copy1_value, exp - needed);
  copy1_value.bits[0] > 4 ? add_long_decimal(*value, onesl, value) : 0;
}

int add_decimal(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                int max_bits) {
  s21_decimal zero = {{0, 0, 0, 0}};
  int flag = 0, res = 0;  // переменные для переполнения и результата
  for (int i = 0; i < max_bits && !res;
       i++) {  // цикл для обработки каждого бита
    int add_bits =
        check_bit(value_1.bits[i / 32], i % 32) +
        check_bit(value_2.bits[i / 32],
                  i % 32);  // вычисляется сумма битов на текущей позиции чисел
    if (add_bits == 2 && flag == 1) {  // Обработка всех возможных комбинаций
                                       // суммы битов и значения переполнения
      set_bit(&result->bits[i / 32], i % 32,
              1);  // Есть переполнение в текущей позиции
      flag = 1;
    } else if (add_bits == 2 && flag == 0) {
      set_bit(&result->bits[i / 32], i % 32,
              0);  // Есть переполнение, но в текущей позиции нет переноса
      flag = 1;
    } else if (add_bits == 1 && flag == 1) {
      set_bit(&result->bits[i / 32], i % 32,
              0);  // Есть перенос, но в текущей позиции нет переполнения
      flag = 1;
    } else if (add_bits == 1 && flag == 0) {
      set_bit(&result->bits[i / 32], i % 32,
              1);  // Есть перенос, и в текущей позиции нет переполнения
    } else if (add_bits == 0 && flag == 1) {
      set_bit(&result->bits[i / 32], i % 32,
              1);  // Есть перенос с предыдущей позиции, но в текущей позиции
                   // нет переполнения
      flag = 0;
    } else {
      set_bit(&result->bits[i / 32], i % 32,
              0);  // Ни переноса, ни переполнения в текущей позиции
    }
    res = (i == max_bits - 1) &&
          flag;  // проверяем было ли переполнение в последней позиции
  }
  *result = res ? zero : *result;  // Если результат равен 1, то устанавливаем
                                   // ноль, иначе оставляем значение
  return res;  // Возвращаем результат (1 - переполнение, 0 - успешно)
}

int add_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2,
                     s21_long_decimal *result) {
  s21_long_decimal zerol = {{0, 0, 0, 0, 0, 0, 0}};
  *result = zerol;
  int flag = 0, res = 0;
  for (int i = 0; i <= MAX_LONG && !res; i++) {
    int add_bits = check_bit(value_1.bits[i / 32], i % 32) +
                   check_bit(value_2.bits[i / 32], i % 32);
    if (add_bits == 2 && flag == 1) {
      set_bit(&result->bits[i / 32], i % 32, 1);
      flag = 1;
    } else if (add_bits == 2 && flag == 0) {
      set_bit(&result->bits[i / 32], i % 32, 0);
      flag = 1;
    } else if (add_bits == 1 && flag == 1) {
      set_bit(&result->bits[i / 32], i % 32, 0);
      flag = 1;
    } else if (add_bits == 1 && flag == 0) {
      set_bit(&result->bits[i / 32], i % 32, 1);
    } else if (add_bits == 0 && flag == 1) {
      set_bit(&result->bits[i / 32], i % 32, 1);
      flag = 0;
    } else {
      set_bit(&result->bits[i / 32], i % 32, 0);
    }
    res = (i == MAX_LONG) && flag;
  }
  *result = res ? zerol : *result;
  return res;
}

void sub_decimal(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                 int max_bits) {
  for (int i = max_bits - 1; i >= 0; i--) {  // цикл для обработки каждого бита
                                             // (от старшего разряда к младшему)
    int sub_bits =
        check_bit(value_1.bits[i / 32], i % 32) -
        check_bit(value_2.bits[i / 32],
                  i % 32);  // вычисляется разность битов на текущей позиции
    if (sub_bits == 0) {  // если биты равны, устанавливает бит результата в 0
      set_bit(&result->bits[i / 32], i % 32, 0);
    } else if (sub_bits == 1) {  // если первый бит больше второго, уставаливает
                                 // бит результата в 1
      set_bit(&result->bits[i / 32], i % 32, 1);
    } else if (sub_bits == -1) {  // если второй бит больше первого, выполняем
                                  // заимствование (вычитание с переносом)
      int j = i,
          check =
              0;  // check - переменная как флаг нахождения установленного бита
      for (; j <= max_bits - 1 &&
             !check;) {  // цикл ищет первый установленный бит
        check = check_bit(result->bits[j / 32], j % 32);
        j++;
      }
      set_bit(&result->bits[(j - 1) / 32], (j - 1) % 32,
              0);  // устанавливает бит в 0 (выполняем заем из старшего разряда
                   // для выполнения вычитания)
      for (int k = j - 2; k >= i; k--) {
        set_bit(
            &result->bits[k / 32], k % 32,
            1);  // устанавливаем бит в 1, чтобы компенсировать заимствование
      }
    }
  }
}

void sub_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2,
                      s21_long_decimal *result) {
  for (int i = MAX_LONG; i >= 0; i--) {
    int sub_bits = check_bit(value_1.bits[i / 32], i % 32) -
                   check_bit(value_2.bits[i / 32], i % 32);
    if (sub_bits == 0) {
      set_bit(&result->bits[i / 32], i % 32, 0);
    } else if (sub_bits == 1) {
      set_bit(&result->bits[i / 32], i % 32, 1);
    } else if (sub_bits == -1) {
      int j = i, check = 0;
      for (; j <= MAX_LONG && !check;) {
        check = check_bit(result->bits[j / 32], j % 32);
        j++;
      }
      set_bit(&result->bits[(j - 1) / 32], (j - 1) % 32, 0);
      for (int k = j - 2; k >= i; k--) {
        set_bit(&result->bits[k / 32], k % 32, 1);
      }
    }
  }
}

void mul_ten_decimal(s21_decimal *value, const int cells,
                     const int shift_amount) {
  for (int i = 0; i < shift_amount; i++) {
    s21_decimal copy_value = *value;
    shift_left(value, cells, 3);  // сдвигаем число на 3 бита (умножаем на 8)
    shift_left(&copy_value, cells,
               1);  // сдвигаем число на 1 бит (умножаем на 2)
    add_decimal(*value, copy_value, value, 32 * cells);
  }
}

void mul_ten_long_decimal(s21_long_decimal *value, int shift_amount) {
  for (int i = 0; i < shift_amount; i++) {
    s21_long_decimal copy_value = *value;
    shift_left_long(value, 3);
    shift_left_long(&copy_value, 1);
    add_long_decimal(*value, copy_value, value);
  }
}

void div_ten_decimal(s21_decimal *value, int max_bits, int shift_amount) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal ones = {{1, 0, 0, 0}};
  s21_decimal tens = {{10, 0, 0, 0}};
  unsigned int bit = (max_bits == 95) ? value->bits[3] : 0;
  for (int i = 0; i < shift_amount; i++) {
    s21_decimal temp = zero, copy_value = *value;
    while (greater_decimal(copy_value, tens, max_bits) ||
           s21_is_equal(copy_value, tens)) {
      s21_decimal copy_tens1 = tens, copy_tens2 = tens, copy_ones = ones;
      int count_sub = 0;  // счетчик для подсчета колличества вычитаний
      while (greater_decimal(copy_value, copy_tens2, max_bits)) {
        mul_ten_decimal(&copy_tens2, (max_bits / 32) + 1, 1);
        if (greater_decimal(copy_value, copy_tens2, max_bits)) {
          copy_decimal(copy_tens2, &copy_tens1);
          count_sub++;
        }
      }
      mul_ten_decimal(&copy_ones, (max_bits / 32) + 1, count_sub);
      sub_decimal(copy_value, copy_tens1, &copy_value, max_bits);
      add_decimal(temp, copy_ones, &temp, max_bits);
    }
    copy_decimal(temp, value);
  }
  value->bits[3] = (max_bits == 95) ? bit : value->bits[3];
}

void div_ten_long_decimal(s21_long_decimal *value, int shift_amount) {
  s21_long_decimal zerol = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal onesl = {{1, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal tensl = {{10, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < shift_amount; i++) {
    s21_long_decimal temp = zerol, copy_value = *value;
    while (greater_long_decimal(copy_value, tensl) ||
           is_equal_long_decimal(copy_value, tensl)) {
      s21_long_decimal copy_tensl1 = tensl, copy_tensl2 = tensl,
                       copy_onesl = onesl;
      int count_sub = 0;
      while (greater_long_decimal(copy_value, copy_tensl2)) {
        mul_ten_long_decimal(&copy_tensl2, 1);
        if (greater_long_decimal(copy_value, copy_tensl2)) {
          copy_long_decimal(copy_tensl2, &copy_tensl1);
          count_sub++;
        }
      }
      mul_ten_long_decimal(&copy_onesl, count_sub);
      sub_long_decimal(copy_value, copy_tensl1, &copy_value);
      add_long_decimal(temp, copy_onesl, &temp);
    }
    copy_long_decimal(temp, value);
  }
}

int div_decimal(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_long_decimal zerol = {{0, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal onesl = {{1, 0, 0, 0, 0, 0, 0}};
  int exp_1 = get_exp(value_1), exp_2 = get_exp(value_2);
  exp_1 > 28     ? round_exp(&value_1, exp_1, 28),
      exp_1 = 28 : 0;  // проверяем экспоненту. Если она превышает 28
  exp_2 > 28     ? round_exp(&value_2, exp_2, 28),
      exp_2 = 28 : 0;  // то округляем ее
  int exp = 0,
      count = 0;  // exp - текущее значение экспоненты во время деления, count -
                  // отслеживание колличества умножений и делений на 10
  int sign_1 = !!(value_1.bits[3] & SD[0]),
      sign_2 = !!(value_2.bits[3] & SD[0]);
  // flag_over - флаг, который становится 1, если в процессе деления произошло
  // переполнение res - флаг, который используется для обозначения окончания
  // деления. Если флаг - 1, то деление завершается
  int flag_over = 0, res = 0;
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  s21_long_decimal a = zerol, b = zerol;
  copy_structs(&value_1, &a, 0);  // копируем структуры (decimal в long_decimal)
  copy_structs(&value_2, &b, 0);  // 0 - направление копирования
  normalize_exp_long(&a, &b, exp_1, exp_2);
  unsigned int shift_count = 0;
  s21_long_decimal temp_1 = zerol, temp_2 = zerol;
  s21_long_decimal on = onesl, copy_a = a;
  div_ten_long_decimal(&copy_a, 1);
  while (greater_long_decimal(copy_a, b) || is_equal_long_decimal(copy_a, b)) {
    if (greater_long_decimal(a, b) || is_equal_long_decimal(copy_a, b)) {
      mul_ten_long_decimal(&b, 1);
      count++;
    }
  }
  mul_ten_long_decimal(&on, count);
  while (exp < 29 && !flag_over && !res) {  // цикл деления
    // Если делитель меньше или равен делимому, вычитаем делитель и увеличиваем
    // результат
    if (greater_long_decimal(a, b) || is_equal_long_decimal(a, b)) {
      if (shift_count) {
        exp += shift_count;
        mul_ten_long_decimal(&temp_2, shift_count);
        shift_count = 0;
      }
      sub_long_decimal(a, b, &a);
      add_long_decimal(temp_1, on, &temp_1);
    } else if (!greater_long_decimal(a, b) && !zeros_equal_long_decimal(a)) {
      // Если делитель больше делимого, выравниваем их и увеличиваем результат
      while (count && greater_long_decimal(b, a)) {
        div_ten_long_decimal(&b, 1);
        div_ten_long_decimal(&on, 1);
        count--;
      }
      if (!zeros_equal_long_decimal(temp_1)) {
        add_long_decimal(temp_2, temp_1, &temp_2);
        temp_1 = zerol;
      } else if (!count) {
        mul_ten_long_decimal(&a, 1);
        shift_count++;
      }
    } else if (zeros_equal_long_decimal(a)) {
      // Если делимое становится равным нулю, завершаем деление
      add_long_decimal(temp_2, temp_1, &temp_2);
      flag_over = 1;
    }
    res = !res && temp_2.bits[3] > 0 && !exp;
  }
  int check = 0;
  if (exp > 28) {
    round_exp_long(&temp_2, exp, 28);
    exp = 28;
    check = zeros_equal_long_decimal(temp_2);
  }
  while (!check_long_decimal(temp_2) && exp && !check && !res) {
    round_exp_long(&temp_2, exp, exp - 1);
    exp--;
  }
  if (check) {
    *result = zero;
  } else if (!res && check_long_decimal(temp_2)) {
    copy_structs(result, &temp_2, 1);
    result->bits[3] = exp << 16;
    set_bit(&result->bits[3], 31, sign_1 && sign_2 ? 0 : sign_1 || sign_2);
  } else {
    res += sign_1;
  }
  return res;
}