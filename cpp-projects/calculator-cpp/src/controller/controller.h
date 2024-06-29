#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

using namespace s21;

class CalculatorController {
 private:
  CalculatorModel *model;
  Credit *creditModel;
  Deposit *depositModel;

 public:
  CalculatorController();
  ~CalculatorController();

  double calculation(string &inputStr, double xValue);
  int creditCalculation();
  int depositCalculation();
};

#endif