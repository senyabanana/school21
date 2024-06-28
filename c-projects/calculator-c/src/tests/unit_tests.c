#include <check.h>
#include <math.h>
#include <string.h>

#include "../calculator.h"

START_TEST(banan_calc_test_1) {
  char input[255] = "3+4*2/(1-5)^2";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 3.5);
}
END_TEST

START_TEST(banan_calc_test_2) {
  char input[255] = "1+2+3+4*5*6^7";
  double result = parser(input, 0);
  ck_assert_int_eq((int)result, 5598726);
}
END_TEST

START_TEST(banan_calc_test_3) {
  char input[255] = "123.456+2*3^4";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 285.456);
}
END_TEST

START_TEST(banan_calc_test_4) {
  char input[255] = "(8+2*5)/(1+3*2-4)";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 6);
}
END_TEST

START_TEST(banan_calc_test_5) {
  char input[255] =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 10);
}
END_TEST

START_TEST(banan_calc_test_6) {
  char input[255] = "cos(1*2)-1";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, -1.41614683655, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_7) {
  char input[255] =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, -1.83907152908, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_8) {
  char input[255] = "sin(cos(5))";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, 0.27987335076, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_9) {
  char input[255] = "2.33mod1";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, 0.33, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_10) {
  char input[255] = "3+4*2/1-5+2^2";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, 10, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_11) {
  double x = 0.0003;
  char input[255] = "asin(2*x)";
  double result = parser(input, x);
  ck_assert_double_eq_tol(result, 0.0006000, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_12) {
  double x = 0.0019;
  char input[255] = "acos(2*x)";
  double result = parser(input, x);
  ck_assert_double_eq_tol(result, 1.567, 1e-03);
}
END_TEST

START_TEST(banan_calc_test_13) {
  double x = 0.0019;
  char input[255] = "atan(2*x)";
  double result = parser(input, x);
  ck_assert_double_eq_tol(result, 0.00379998, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_14) {
  double x = 0.004;
  char input[255] = "tan(2*x)";
  double result = parser(input, x);
  ck_assert_double_eq_tol(result, 0.00800017, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_15) {
  double x = 25;
  char input[255] = "sqrt(2*x)";
  double result = parser(input, x);
  ck_assert_double_eq_tol(result, 7.07107, 1e-05);
}
END_TEST

START_TEST(banan_calc_test_16) {
  double x = 2;
  char input[255] = "ln(10*x)";
  double result = parser(input, x);
  ck_assert_double_eq_tol(result, 2.99573, 1e-05);
}
END_TEST

START_TEST(banan_calc_test_17) {
  double x = 2;
  char input[255] = "log(10*x)";
  double result = parser(input, x);
  ck_assert_double_eq_tol(result, 1.30103, 1e-05);
}
END_TEST

START_TEST(banan_calc_test_18) {
  char input[255] = "()";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, 0, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_19) {
  char input[255] = "3-(-3)";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, 6, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_20) {
  char input[255] = "3-(+3)";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, 0, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_21) {
  char input[255] = "2^2^3";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 256);
}
END_TEST

START_TEST(banan_calc_test_22) {
  char input[255] = "-5+2*3";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 1);
}
END_TEST

START_TEST(banan_calc_test_23) {
  char input[255] = "3*-2+6";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 0);
}
END_TEST

START_TEST(banan_calc_test_24) {
  char input[255] = "2^-3+0.875";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 1);
}
END_TEST

START_TEST(banan_calc_test_25) {
  char input[255] = "2*cos(5)+5";
  double result = parser(input, 0);
  ck_assert_double_eq_tol(result, 5.5673244, 1e-07);
}
END_TEST

START_TEST(banan_calc_test_26) {
  char input[256] = "1.25+3.45";
  double result = parser(input, 0);
  ck_assert_float_eq(1.25 + 3.45, result);
}
END_TEST

START_TEST(banan_calc_test_27) {
  char input[256] = "1.25-3.45";
  double result = parser(input, 0);
  ck_assert_float_eq(1.25 - 3.45, result);
}
END_TEST

START_TEST(banan_calc_test_28) {
  char input[256] = "1.25*3.45";
  double result = parser(input, 0);
  ck_assert_float_eq(1.25 * 3.45, result);
}
END_TEST

START_TEST(banan_calc_test_29) {
  char input[256] = "3*(4+7)";
  double result = parser(input, 0);
  ck_assert_float_eq(3 * (4 + 7), result);
}
END_TEST

START_TEST(banan_calc_test_30) {
  char input[256] = "1.25/3.45";
  double result = parser(input, 0);
  ck_assert_float_eq(1.25 / 3.45, result);
}
END_TEST

START_TEST(banan_calc_test_31) {
  char input[256] = "1.25mod3.45";
  double result = parser(input, 0);
  ck_assert_float_eq(fmod(1.25, 3.45), result);
}
END_TEST

