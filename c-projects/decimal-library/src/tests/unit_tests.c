#include <check.h>
#include <ctype.h>
#include <math.h>

#include "../s21_decimal.h"

START_TEST(s21_add_test_1) {
  s21_decimal src1, src2;
  int a = -1234;
  float b = 1.234;
  float res_our_dec = 0.0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1232.766;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_2) {
  s21_decimal src1, src2;
  int a = -1234;
  float b = -1.234;
  float res_our_dec = 0.0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1235.234;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_3) {
  s21_decimal src1, src2;
  float a = -1234;
  float b = -221.234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1455.234;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_4) {
  s21_decimal src1, src2;
  int a = -1234;
  float b = -221.234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1455.234;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_5) {
  s21_decimal src1, src2;
  float a = -9403;
  float b = 0.00234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -9402.99766;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_6) {
  s21_decimal src1, src2;
  int a = -9403;
  int b = 234;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -9169;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_int(temp, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_7) {
  s21_decimal src1, src2;
  float a = -940.3;
  float b = 0.000234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -940.299766;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_8) {
  s21_decimal src1, src2;
  float a = -0.9403;
  float b = 0.000234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -0.940066;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_9) {
  s21_decimal src1, src2;
  float a = -0.9403;
  float b = 2.0234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1.0831;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq_tol(res_our_dec, res_origin, 1e-6);
}
END_TEST

START_TEST(s21_add_test_10) {
  s21_decimal src1, src2;
  float a = -0.9403;
  float b = -112.0234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -112.9637;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_11) {
  s21_decimal src1, src2;
  float a = -0.94e03;
  float b = -112.0234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1052.0234;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_12) {
  s21_decimal src1, src2;
  float a = -0.94e03;
  float b = -112.0e2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -12140;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_add(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_add_test_13) {
  s21_decimal src1 = {{0x80000000, 0x80000000, 0x80000000, 0}},
              src2 = {{2, 0, 0, 0}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_add(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_add_test_14) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{2, 0, 0, 0x80000000}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_add(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_add_test_15) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{0, 0, 0, 2}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_add(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_add_test_16) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff,
                       0b00000000000000001111111000000000}},
              src2 = {{0xffffffff, 0xffffffff, 0,
                       0b00000000000000001111111000000000}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_add(src1, src2, &temp);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_add_test_17) {
  s21_decimal src1 = {{0xffffffff, 0xffffff00, 0,
                       0b00000000000000001111111000000000}},
              src2 = {{0xffffffff, 0xffffff00, 0,
                       0b00000000000000001111111000000000}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_add(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_sub_test_1) {
  s21_decimal src1, src2;
  int a = 9403;
  int b = 202;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 9201;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &temp);
  s21_from_decimal_to_int(temp, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_test_2) {
  s21_decimal src1, src2;
  int a = 9403;
  float b = 202.098;
  float res_our_dec = 0.0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 9200.902;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_test_3) {
  s21_decimal src1, src2;
  float a = -9403;
  float b = 202.098;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a - b;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_test_4) {
  s21_decimal src1, src2;
  float a = 9403.0;
  float b = 202.09e8;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -20208990597;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_test_5) {
  s21_decimal src1, src2;
  float a = 9403.0e2;
  float b = 202.09e8;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -20208059700;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_test_6) {
  s21_decimal src1, src2;
  float a = -9403.0e2;
  int b = -202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = a - b;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_test_7) {
  s21_decimal src1, src2;
  float a = -94;
  float b = -202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a - b;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_sub(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_sub_test_11) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{2, 0, 0, 0x80000000}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_sub(src1, src2, &temp);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_sub_test_12) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{2, 0x80000000, 0x80000000, 2}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_sub(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_mul_test_1) {
  s21_decimal src1, src2;
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_mul(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_test_2) {
  s21_decimal src1, src2;
  float a = 9403.0e2;
  float b = 9403.0e2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 884164090000;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_mul(src1, src2, &temp);
  s21_from_decimal_to_float(temp, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_test_3) {
  s21_decimal src1, src2;
  int a = 9403;
  int b = 202;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 1899406;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_mul(src1, src2, &temp);
  s21_from_decimal_to_int(temp, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_test_4) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -65536;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_mul(src1, src2, &temp);
  s21_from_decimal_to_int(temp, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_test_5) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_mul(src1, src2, &temp);
  s21_from_decimal_to_int(temp, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_mul_test_9) {
  s21_decimal src1 = {{0x80000000, 0x80000000, 0x80000000, 0}},
              src2 = {{2, 0, 0, 0x80000000}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_mul(src1, src2, &temp);
  ck_assert_int_eq(a, 2);
}
END_TEST

START_TEST(s21_mul_test_10) {
  s21_decimal src1 = {{0x80000000, 0x80000000, 0x80000000, 0}},
              src2 = {{2, 0, 0, 0xffffffff}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_mul(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_mul_test_12) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{2, 0, 0xffffffff, 0}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_mul(src1, src2, &temp);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_div_test_1) {
  s21_decimal src1, src2, res_div;
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 4654.950495049504950495049505;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_2) {
  s21_decimal src1, src2, res_div;
  int a = -32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -16384;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_int(res_div, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_3) {
  s21_decimal src1, src2, res_div;
  float a = -9403.0e2;
  float b = -2020.29;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 465.4282306005573457275935633;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_4) {
  s21_decimal src1, src2, res_div;
  float a = -9403.0e2;
  float b = 2020.29;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -465.4282306005573457275935633;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_5) {
  s21_decimal src1, src2, res_div;
  float a = -9403.0e20;
  float b = 2.28e17;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_6) {
  s21_decimal src1, src2, res_div;
  float a = -0.9;
  float b = 30.323;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_7) {
  s21_decimal src1, src2, res_div;
  float a = -0.9e3;
  float b = 30.32;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_8) {
  s21_decimal src1, src2, res_div;
  float a = -0.9e3;
  int b = 30;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = a / b;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_9) {
  s21_decimal src1, src2, res_div;
  float a = -0.9;
  float b = 0.000076;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  s21_div(src1, src2, &res_div);
  s21_from_decimal_to_float(res_div, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(s21_div_test_10) {
  s21_decimal src1 = {{0, 0, 0, 0}},
              src2 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_div(src2, src1, &temp);
  ck_assert_float_eq(a, 3);
}
END_TEST

START_TEST(s21_div_test_12) {
  s21_decimal src1 = {{0x80000000, 0x80000000, 0x80000000, 0}},
              src2 = {{2, 0, 0, 28 << 16}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_div(src1, src2, &temp);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(s21_div_test_13) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{2, 0, 0xffffffff, 0}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_div(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_div_test_14) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{2, 2, 2, 2}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_div(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_div_test_15) {
  s21_decimal src1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0}},
              src2 = {{0xffffffff, 0xffffffff, 0xffffffff, 28 << 16}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_div(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_div_test_16) {
  s21_decimal src1 = {{1, 0, 0, 28 << 16}}, src2 = {{100000, 0, 0, 0}};
  s21_decimal temp = {{0, 0, 0, 0}};
  int a = s21_div(src1, src2, &temp);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(s21_is_less_test) {
  s21_decimal dst1, dst2;

  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_less(dst1, dst2), 0);  // 1.2345 < 1.2
  ck_assert_int_eq(s21_is_less(dst2, dst1), 1);  // 1.2 < 1.2345

  s21_negate(dst1, &dst1);
  s21_negate(dst2, &dst2);
  ck_assert_int_eq(s21_is_less(dst1, dst2), 1);  // -1.2345 < -1.2
  ck_assert_int_eq(s21_is_less(dst2, dst1), 0);  // -1.2 < -1.2345

  s21_negate(dst1, &dst1);
  ck_assert_int_eq(s21_is_less(dst1, dst2), 0);  //  1.2345 < -1.2 fail
  ck_assert_int_eq(s21_is_less(dst2, dst1), 1);  //  -1.2 < 1.2345 fail

  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_less(dst1, dst2), 0);  // 0 < 0
}
END_TEST

START_TEST(s21_is_less_or_equal_test) {
  s21_decimal dst1, dst2;

  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), 0);  // 1.2345 <= 1.2
  ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), 1);  // 1.2 <= 1.2345

  s21_negate(dst1, &dst1);
  s21_negate(dst2, &dst2);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), 1);  // -1.2345 <= -1.2
  ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), 0);  // -1.2 <= 1.2345

  s21_negate(dst1, &dst1);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2),
                   0);  //  1.2345 <= -1.2 // fail
  ck_assert_int_eq(s21_is_less_or_equal(dst2, dst1), 1);  //  -1.2 <= 1.2345

  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), 1);  // 0 <= 0

  s21_from_float_to_decimal(1726.73, &dst1);
  s21_from_float_to_decimal(1726.73, &dst2);
  ck_assert_int_eq(s21_is_less_or_equal(dst1, dst2), 1);  // 1726.73 <= 1726.73
}
END_TEST

START_TEST(s21_is_greater_test) {
  s21_decimal dst1, dst2;

  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);  // 1.2345 > 1.2
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);  // 1.2 > 1.2345

  s21_negate(dst1, &dst1);
  s21_negate(dst2, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);  // -1.2345 > -1.2
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 1);  // -1.2 > 1.2345

  s21_negate(dst1, &dst1);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);  //  1.2345 > -1.2
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);  //  -1.2 > 1.2345

  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);  // 0 > 0
}
END_TEST

