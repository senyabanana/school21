#include "controller.h"

CalculatorController::CalculatorController() {
  model = new CalculatorModel();
  creditModel = new Credit();
  depositModel = new Deposit();
}

CalculatorController::~CalculatorController() {
  delete model;
  delete creditModel;
  delete depositModel;
}

double CalculatorController::calculation(string& inputStr, double xValue) {
  return this->model->parser(inputStr, xValue);
}

int CalculatorController::creditCalculation() {
  return this->creditModel->creditCalculation();
}

int CalculatorController::depositCalculation() {
  return this->depositModel->depositCalculation();
}