START_TEST(banan_calc_test_32) {
  char input[256] = "1.25^3.45";
  double result = parser(input, 0);
  ck_assert_float_eq(powf(1.25, 3.45), result);
}
END_TEST

START_TEST(banan_calc_test_33) {
  char input[256] = "x";
  double result = parser(input, 2.22);
  ck_assert_float_eq(2.22, result);
}
END_TEST

START_TEST(banan_calc_test_34) {
  char input[256] = "(+5.23+1.25)*(0.25+0.001)";
  double result = parser(input, 0);
  ck_assert_float_eq((5.23 + 1.25) * (0.25 + 0.001), result);
}
END_TEST

START_TEST(banan_calc_test_35) {
  char input[256] = "sin((5.23+1.25)*(0.25+0.001))";
  double result = parser(input, 0);
  ck_assert_float_eq(sin((5.23 + 1.25) * (0.25 + 0.001)), result);
}
END_TEST

START_TEST(banan_calc_test_36) {
  char input[256] = "cos((5.23+1.25)*(0.25+0.001))";
  double result = parser(input, 0);
  ck_assert_float_eq(cos((5.23 + 1.25) * (0.25 + 0.001)), result);
}
END_TEST

START_TEST(banan_calc_test_37) {
  char input[256] = "tan((5.23+1.25)*(0.25+0.001))";
  double result = parser(input, 0);
  ck_assert_float_eq(tan((5.23 + 1.25) * (0.25 + 0.001)), result);
}
END_TEST

START_TEST(banan_calc_test_38) {
  char input[256] = "asin(7/7.7)";
  double result = parser(input, 0);
  ck_assert_float_eq(asin(7 / 7.7), result);
}
END_TEST

START_TEST(banan_calc_test_39) {
  char input[256] = "acos(7/7.7)";
  double result = parser(input, 0);
  ck_assert_float_eq(acos(7 / 7.7), result);
}
END_TEST

START_TEST(banan_calc_test_40) {
  char input[256] = "atan(7/7.7)";
  double result = parser(input, 0);
  ck_assert_float_eq(atan(7 / 7.7), result);
}
END_TEST

START_TEST(banan_calc_test_41) {
  char input[256] = "sqrt(1357-245)";
  double result = parser(input, 0);
  ck_assert_float_eq(sqrt(1357 - 245), result);
}
END_TEST

START_TEST(banan_calc_test_42) {
  char input[256] = "ln(1357-245)";
  double result = parser(input, 0);
  ck_assert_float_eq(log(1357 - 245), result);
}
END_TEST

START_TEST(banan_calc_test_43) {
  char input[256] = "log(1357-245)";
  double result = parser(input, 0);
  ck_assert_float_eq(log10(1357 - 245), result);
}
END_TEST

START_TEST(banan_calc_test_44) {
  char input[256] = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
  double result = parser(input, 0);
  ck_assert_float_eq(log10(32 + 1) * 7 / 11 * 432 * (sin(2) * 12 - 45 + 4) / 2,
                     result);
}
END_TEST

START_TEST(banan_calc_test_45) {
  char input[256] = "cos(sin(tan(-0.005)))";
  double result = parser(input, 0);
  ck_assert_float_eq(cos(sin(tan(-0.005))), result);
}
END_TEST

START_TEST(banan_calc_test_46) {
  char input[255] = "(((--2*3";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 6);
}
END_TEST

START_TEST(banan_calc_test_47) {
  char input[255] = "(-1)^2-(-1^2)";
  double result = parser(input, 0);
  ck_assert_double_eq(result, 2);
}
END_TEST

START_TEST(banan_credit_calc_test) {
    Credit a = {0};
    Credit *calc = &a;
    calc->credit_amount = 100000;
    calc->credit_term = 12;
    calc->percent = 5;
    calc->type_of_credit = 0;
    credit_calculator(calc);
    ck_assert_int_eq(102728, (int)calc->total_payout);
    ck_assert_int_eq(2728, (int)calc->overpayment);
    ck_assert_int_eq(8560, (int)calc->monthly_payment[0]);

    calc->credit_amount = 100000;
    calc->credit_term = 12;
    calc->percent = 5;
    calc->type_of_credit = 1;
    credit_calculator(calc);
    ck_assert_int_eq(102708, (int)calc->total_payout);
    ck_assert_int_eq(2708, (int)calc->overpayment);
    ck_assert_int_eq(8750, (int)calc->monthly_payment[0]);
}
END_TEST