START_TEST(s21_is_greater_or_equal_test) {
  s21_decimal dst1, dst2;

  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2), 1);  // 1.2345 >= 1.2
  ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1), 0);  // 1.2 >= 1.2345

  s21_negate(dst1, &dst1);
  s21_negate(dst2, &dst2);
  ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2), 0);  // -1.2345 >= -1.2
  ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1), 1);  // -1.2 >= 1.2345

  s21_negate(dst1, &dst1);
  ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2),
                   1);  //  1.2345 >= -1.2 // fail
  ck_assert_int_eq(s21_is_greater_or_equal(dst2, dst1), 0);  //  -1.2 >= 1.2345

  s21_from_float_to_decimal(0.0, &dst1);
  s21_from_float_to_decimal(0.0, &dst2);
  ck_assert_int_eq(s21_is_greater_or_equal(dst1, dst2), 1);  // 0 >= 0
}
END_TEST

START_TEST(s21_is_equal_test) {
  s21_decimal dst1, dst2;

  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_equal(dst1, dst2), 0);  // 1.2345 = 1.2

  s21_from_float_to_decimal(-234.17, &dst1);
  s21_from_float_to_decimal(234.17, &dst2);
  ck_assert_int_eq(s21_is_equal(dst1, dst2), 0);

  s21_from_float_to_decimal(234.17, &dst1);
  s21_from_float_to_decimal(234.17, &dst2);
  ck_assert_int_eq(s21_is_equal(dst1, dst2), 1);
}
END_TEST

