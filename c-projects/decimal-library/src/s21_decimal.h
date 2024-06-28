#ifndef _SRC_S21_DECIMAL_H_
#define _SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP1_MASK 0x7f800000  // маска для извлечения степени в битах 16-23
#define EXP2_MASK \
  0xff0000  // маска для извлечения степени в битах 16-23 (в более низком
            // уровне)
#define MANTIS_MASK \
  0x7fffff  // маска для извлечения мантиссы числа в битах 0-95
#define MAX_FLOAT 10000000
#define MAX_BIT 0x80000000
#define MAX_LONG 223
#define MAX_LONG_BITS 7

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_long_decimal;

/* Функции для работы с битами */

/* Узнать бит по индексу. Принимает unsigned число и позицию */
int check_bit(const int value, const int index);

/* Установить бит по индексу. Принимает указатель на unsigned, позицию и бит(0,
 * 1) */
void set_bit(unsigned int *value, const int index, const int bit);

/* Сравнить биты на позиции. Принимает два unsigned числа и позицию */
int equal_bit(unsigned int value_1, unsigned int value_2, int index);

/* Сдвигает всю конструкцию на указанное колличество битов в большую сторону.
Принимает указатель на s21_decimal, сколько ячеек двигать (0, 4) и размер сдвига
*/
void shift_left(s21_decimal *value, const int cells, const int shift);

/* Сдвигает всю конструкцию на указанное колличество битов в большую сторону.
Принимает указатель на s21_long_decimal и размер сдвига */
void shift_left_long(s21_long_decimal *value, const int shift);

/* Вспомогательные булевые функции */

/* Возвращает 1 если первое число больше второго. Сравнение идет по указзаному
 * колличеству битю Не учитывается знак и степень */
int greater_decimal(s21_decimal value_1, s21_decimal value_2, int max_bits);

/* Возвращает 1 если первое число больше второго. Сравнение идет по указзаному
 * колличеству битю Не учитывается знак и степень */
int greater_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2);

/* Сравнение числа с 0. Возвращает 1 если указанные ячейки (1, 3) переданной
 * структуры равны 0 */
int zeros_equal_decimal(s21_decimal value, int max_bits);

/* Сравнение числа с 0. Возвращает 1 если указанные ячейки (1, 3) переданной
 * структуры равны 0 */
int zeros_equal_long_decimal(s21_long_decimal value);

/* Проверяет все ли биты структуры s21_long_decimal равны 0 */
int check_long_decimal(s21_long_decimal value);

/* Проверяет на равенство двух чисел s21_long_decimal. Возвращает 1 если числа
 * равны */
int is_equal_long_decimal(const s21_long_decimal value_1,
                          const s21_long_decimal value_2);

/* Прочие вспомогательные функции */

/* Копирует перувую структуру s21_decimal в другую */
void copy_decimal(s21_decimal value_1, s21_decimal *value_2);

/* Копирует перувую структуру s21_decimal_long в другую */
void copy_long_decimal(s21_long_decimal value_1, s21_long_decimal *value_2);

/* Копирует данные между структурами s21_decimal и s21_long_decimal.
shift указывает направление копирования. Если равно 1 - копируется из long в
decimal, иначе - из decimal до long */
void copy_structs(s21_decimal *value_1, s21_long_decimal *value_2, int shift);

/* Возваращет первое вхождение значимого бита в указанной позиции 191 > i > 0*/
int search_bits(s21_long_decimal value);

/* Конвертация числа флоат с дробной частью в структуру децимал */
void float_exp(unsigned int *scale_amount, s21_decimal *dst, float src);

/* Конвертация числа флоат с большой целой частью, без дробной части в структуру
 * децимал с минимальными потерями точности */
void float_nonexp(unsigned int binary_scale, s21_decimal *dst);

/* Вспомогательные функции для работы с экспонентой числа (степенью числа)
 * (scale) */

/* Возвращает экспонету из децнимала */
unsigned int get_exp(s21_decimal value);

/* Очищает степень в структуре, но оставляет знак */
void clear_exp(s21_decimal *value);

/* Нормализация экспоненты. Приведение к общему знаменателю */
void normalize_exp_long(s21_long_decimal *value_1, s21_long_decimal *value_2,
                        unsigned int exp_1, unsigned int exp_2);

/* Округление s21_decimal */
void round_exp(s21_decimal *value, int exp, int needed);

/* Округление s21_long_decimal */
void round_exp_long(s21_long_decimal *value, int exp, int needed);

/* Вспомогательные арифметические функции */

/* Сложение двух структур s21_decimal и запись их в третью.
Сложение выполняется при идеальных условиях, без учёта знака, степени по
указанному количеству битов. Возвращает 1 если число выходит за допустимый
диапазон (переполнение)*/
int add_decimal(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                int max_bits);

/* Сложение двух структур s21_long_decimal и запись их в третью.
Сложение выполняется при идеальных условиях, без учёта знака, степени по
указанному количеству битов. Возвращает 1 если число выходит за допустимый
диапазон (переполнение)*/
int add_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2,
                     s21_long_decimal *result);

/* Вычитание двух структур s21_decimal и запись их в третью.
Вычитание выполняется при идеальных условиях a > b, без учёта знака, степени по
указанному количеству битов */
void sub_decimal(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                 int max_bits);

/* Вычитание двух структур s21_long_decimal и запись из в третью.
Вычитание выполняется при идеальных условиях a > b, без учёта знака, степени по
указанному количеству битов */
void sub_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2,
                      s21_long_decimal *result);

/* Умножает переданную структуру на 10 по указзанному колличеству ячеек
 * указанное колличество раз */
void mul_ten_decimal(s21_decimal *value, const int cells,
                     const int shift_amount);

/* Умножает переданную структуру на 10 по указзанному колличеству ячеек
 * указанное колличество раз */
void mul_ten_long_decimal(s21_long_decimal *value, int shift_amount);

/* Делит переданную структуру на 10 по указанному колличеству битов указанное
 * колличество раз */
void div_ten_decimal(s21_decimal *value, int max_bits, int shift_amount);

/* Делит переданную структуру на 10 по указанному колличеству битов указанное
 * колличество раз */
void div_ten_long_decimal(s21_long_decimal *value, int shift_amount);

/* Основное тело деления. Выполняет деление вычитанием с домножением на 10 при
необходимости. Возвращает 1 если число выходит за допустимый диапазон и число
положительное, или 2 если отрицательное Используется в функции s21_div */
int div_decimal(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/* Арифметические операторы */

// Сложение
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Вычитание
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Деление
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/* Операторы сравнения */

// Меньше ( < )
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

// Меньше или равно ( <= )
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// Больше ( > )
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

// Больше или равно ( >= )
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

// Равно ( == )
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

// Не равно ( != )
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

/* Преобразователи */

// Преобразование из int в decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// Преобразование из float в decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// Преобразование из decimal в int
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// Преобразование из decimal в float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/* Другие функции */

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности
int s21_floor(s21_decimal value, s21_decimal *result);

// Округляет Decimal до ближайшего целого числа
int s21_round(s21_decimal value, s21_decimal *result);

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули
int s21_truncate(s21_decimal value, s21_decimal *result);

// Возвращает результат умножения указанного Decimal на -1
int s21_negate(s21_decimal value, s21_decimal *result);

#endif