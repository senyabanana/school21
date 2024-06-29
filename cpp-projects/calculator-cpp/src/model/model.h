#ifndef MODEL_H
#define MODEL_H

#include <array>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {

using std::array;
using std::stack;
using std::string;

typedef enum class OperationType {
  NUMBER = 1,
  X,
  PLUS,
  MINUS,
  MUL,
  DIV,
  POW,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  UNARY_MINUS
} OperationType;

typedef enum class PriorityType {
  BRACKET = -1,
  NUM,
  LOW,
  MIDDLE,
  HIGH
} PriorityType;

class StackItem {
 public:
  StackItem(double value, OperationType type, PriorityType priority)
      : value(value), type(type), priority(priority) {}
  double getValue() const { return value; }
  OperationType getType() const { return type; }
  PriorityType getPriority() const { return priority; }

 private:
  double value;
  OperationType type;
  PriorityType priority;
};

class CalculatorModel {
 private:
  stack<StackItem> inputStack;

  void pushStack(double value, OperationType type, PriorityType priority);
  double binaryOperation(double a, double b, OperationType operation);
  double unaryOperation(double a, OperationType operation);

 public:
  CalculatorModel(){};
  ~CalculatorModel(){};

  double parser(string& inputStr, double xValue);
  double calculation();
  void shantingYard();
  void reverseStack();
  void numbersToStr(string& tempStr, char sym, bool& isNumber,
                    int& tempStrIndex);
  void checkNumbers(string& tempStr, bool& isNumber, int& tempStrIndex);
  void operations(string& tempStr, char mathOperator, bool& isNumber,
                  int& tempStrIndex, size_t& i, string& inputStr);
  void functions(char function, string& inputStr, size_t& i);
  bool arithmetic(StackItem stack);
  bool triganometry(StackItem stack);
};

typedef enum class CreditType { ANNUNITY, DIFFERENTIATED } CreditType;

class Credit {
 public:
  Credit(){};
  ~Credit(){};

  Credit(double amount, double percent, int term, CreditType type)
      : creditAmount(amount), percent(percent), creditTerm(term), type(type) {}
  int creditCalculation();
  double getMonthlyPayment(int index) const { return monthlyPayment[index]; }
  double getOverpayment() const { return overpayment; }
  double getTotalPayout() const { return totalPayout; }
  CreditType getType() const { return type; }
  int getCreditTerm() const { return creditTerm; }
  void setCreditAmount(double a) { creditAmount = a; }
  void setPercent(double p) { percent = p; }
  void setCreditTerm(double ct) { creditTerm = ct; }
  void setType(CreditType ct) { type = ct; }

 private:
  double creditAmount;
  double percent;
  int creditTerm;
  CreditType type;
  array<double, 600> monthlyPayment = {0.0};
  double overpayment = 0;
  double totalPayout = 0;
};

typedef enum class Frequency { MONTHLY, QUARTERLY, ANNUAL } Frequency;

class Deposit {
 public:
  Deposit(){};
  ~Deposit(){};

  Deposit(double amount, double percent, double tax, int term,
          Frequency frequency, bool capitalization)
      : depositAmount(amount),
        percent(percent),
        taxRate(tax),
        depositTerm(term),
        frequency(frequency),
        capitalization(capitalization) {}
  int depositCalculation();
  double getInterest() const { return interest; }
  double getTaxAmount() const { return taxAmount; }
  double getOutputAmount() const { return outputAmount; }
  void setDepositAmount(double a) { depositAmount = a; }
  void setPercent(double p) { percent = p; }
  void setTax(double t) { taxRate = t; }
  void setDepositTerm(int dt) { depositTerm = dt; }
  void setFrequency(Frequency fre) { frequency = fre; }
  void setCapitalization(bool cap) { capitalization = cap; }
  void setAddListValue(int index, double value) { addList[index] = value; }
  void setWithdrawalsList(int index, double value) {
    withdrawalsList[index] = value;
  }

 private:
  double depositAmount = 0;
  double percent = 0;
  double taxRate = 0;
  int depositTerm = 0;
  Frequency frequency;
  bool capitalization;
  array<double, 600> addList = {0.0};
  array<double, 600> withdrawalsList = {0.0};
  double interest = 0;
  double taxAmount = 0;
  double outputAmount = 0;
};
}  // namespace s21

#endif