START_TEST(s21_is_not_equal_test) {
  s21_decimal dst1, dst2;

  s21_from_float_to_decimal(1.2345, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_not_equal(dst1, dst2), 1);  // 1.2345 = 1.2

  s21_from_float_to_decimal(1.2, &dst1);
  s21_from_float_to_decimal(1.2, &dst2);
  ck_assert_int_eq(s21_is_not_equal(dst1, dst2), 0);  // 1.2 = 1.2

  s21_from_float_to_decimal(234.17, &dst1);
  s21_from_float_to_decimal(234.17, &dst2);
  ck_assert_int_eq(s21_is_not_equal(dst1, dst2), 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test) {
  s21_decimal dst1;

  int a = -128, b;
  s21_from_int_to_decimal(a, &dst1);
  s21_from_decimal_to_int(dst1, &b);
  ck_assert_int_eq(a, b);

  a = 0;
  s21_from_int_to_decimal(a, &dst1);
  s21_from_decimal_to_int(dst1, &b);
  ck_assert_int_eq(a, b);

  a = 127;
  s21_from_int_to_decimal(a, &dst1);
  s21_from_decimal_to_int(dst1, &b);
  ck_assert_int_eq(a, b);

  a = -2147483647;
  s21_from_int_to_decimal(a, &dst1);
  s21_from_decimal_to_int(dst1, &b);
  ck_assert_int_eq(a, b);

  a = 2147483647;
  s21_from_int_to_decimal(a, &dst1);
  s21_from_decimal_to_int(dst1, &b);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal dst1;

  float a = 0.3, b;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);

  a = 127.1234;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);

  a = -128.023;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);

  a = -2.1474836E+09;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);

  a = 22.14836E+03;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);

  a = -2147221504;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);

  a = -333.2222;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);

  a = 1.02E+09;
  s21_from_float_to_decimal(a, &dst1);
  s21_from_decimal_to_float(dst1, &b);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_from_float_to_decimal_7) {
  s21_decimal dst1;
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &dst1);
  ck_assert_int_eq(dst1.bits[0], 0);
  ck_assert_int_eq(dst1.bits[1], 0);
  ck_assert_int_eq(dst1.bits[2], 0);
  ck_assert_int_eq(dst1.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_8) {
  s21_decimal dst1;
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &dst1);
  ck_assert_int_eq(dst1.bits[0], 0);
  ck_assert_int_eq(dst1.bits[1], 0);
  ck_assert_int_eq(dst1.bits[2], 0);
  ck_assert_int_eq(dst1.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_9) {
  s21_decimal dst1;
  float a = 0.0 / 0.0;
  int b = s21_from_float_to_decimal(a, &dst1);
  ck_assert_int_eq(dst1.bits[0], 0);
  ck_assert_int_eq(dst1.bits[1], 0);
  ck_assert_int_eq(dst1.bits[2], 0);
  ck_assert_int_eq(dst1.bits[3], 0);
  ck_assert_int_eq(b, 1);
}
END_TEST

