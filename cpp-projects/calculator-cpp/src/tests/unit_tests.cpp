#include <gtest/gtest.h>

#include <cmath>

#include "../controller/controller.h"

using namespace s21;
using std::string;

TEST(BananCalcTest, Test1) {
  CalculatorModel CalculatorModel;
  string input = "3+4*2/(1-5)^2";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_DOUBLE_EQ(result, 3.5);
}

TEST(BananCalcTest, Test2) {
  CalculatorModel CalculatorModel;
  string input = "1+2+3+4*5*6^7";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_EQ((int)result, 5598726);
}

TEST(BananCalcTest, Test3) {
  CalculatorModel CalculatorModel;
  string input = "123.456+2*3^4";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_DOUBLE_EQ(result, 285.456);
}

TEST(BananCalcTest, Test4) {
  CalculatorModel CalculatorModel;
  string input = "(8+2*5)/(1+3*2-4)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_DOUBLE_EQ(result, 6);
}

TEST(BananCalcTest, Test5) {
  CalculatorModel CalculatorModel;
  string input =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_DOUBLE_EQ(result, 10);
}

TEST(BananCalcTest, Test6) {
  CalculatorModel CalculatorModel;
  string input = "cos(1*2)-1";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, -1.41614683655, 1e-07);
}

TEST(BananCalcTest, Test7) {
  CalculatorModel CalculatorModel;
  string input =
      "cos(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/"
      "2)))-1";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, -1.83907152908, 1e-07);
}

TEST(BananCalcTest, Test8) {
  CalculatorModel CalculatorModel;
  string input = "sin(cos(5))";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 0.27987335076, 1e-07);
}

TEST(BananCalcTest, Test9) {
  CalculatorModel CalculatorModel;
  string input = "2.33mod1";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 0.33, 1e-07);
}

TEST(BananCalcTest, Test10) {
  CalculatorModel CalculatorModel;
  string input = "3+4*2/1-5+2^2";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 10, 1e-07);
}

TEST(BananCalcTest, Test11) {
  CalculatorModel CalculatorModel;
  double x = 0.0003;
  string input = "asin(2*x)";
  double result = CalculatorModel.parser(input, x);
  EXPECT_NEAR(result, asin(2 * x), 1e-07);
}

TEST(BananCalcTest, Test12) {
  CalculatorModel CalculatorModel;
  double x = 0.0019;
  string input = "acos(2*x)";
  double result = CalculatorModel.parser(input, x);
  EXPECT_NEAR(result, 1.567, 1e-03);
}

TEST(BananCalcTest, Test13) {
  CalculatorModel CalculatorModel;
  double x = 0.0019;
  string input = "atan(2*x)";
  double result = CalculatorModel.parser(input, x);
  EXPECT_NEAR(result, 0.00379998, 1e-07);
}

TEST(BananCalcTest, Test14) {
  CalculatorModel CalculatorModel;
  double x = 0.004;
  string input = "tan(2*x)";
  double result = CalculatorModel.parser(input, x);
  EXPECT_NEAR(result, 0.00800017, 1e-07);
}

TEST(BananCalcTest, Test15) {
  CalculatorModel CalculatorModel;
  double x = 25;
  string input = "sqrt(2*x)";
  double result = CalculatorModel.parser(input, x);
  EXPECT_NEAR(result, 7.07107, 1e-05);
}

TEST(BananCalcTest, Test16) {
  CalculatorModel CalculatorModel;
  double x = 2;
  string input = "ln(10*x)";
  double result = CalculatorModel.parser(input, x);
  EXPECT_NEAR(result, 2.99573, 1e-05);
}

TEST(BananCalcTest, Test17) {
  CalculatorModel CalculatorModel;
  double x = 2;
  string input = "log(10*x)";
  double result = CalculatorModel.parser(input, x);
  EXPECT_NEAR(result, 1.30103, 1e-05);
}

TEST(BananCalcTest, Test18) {
  CalculatorModel CalculatorModel;
  string input = "()";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 0, 1e-07);
}

TEST(BananCalcTest, Test19) {
  CalculatorModel CalculatorModel;
  string input = "3-(-3)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 6, 1e-07);
}

TEST(BananCalcTest, Test20) {
  CalculatorModel CalculatorModel;
  string input = "3-(+3)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 0, 1e-07);
}

TEST(BananCalcTest, Test21) {
  CalculatorModel CalculatorModel;
  string input = "2^2^3";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_DOUBLE_EQ(result, 256);
}

TEST(BananCalcTest, Test22) {
  CalculatorModel CalculatorModel;
  string input = "-5+2*3";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 1, 1e-07);
}

TEST(BananCalcTest, Test23) {
  CalculatorModel CalculatorModel;
  string input = "3*-2+6";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 0, 1e-07);
}

TEST(BananCalcTest, Test24) {
  CalculatorModel CalculatorModel;
  string input = "2^-3+0.875";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 1, 1e-07);
}

TEST(BananCalcTest, Test25) {
  CalculatorModel CalculatorModel;
  string input = "2*cos(5)+5";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_NEAR(result, 5.5673244, 1e-07);
}