START_TEST(banan_deposit_calc_test) {
    Deposit a = {0};
    Deposit *calc = &a;
    calc->deposit_amount = 100000;
    calc->deposit_term = 12;
    calc->percent = 5;
    calc->frequency = 0;
    calc->capitalization = 0;
    calc->tax = 0;
    deposit_calculator(calc);
    ck_assert_int_eq(100000, (int)calc->output_amount);
    ck_assert_int_eq(5000, (int)calc->interest);
    ck_assert_int_eq(0, (int)calc->tax_amount);

    calc->frequency = 0;
    calc->capitalization = 1;
    calc->tax = 0;
    deposit_calculator(calc);
    ck_assert_int_eq(105116, (int)calc->output_amount);
    ck_assert_int_eq(5116, (int)calc->interest);
    ck_assert_int_eq(0, (int)calc->tax_amount);

    calc->percent = 20;
    calc->frequency = 0;
    calc->capitalization = 1;
    calc->tax = 35;
    deposit_calculator(calc);
    ck_assert_int_eq(113803, (int)calc->output_amount);
    ck_assert_int_eq(21236, (int)calc->interest);
    ck_assert_int_eq(7432, (int)calc->tax_amount);

    calc->percent = 20;
    calc->frequency = 1;
    calc->capitalization = 1;
    calc->tax = 35;
    deposit_calculator(calc);
    ck_assert_int_eq(113647, (int)calc->output_amount);
    ck_assert_int_eq(20996, (int)calc->interest);
    ck_assert_int_eq(7348, (int)calc->tax_amount);

    calc->percent = 20;
    calc->frequency = 2;
    calc->capitalization = 1;
    calc->tax = 35;
    deposit_calculator(calc);
    ck_assert_int_eq(113000, (int)calc->output_amount);
    ck_assert_int_eq(20000, (int)calc->interest);
    ck_assert_int_eq(7000, (int)calc->tax_amount);
}
END_TEST

int main() {
  Suite *suite = suite_create("а когда не ранинг:");
  TCase *tc = tcase_create("smart_calc");
  SRunner *srunner = srunner_create(suite);
  int result;
  suite_add_tcase(suite, tc);

  tcase_add_test(tc, banan_calc_test_1);
  tcase_add_test(tc, banan_calc_test_2);
  tcase_add_test(tc, banan_calc_test_3);
  tcase_add_test(tc, banan_calc_test_4);
  tcase_add_test(tc, banan_calc_test_5);
  tcase_add_test(tc, banan_calc_test_6);
  tcase_add_test(tc, banan_calc_test_7);
  tcase_add_test(tc, banan_calc_test_8);
  tcase_add_test(tc, banan_calc_test_9);
  tcase_add_test(tc, banan_calc_test_10);
  tcase_add_test(tc, banan_calc_test_11);
  tcase_add_test(tc, banan_calc_test_12);
  tcase_add_test(tc, banan_calc_test_13);
  tcase_add_test(tc, banan_calc_test_14);
  tcase_add_test(tc, banan_calc_test_15);
  tcase_add_test(tc, banan_calc_test_16);
  tcase_add_test(tc, banan_calc_test_17);
  tcase_add_test(tc, banan_calc_test_18);
  tcase_add_test(tc, banan_calc_test_19);
  tcase_add_test(tc, banan_calc_test_20);
  tcase_add_test(tc, banan_calc_test_21);
  tcase_add_test(tc, banan_calc_test_22);
  tcase_add_test(tc, banan_calc_test_23);
  tcase_add_test(tc, banan_calc_test_24);
  tcase_add_test(tc, banan_calc_test_25);
  tcase_add_test(tc, banan_calc_test_26);
  tcase_add_test(tc, banan_calc_test_27);
  tcase_add_test(tc, banan_calc_test_28);
  tcase_add_test(tc, banan_calc_test_29);
  tcase_add_test(tc, banan_calc_test_30);
  tcase_add_test(tc, banan_calc_test_31);
  tcase_add_test(tc, banan_calc_test_32);
  tcase_add_test(tc, banan_calc_test_33);
  tcase_add_test(tc, banan_calc_test_34);
  tcase_add_test(tc, banan_calc_test_35);
  tcase_add_test(tc, banan_calc_test_36);
  tcase_add_test(tc, banan_calc_test_37);
  tcase_add_test(tc, banan_calc_test_38);
  tcase_add_test(tc, banan_calc_test_39);
  tcase_add_test(tc, banan_calc_test_40);
  tcase_add_test(tc, banan_calc_test_41);
  tcase_add_test(tc, banan_calc_test_42);
  tcase_add_test(tc, banan_calc_test_43);
  tcase_add_test(tc, banan_calc_test_44);
  tcase_add_test(tc, banan_calc_test_45);
  tcase_add_test(tc, banan_calc_test_46);
  tcase_add_test(tc, banan_calc_test_47);
  tcase_add_test(tc, banan_calc_test_47);
  tcase_add_test(tc, banan_credit_calc_test);
  tcase_add_test(tc, banan_deposit_calc_test);

  srunner_run_all(srunner, CK_VERBOSE);
  result = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return result == 0 ? 0 : 1;
}