START_TEST(s21_floor_test_1) {
  s21_decimal src1, res;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b00000000000010100000000000000000;
  s21_floor(src1, &res);
  s21_decimal result;
  result.bits[0] = 0b10100111011000111111111111111111;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_test_2) {
  s21_decimal src1, res;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_floor(src1, &res);
  s21_decimal result;
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_test_3) {
  s21_decimal src1 = {{123456, 0, 0, (3 << 16) + 0x80000000}}, res;
  float a = 123.45;
  float b = floor(-123.456);
  s21_floor(src1, &res);
  s21_from_decimal_to_float(res, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_floor_test_4) {
  s21_decimal src1, res;
  src1.bits[0] = 0b10010011111100000001110001010010;
  src1.bits[1] = 0b00000000000000000000000100100000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000010100000000000000000;
  s21_floor(src1, &res);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_test_5) {
  s21_decimal src1, res;
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  s21_floor(src1, &res);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_test_6) {
  s21_decimal src1, res;
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000100100000000000000000;
  s21_floor(src1, &res);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_test_7) {
  s21_decimal src1, result;
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000001110000000000000000;
  s21_floor(src1, &result);
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0b00000000000000000000001000010010;
  result_origin.bits[0] = 0b00110110101101101000110000111111;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_round_test_1) {
  s21_decimal src1, src2;
  float a = 4.5;
  float b = 5;
  s21_from_float_to_decimal(a, &src1);
  s21_round(src1, &src2);
  s21_from_decimal_to_float(src2, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal src1, src2;
  float a = 1.0 / 0.0;
  float b = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_round(src1, &src2);
  s21_from_decimal_to_float(src2, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_round_test_3) {
  s21_decimal src1, src2;
  float a = -1.0 / 0.0;
  float b = 0;
  s21_from_float_to_decimal(a, &src1);
  s21_round(src1, &src2);
  s21_from_decimal_to_float(src2, &a);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(s21_truncate_test_1) {
  s21_decimal src1, res;
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_truncate(src1, &res);
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_test_2) {
  s21_decimal src1, res;
  src1.bits[3] = 0x800C0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x80000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x1197998;
  s21_truncate(src1, &res);
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_test_3) {
  s21_decimal src1, res;
  src1.bits[3] = 0x80000000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x80000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0xFFFFFFFF;
  result.bits[0] = 0xFFFFFFFF;
  s21_truncate(src1, &res);
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_test_4) {
  s21_decimal src1, res;
  src1.bits[0] = 0b00000000000000000000000001101101;
  src1.bits[1] = 0b00000000000011000110010101011011;
  src1.bits[2] = 0b00000000000000000011000000111001;
  src1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(src1, &res);
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_test_5) {
  s21_decimal src1, res;
  src1.bits[0] = 0b11011110101001001000000010110110;
  src1.bits[1] = 0b01011111101001011101111110100000;
  src1.bits[2] = 0b00011111111010011010111101100000;
  src1.bits[3] = 0b00000000000010010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00110100101011011100000100111110;
  result.bits[1] = 0b10001001000100001000011110111001;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(src1, &res);
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_test_7) {
  s21_decimal src1, res;
  src1.bits[0] = 0b11010000101000110011000001101101;
  src1.bits[1] = 0b00011111100110100110101101011000;
  src1.bits[2] = 0;
  src1.bits[3] = 0b00000000000010010000000000000000;
  s21_truncate(src1, &res);
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b10000111101111000001011000011110;
  ck_assert_int_eq(result_origin.bits[3], res.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], res.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], res.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], res.bits[0]);
}
END_TEST

START_TEST(s21_truncate_test_8) {
  s21_decimal src1, res;
  src1.bits[0] = 0b01111000101001111011110011000110;
  src1.bits[1] = 0b10011111111111001111101010000100;
  src1.bits[2] = 0b00011111111010011010111101101101;
  src1.bits[3] = 0b00000000000111000000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_truncate(src1, &res);
  ck_assert_float_eq(res.bits[0], result.bits[0]);
  ck_assert_float_eq(res.bits[1], result.bits[1]);
  ck_assert_float_eq(res.bits[2], result.bits[2]);
  ck_assert_float_eq(res.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_negate_test_1) {
  int a = 10;
  int res_a = 0;
  s21_decimal src;
  s21_from_int_to_decimal(a, &src);
  s21_decimal res;
  s21_negate(src, &res);
  s21_from_decimal_to_int(res, &res_a);
  ck_assert_int_eq(-10, res_a);
}
END_TEST

START_TEST(s21_negate_test_2) {
  float a = 10.12345;
  float res_a = 0;
  s21_decimal src;
  s21_from_float_to_decimal(a, &src);
  s21_decimal res;
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-10.12345, res_a);
}
END_TEST

START_TEST(s21_negate_test_3) {
  float a = 10.1234e5;
  float res_a = 0;
  s21_decimal src;
  s21_from_float_to_decimal(a, &src);
  s21_decimal res;
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-10.1234e5, res_a);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("а когда не ранинг");
  SRunner *srunner = srunner_create(suite);

  TCase *s21_add_p_1 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_1);
  tcase_add_test(s21_add_p_1, s21_add_test_1);

  TCase *s21_add_p_2 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_2);
  tcase_add_test(s21_add_p_2, s21_add_test_2);

  TCase *s21_add_p_3 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_3);
  tcase_add_test(s21_add_p_3, s21_add_test_3);

  TCase *s21_add_p_4 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_4);
  tcase_add_test(s21_add_p_4, s21_add_test_4);

  TCase *s21_add_p_5 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_5);
  tcase_add_test(s21_add_p_5, s21_add_test_5);

  TCase *s21_add_p_6 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_6);
  tcase_add_test(s21_add_p_6, s21_add_test_6);

  TCase *s21_add_p_7 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_7);
  tcase_add_test(s21_add_p_7, s21_add_test_7);

  TCase *s21_add_p_8 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_8);
  tcase_add_test(s21_add_p_8, s21_add_test_8);

  TCase *s21_add_p_9 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_9);
  tcase_add_test(s21_add_p_9, s21_add_test_9);

  TCase *s21_add_p_10 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_10);
  tcase_add_test(s21_add_p_10, s21_add_test_10);

  TCase *s21_add_p_11 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_11);
  tcase_add_test(s21_add_p_11, s21_add_test_11);

  TCase *s21_add_p_12 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_12);
  tcase_add_test(s21_add_p_12, s21_add_test_12);

  TCase *s21_add_p_13 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_13);
  tcase_add_test(s21_add_p_13, s21_add_test_13);

  TCase *s21_add_p_14 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_14);
  tcase_add_test(s21_add_p_14, s21_add_test_14);

  TCase *s21_add_p_15 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_15);
  tcase_add_test(s21_add_p_15, s21_add_test_15);

  TCase *s21_add_p_16 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_16);
  tcase_add_test(s21_add_p_16, s21_add_test_16);

  TCase *s21_add_p_17 = tcase_create("s21_add");
  suite_add_tcase(suite, s21_add_p_17);
  tcase_add_test(s21_add_p_17, s21_add_test_17);

  TCase *s21_sub_p_1 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_1);
  tcase_add_test(s21_sub_p_1, s21_sub_test_1);

  TCase *s21_sub_p_2 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_2);
  tcase_add_test(s21_sub_p_2, s21_sub_test_2);

  TCase *s21_sub_p_3 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_3);
  tcase_add_test(s21_sub_p_3, s21_sub_test_3);

  TCase *s21_sub_p_4 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_4);
  tcase_add_test(s21_sub_p_4, s21_sub_test_4);

  TCase *s21_sub_p_5 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_5);
  tcase_add_test(s21_sub_p_5, s21_sub_test_5);

  TCase *s21_sub_p_6 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_6);
  tcase_add_test(s21_sub_p_6, s21_sub_test_6);

  TCase *s21_sub_p_7 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_7);
  tcase_add_test(s21_sub_p_7, s21_sub_test_7);

  TCase *s21_sub_p_11 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_11);
  tcase_add_test(s21_sub_p_11, s21_sub_test_11);

  TCase *s21_sub_p_12 = tcase_create("s21_sub");
  suite_add_tcase(suite, s21_sub_p_12);
  tcase_add_test(s21_sub_p_12, s21_sub_test_12);

  TCase *s21_mul_p_1 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_1);
  tcase_add_test(s21_mul_p_1, s21_mul_test_1);

  TCase *s21_mul_p_2 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_2);
  tcase_add_test(s21_mul_p_2, s21_mul_test_2);

  TCase *s21_mul_p_3 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_3);
  tcase_add_test(s21_mul_p_3, s21_mul_test_3);

  TCase *s21_mul_p_4 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_4);
  tcase_add_test(s21_mul_p_4, s21_mul_test_4);

  TCase *s21_mul_p_5 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_5);
  tcase_add_test(s21_mul_p_5, s21_mul_test_5);

  TCase *s21_mul_p_9 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_9);
  tcase_add_test(s21_mul_p_9, s21_mul_test_9);

  TCase *s21_mul_p_10 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_10);
  tcase_add_test(s21_mul_p_10, s21_mul_test_10);

  TCase *s21_mul_p_12 = tcase_create("s21_mul");
  suite_add_tcase(suite, s21_mul_p_12);
  tcase_add_test(s21_mul_p_12, s21_mul_test_12);

  TCase *s21_div_p_1 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_1);
  tcase_add_test(s21_div_p_1, s21_div_test_1);

  TCase *s21_div_p_2 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_2);
  tcase_add_test(s21_div_p_2, s21_div_test_2);

  TCase *s21_div_p_3 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_3);
  tcase_add_test(s21_div_p_3, s21_div_test_3);

  TCase *s21_div_p_4 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_4);
  tcase_add_test(s21_div_p_4, s21_div_test_4);

  TCase *s21_div_p_5 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_5);
  tcase_add_test(s21_div_p_5, s21_div_test_5);

  TCase *s21_div_p_6 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_6);
  tcase_add_test(s21_div_p_6, s21_div_test_6);

  TCase *s21_div_p_7 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_7);
  tcase_add_test(s21_div_p_7, s21_div_test_7);

  TCase *s21_div_p_8 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_8);
  tcase_add_test(s21_div_p_8, s21_div_test_8);

  TCase *s21_div_p_9 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_9);
  tcase_add_test(s21_div_p_9, s21_div_test_9);

  TCase *s21_div_p_10 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_10);
  tcase_add_test(s21_div_p_10, s21_div_test_10);

  TCase *s21_div_p_12 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_12);
  tcase_add_test(s21_div_p_12, s21_div_test_12);

  TCase *s21_div_p_13 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_13);
  tcase_add_test(s21_div_p_13, s21_div_test_13);

  TCase *s21_div_p_14 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_14);
  tcase_add_test(s21_div_p_14, s21_div_test_14);

  TCase *s21_div_p_15 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_15);
  tcase_add_test(s21_div_p_15, s21_div_test_15);

  TCase *s21_div_p_16 = tcase_create("s21_div");
  suite_add_tcase(suite, s21_div_p_16);
  tcase_add_test(s21_div_p_16, s21_div_test_16);

  TCase *s21_is_less_p = tcase_create("s21_is_less");
  suite_add_tcase(suite, s21_is_less_p);
  tcase_add_test(s21_is_less_p, s21_is_less_test);

  TCase *s21_is_less_or_equal_p = tcase_create("s21_is_less_or_equal");
  suite_add_tcase(suite, s21_is_less_or_equal_p);
  tcase_add_test(s21_is_less_or_equal_p, s21_is_less_or_equal_test);

  TCase *s21_is_greater_p = tcase_create("s21_is_greater");
  suite_add_tcase(suite, s21_is_greater_p);
  tcase_add_test(s21_is_greater_p, s21_is_greater_test);

  TCase *s21_is_greater_or_equal_p = tcase_create("s21_is_greater_or_equal");
  suite_add_tcase(suite, s21_is_greater_or_equal_p);
  tcase_add_test(s21_is_greater_or_equal_p, s21_is_greater_or_equal_test);

  TCase *s21_is_equal_p = tcase_create("s21_is_equal");
  suite_add_tcase(suite, s21_is_equal_p);
  tcase_add_test(s21_is_equal_p, s21_is_equal_test);

  TCase *s21_is_not_equal_p = tcase_create("s21_is_not_equal");
  suite_add_tcase(suite, s21_is_not_equal_p);
  tcase_add_test(s21_is_not_equal_p, s21_is_not_equal_test);

  TCase *s21_from_int_to_decimal_p = tcase_create("s21_from_int_to_decimal_p");
  suite_add_tcase(suite, s21_from_int_to_decimal_p);
  tcase_add_test(s21_from_int_to_decimal_p, s21_from_int_to_decimal_test);

  TCase *s21_from_float_to_decimal_p =
      tcase_create("s21_from_float_to_decimal_p");
  suite_add_tcase(suite, s21_from_float_to_decimal_p);
  tcase_add_test(s21_from_float_to_decimal_p, s21_from_float_to_decimal_1);

  TCase *s21_from_float_to_decimal_p_7 =
      tcase_create("s21_from_float_to_decimal_p_7");
  suite_add_tcase(suite, s21_from_float_to_decimal_p_7);
  tcase_add_test(s21_from_float_to_decimal_p_7, s21_from_float_to_decimal_7);

  TCase *s21_from_float_to_decimal_p_8 =
      tcase_create("s21_from_float_to_decimal_p_8");
  suite_add_tcase(suite, s21_from_float_to_decimal_p_8);
  tcase_add_test(s21_from_float_to_decimal_p_8, s21_from_float_to_decimal_8);

  TCase *s21_from_float_to_decimal_p_9 =
      tcase_create("s21_from_float_to_decimal_p_9");
  suite_add_tcase(suite, s21_from_float_to_decimal_p_9);
  tcase_add_test(s21_from_float_to_decimal_p_9, s21_from_float_to_decimal_9);

  TCase *s21_floor_p_1 = tcase_create("s21_floor");
  suite_add_tcase(suite, s21_floor_p_1);
  tcase_add_test(s21_floor_p_1, s21_floor_test_1);

  TCase *s21_floor_p_2 = tcase_create("s21_floor");
  suite_add_tcase(suite, s21_floor_p_2);
  tcase_add_test(s21_floor_p_2, s21_floor_test_2);

  TCase *s21_floor_p_3 = tcase_create("s21_floor");
  suite_add_tcase(suite, s21_floor_p_3);
  tcase_add_test(s21_floor_p_3, s21_floor_test_3);

  TCase *s21_floor_p_4 = tcase_create("s21_floor");
  suite_add_tcase(suite, s21_floor_p_4);
  tcase_add_test(s21_floor_p_4, s21_floor_test_4);

  TCase *s21_floor_p_5 = tcase_create("s21_floor");
  suite_add_tcase(suite, s21_floor_p_5);
  tcase_add_test(s21_floor_p_5, s21_floor_test_5);

  TCase *s21_floor_p_6 = tcase_create("s21_floor");
  suite_add_tcase(suite, s21_floor_p_6);
  tcase_add_test(s21_floor_p_6, s21_floor_test_6);

  TCase *s21_floor_p_7 = tcase_create("s21_floor");
  suite_add_tcase(suite, s21_floor_p_7);
  tcase_add_test(s21_floor_p_7, s21_floor_test_7);

  TCase *s21_round_p_1 = tcase_create("s21_round");
  suite_add_tcase(suite, s21_round_p_1);
  tcase_add_test(s21_round_p_1, s21_round_test_1);

  TCase *s21_round_p_2 = tcase_create("s21_round");
  suite_add_tcase(suite, s21_round_p_2);
  tcase_add_test(s21_round_p_2, s21_round_test_2);

  TCase *s21_round_p_3 = tcase_create("s21_round");
  suite_add_tcase(suite, s21_round_p_3);
  tcase_add_test(s21_round_p_3, s21_round_test_3);

  TCase *s21_truncate_p_1 = tcase_create("s21_truncate");
  suite_add_tcase(suite, s21_truncate_p_1);
  tcase_add_test(s21_truncate_p_1, s21_truncate_test_1);

  TCase *s21_truncate_p_2 = tcase_create("s21_truncate");
  suite_add_tcase(suite, s21_truncate_p_2);
  tcase_add_test(s21_truncate_p_2, s21_truncate_test_2);

  TCase *s21_truncate_p_3 = tcase_create("s21_truncate");
  suite_add_tcase(suite, s21_truncate_p_3);
  tcase_add_test(s21_truncate_p_3, s21_truncate_test_3);

  TCase *s21_truncate_p_4 = tcase_create("s21_truncate");
  suite_add_tcase(suite, s21_truncate_p_4);
  tcase_add_test(s21_truncate_p_4, s21_truncate_test_4);

  TCase *s21_truncate_p_5 = tcase_create("s21_truncate");
  suite_add_tcase(suite, s21_truncate_p_5);
  tcase_add_test(s21_truncate_p_5, s21_truncate_test_5);

  TCase *s21_truncate_p_7 = tcase_create("s21_truncate");
  suite_add_tcase(suite, s21_truncate_p_7);
  tcase_add_test(s21_truncate_p_7, s21_truncate_test_7);

  TCase *s21_truncate_p_8 = tcase_create("s21_truncate");
  suite_add_tcase(suite, s21_truncate_p_8);
  tcase_add_test(s21_truncate_p_8, s21_truncate_test_8);

  TCase *s21_negate_p_1 = tcase_create("s21_negate");
  suite_add_tcase(suite, s21_negate_p_1);
  tcase_add_test(s21_negate_p_1, s21_negate_test_1);

  TCase *s21_negate_p_2 = tcase_create("s21_negate");
  suite_add_tcase(suite, s21_negate_p_2);
  tcase_add_test(s21_negate_p_2, s21_negate_test_2);

  TCase *s21_negate_p_3 = tcase_create("s21_negate");
  suite_add_tcase(suite, s21_negate_p_3);
  tcase_add_test(s21_negate_p_3, s21_negate_test_3);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}