TEST(BananCalcTest, Test26) {
  CalculatorModel CalculatorModel;
  string input = "1.25+3.45";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(1.25 + 3.45, result);
}

TEST(BananCalcTest, Test27) {
  CalculatorModel CalculatorModel;
  string input = "1.25-3.45";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(1.25 - 3.45, result);
}

TEST(BananCalcTest, Test28) {
  CalculatorModel CalculatorModel;
  string input = "1.25*3.45";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(1.25 * 3.45, result);
}

TEST(BananCalcTest, Test29) {
  CalculatorModel CalculatorModel;
  string input = "3*(4+7)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(3 * (4 + 7), result);
}

TEST(BananCalcTest, Test30) {
  CalculatorModel CalculatorModel;
  string input = "1.25/3.45";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(1.25 / 3.45, result);
}

TEST(BananCalcTest, Test31) {
  CalculatorModel CalculatorModel;
  string input = "1.25mod3.45";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(fmod(1.25, 3.45), result);
}

TEST(BananCalcTest, Test32) {
  CalculatorModel CalculatorModel;
  string input = "1.25^3.45";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(powf(1.25, 3.45), result);
}

TEST(BananCalcTest, Test33) {
  CalculatorModel CalculatorModel;
  string input = "x";
  double result = CalculatorModel.parser(input, 2.22);
  EXPECT_FLOAT_EQ(2.22, result);
}

TEST(BananCalcTest, Test34) {
  CalculatorModel CalculatorModel;
  string input = "(+5.23+1.25)*(0.25+0.001)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ((5.23 + 1.25) * (0.25 + 0.001), result);
}

TEST(BananCalcTest, Test35) {
  CalculatorModel CalculatorModel;
  string input = "sin((5.23+1.25)*(0.25+0.001))";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(sin((5.23 + 1.25) * (0.25 + 0.001)), result);
}

TEST(BananCalcTest, Test36) {
  CalculatorModel CalculatorModel;
  string input = "cos((5.23+1.25)*(0.25+0.001))";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(cos((5.23 + 1.25) * (0.25 + 0.001)), result);
}

TEST(BananCalcTest, Test37) {
  CalculatorModel CalculatorModel;
  string input = "tan((5.23+1.25)*(0.25+0.001))";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(tan((5.23 + 1.25) * (0.25 + 0.001)), result);
}

TEST(BananCalcTest, Test38) {
  CalculatorModel CalculatorModel;
  string input = "asin(7/7.7)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(asin(7 / 7.7), result);
}

TEST(BananCalcTest, Test39) {
  CalculatorModel CalculatorModel;
  string input = "acos(7/7.7)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(acos(7 / 7.7), result);
}

TEST(BananCalcTest, Test40) {
  CalculatorModel CalculatorModel;
  string input = "atan(7/7.7)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(atan(7 / 7.7), result);
}

TEST(BananCalcTest, Test41) {
  CalculatorModel CalculatorModel;
  string input = "sqrt(1357-245)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(sqrt(1357 - 245), result);
}

TEST(BananCalcTest, Test42) {
  CalculatorModel CalculatorModel;
  string input = "ln(1357-245)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(log(1357 - 245), result);
}

TEST(BananCalcTest, Test43) {
  CalculatorModel CalculatorModel;
  string input = "log(1357-245)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(log10(1357 - 245), result);
}

TEST(BananCalcTest, Test44) {
  CalculatorModel CalculatorModel;
  string input = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(log10(32 + 1) * 7 / 11 * 432 * (sin(2) * 12 - 45 + 4) / 2,
                  result);
}

TEST(BananCalcTest, Test45) {
  CalculatorModel CalculatorModel;
  string input = "cos(sin(tan(-0.005)))";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_FLOAT_EQ(cos(sin(tan(-0.005))), result);
}

TEST(BananCalcTest, Test46) {
  CalculatorModel CalculatorModel;
  string input = "(((--2*3";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_DOUBLE_EQ(result, 6);
}

TEST(BananCalcTest, Test47) {
  CalculatorModel CalculatorModel;
  string input = "(-1)^2-(-1^2)";
  double result = CalculatorModel.parser(input, 0);
  EXPECT_DOUBLE_EQ(result, 2);
}

TEST(CreditCalculatorTest, AnnuityCredit) {
  Credit a(100000, 5, 12, CreditType::ANNUNITY);
  a.creditCalculation();
  EXPECT_EQ(102728, static_cast<int>(a.getTotalPayout()));
  EXPECT_EQ(2728, static_cast<int>(a.getOverpayment()));
  EXPECT_EQ(8560, static_cast<int>(a.getMonthlyPayment(0)));
}

TEST(CreditCalculatorTest, DifferentiatedCredit) {
  Credit b(100000, 5, 12, CreditType::DIFFERENTIATED);
  b.creditCalculation();
  EXPECT_EQ(102708, static_cast<int>(b.getTotalPayout()));
  EXPECT_EQ(2708, static_cast<int>(b.getOverpayment()));
  EXPECT_EQ(8750, static_cast<int>(b.getMonthlyPayment(0)));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
