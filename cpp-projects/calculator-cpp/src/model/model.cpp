#include "model.h"

using namespace s21;

double CalculatorModel::parser(string& inputStr, double xValue) {
  double result = 0;
  string tempStr;
  size_t strLenght = inputStr.length();
  int tempStrIndex = 0;
  bool isNumber = false;
  for (size_t i = 0; i < strLenght; i++) {
    switch (inputStr[i]) {
      case 'x':
        pushStack(xValue, OperationType::X, PriorityType::NUM);
        break;
      case '.':
      case '0' ... '9':
        numbersToStr(tempStr, inputStr[i], isNumber, tempStrIndex);
        break;
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case 'm':
        operations(tempStr, inputStr[i], isNumber, tempStrIndex, i, inputStr);
        break;
      case 'c':
      case 's':
      case 't':
      case 'a':
      case 'l':
        functions(inputStr[i], inputStr, i);
        break;
      case '(':
        pushStack(0, OperationType::LEFT_BRACKET, PriorityType::BRACKET);
        break;
      case ')':
        checkNumbers(tempStr, isNumber, tempStrIndex);
        pushStack(0, OperationType::RIGHT_BRACKET, PriorityType::BRACKET);
        break;
      default:
        checkNumbers(tempStr, isNumber, tempStrIndex);
        break;
    }
  }
  if (!tempStr.empty()) {
    checkNumbers(tempStr, isNumber, tempStrIndex);
  }
  reverseStack();
  shantingYard();
  reverseStack();
  result = calculation();
  return result;
}

void CalculatorModel::shantingYard() {
  stack<StackItem> output;
  stack<StackItem> support;
  while (!inputStack.empty()) {
    StackItem currentItem = inputStack.top();
    inputStack.pop();
    if (currentItem.getType() == OperationType::NUMBER ||
        currentItem.getType() == OperationType::X) {
      output.push(currentItem);
    } else if (currentItem.getType() == OperationType::LEFT_BRACKET ||
               triganometry(currentItem) ||
               currentItem.getType() == OperationType::UNARY_MINUS) {
      support.push(currentItem);
    } else if (arithmetic(currentItem)) {
      while (!support.empty() &&
             currentItem.getPriority() <= support.top().getPriority() &&
             currentItem.getType() != OperationType::POW) {
        output.push(support.top());
        support.pop();
      }
      support.push(currentItem);
    } else if (currentItem.getType() == OperationType::RIGHT_BRACKET) {
      while (support.top().getType() != OperationType::LEFT_BRACKET) {
        output.push(support.top());
        support.pop();
      }
      support.pop();
      if (!support.empty() && triganometry(support.top())) {
        output.push(support.top());
        support.pop();
      }
    }
  }
  while (!support.empty()) {
    output.push(support.top());
    support.pop();
  }
  std::swap(inputStack, output);
}

double CalculatorModel::calculation() {
  stack<double> support;
  double result = 0;
  double a = 0;
  double b = 0;
  int operandCount = 2;
  while (!inputStack.empty()) {
    StackItem currentItem = inputStack.top();
    inputStack.pop();
    if (currentItem.getPriority() == PriorityType::NUM) {
      support.push(currentItem.getValue());
    } else if (currentItem.getType() == OperationType::UNARY_MINUS) {
      double temp = support.top();
      support.pop();
      support.push(-temp);
    } else if (currentItem.getPriority() > PriorityType::NUM &&
               currentItem.getType() < OperationType::COS) {
      while (!support.empty()) {
        if (operandCount == 2) {
          b = support.top();
        } else if (operandCount == 1) {
          a = support.top();
        } else {
          break;
        }
        operandCount--;
        support.pop();
      }
      if (operandCount == 0) {
        support.push(binaryOperation(a, b, currentItem.getType()));
      }
      operandCount = 2;
    } else if (currentItem.getPriority() > PriorityType::NUM &&
               currentItem.getType() > OperationType::MOD &&
               currentItem.getType() < OperationType::LEFT_BRACKET) {
      while (!support.empty()) {
        if (operandCount == 2) {
          b = support.top();
        } else if (operandCount == 1) {
          break;
        }
        operandCount--;
        support.pop();
      }
      if (operandCount == 1) {
        support.push(unaryOperation(b, currentItem.getType()));
      }
      operandCount = 2;
    }
  }
  if (!support.empty()) {
    result = support.top();
  }
  return result;
}

void CalculatorModel::pushStack(double value, OperationType type,
                                PriorityType priority) {
  inputStack.push({value, type, priority});
}

void CalculatorModel::reverseStack() {
  stack<StackItem> newStack;
  while (!inputStack.empty()) {
    newStack.push(inputStack.top());
    inputStack.pop();
  }
  std::swap(inputStack, newStack);
}

void CalculatorModel::operations(string& tempStr, char mathOperartor,
                                 bool& isNumber, int& tempStrIndex, size_t& i,
                                 string& inputStr) {
  switch (mathOperartor) {
    case '+':
      if (inputStr[i - 1] == '(') {
        tempStr[tempStrIndex++] = mathOperartor;
      } else {
        checkNumbers(tempStr, isNumber, tempStrIndex);
        pushStack(0, OperationType::PLUS, PriorityType::LOW);
      }
      break;
    case '-':
      if (i == 0 || strchr("(+-*/^m", inputStr[i - 1])) {
        pushStack(0, OperationType::UNARY_MINUS, PriorityType::HIGH);
      } else {
        checkNumbers(tempStr, isNumber, tempStrIndex);
        pushStack(0, OperationType::MINUS, PriorityType::LOW);
      }
      break;
    case '*':
      checkNumbers(tempStr, isNumber, tempStrIndex);
      pushStack(0, OperationType::MUL, PriorityType::MIDDLE);
      break;
    case '/':
      checkNumbers(tempStr, isNumber, tempStrIndex);
      pushStack(0, OperationType::DIV, PriorityType::MIDDLE);
      break;
    case '^':
      checkNumbers(tempStr, isNumber, tempStrIndex);
      pushStack(0, OperationType::POW, PriorityType::HIGH);
      break;
    case 'm':
      if (inputStr[i + 1] == 'o' ? inputStr[i + 2] == 'd' ? 1 : 0 : 0) {
        i += 2;
        checkNumbers(tempStr, isNumber, tempStrIndex);
        pushStack(0, OperationType::MOD, PriorityType::HIGH);
      }
      break;
  }
}

void CalculatorModel::functions(char function, string& inputStr, size_t& i) {
  switch (function) {
    case 'c':
      if (inputStr[i + 1] == 'o' ? inputStr[i + 2] == 's' ? 1 : 0 : 0) {
        i += 2;
        pushStack(0, OperationType::COS, PriorityType::HIGH);
      }
      break;
    case 's':
      if (inputStr[i + 1] == 'i' ? inputStr[i + 2] == 'n' ? 1 : 0 : 0) {
        i += 2;
        pushStack(0, OperationType::SIN, PriorityType::HIGH);
      }
      if (inputStr[i + 1] == 'q'
              ? inputStr[i + 2] == 'r' ? inputStr[i + 3] == 't' ? 1 : 0 : 0
              : 0) {
        i += 3;
        pushStack(0, OperationType::SQRT, PriorityType::HIGH);
      }
      break;
    case 't':
      if (inputStr[i + 1] == 'a' ? inputStr[i + 2] == 'n' ? 1 : 0 : 0) {
        i += 2;
        pushStack(0, OperationType::TAN, PriorityType::HIGH);
      }
      break;
    case 'a':
      if (inputStr[i + 1] == 'c'
              ? inputStr[i + 2] == 'o' ? inputStr[i + 3] == 's' ? 1 : 0 : 0
              : 0) {
        i += 3;
        pushStack(0, OperationType::ACOS, PriorityType::HIGH);
      }
      if (inputStr[i + 1] == 's'
              ? inputStr[i + 2] == 'i' ? inputStr[i + 3] == 'n' ? 1 : 0 : 0
              : 0) {
        i += 3;
        pushStack(0, OperationType::ASIN, PriorityType::HIGH);
      }
      if (inputStr[i + 1] == 't'
              ? inputStr[i + 2] == 'a' ? inputStr[i + 3] == 'n' ? 1 : 0 : 0
              : 0) {
        i += 3;
        pushStack(0, OperationType::ATAN, PriorityType::HIGH);
      }
      break;
    case 'l':
      if (inputStr[i + 1] == 'n' ? 1 : 0) {
        i += 1;
        pushStack(0, OperationType::LN, PriorityType::HIGH);
      }
      if (inputStr[i + 1] == 'o' ? inputStr[i + 2] == 'g' ? 1 : 0 : 0) {
        i += 2;
        pushStack(0, OperationType::LOG, PriorityType::HIGH);
      }
      break;
  }
}

void CalculatorModel::numbersToStr(string& tempStr, char sym, bool& isNumber,
                                   int& tempStrIndex) {
  tempStr.push_back(sym);
  tempStrIndex++;
  isNumber = true;
}

void CalculatorModel::checkNumbers(string& tempStr, bool& isNumber,
                                   int& tempStrIndex) {
  if (isNumber && !tempStr.empty()) {
    pushStack(std::stod(tempStr), OperationType::NUMBER, PriorityType::NUM);
    tempStr.clear();
    tempStrIndex = 0;
    isNumber = false;
  }
}

double CalculatorModel::binaryOperation(double a, double b,
                                        OperationType operation) {
  switch (operation) {
    case OperationType::PLUS:
      return a + b;
    case OperationType::MINUS:
      return a - b;
    case OperationType::MUL:
      return a * b;
    case OperationType::DIV:
      return a / b;
    case OperationType::POW:
      return pow(a, b);
    case OperationType::MOD:
      return fmod(a, b);
    default:
      return 0;
  }
}

double CalculatorModel::unaryOperation(double a, OperationType operation) {
  switch (operation) {
    case OperationType::COS:
      return cos(a);
    case OperationType::SIN:
      return sin(a);
    case OperationType::TAN:
      return tan(a);
    case OperationType::ACOS:
      return acos(a);
    case OperationType::ASIN:
      return asin(a);
    case OperationType::ATAN:
      return atan(a);
    case OperationType::SQRT:
      return sqrt(a);
    case OperationType::LN:
      return log(a);
    case OperationType::LOG:
      return log10(a);
    default:
      return 0;
  }
}

bool CalculatorModel::arithmetic(StackItem stack) {
  return ((stack.getType() >= OperationType::PLUS &&
           stack.getType() <= OperationType::MOD) ||
          stack.getType() == OperationType::UNARY_MINUS);
}

bool CalculatorModel::triganometry(StackItem stack) {
  return (stack.getType() >= OperationType::COS &&
          stack.getType() <= OperationType::LOG);
}

int Credit::creditCalculation() {
  monthlyPayment[0] = 0;
  overpayment = 0;
  totalPayout = 0;
  double monthlyRate = percent / 100 / 12;
  if (type == CreditType::ANNUNITY) {
    monthlyPayment[0] =
        creditAmount *
        (monthlyRate + (monthlyRate / (pow(1 + monthlyRate, creditTerm) - 1)));
    totalPayout = monthlyPayment[0] * creditTerm;
    overpayment = totalPayout - creditAmount;
  } else {
    double monthlyAmount = 0;
    double remainingAmount = 0;
    double interestAmount = 0;
    monthlyAmount = creditAmount / creditTerm;
    for (int i = 0; i < creditTerm; i++) {
      remainingAmount = creditAmount - monthlyAmount * i;
      interestAmount = remainingAmount * monthlyRate;
      monthlyPayment[i] = monthlyAmount + interestAmount;
      totalPayout += monthlyPayment[i];
    }
    overpayment = totalPayout - creditAmount;
  }
  return 0;
}

int Deposit::depositCalculation() {
  interest = 0;
  taxAmount = 0;
  outputAmount = 0;
  double currentInterest;
  depositAmount += (addList[0] + addList[1] + addList[3]);
  depositAmount -=
      (withdrawalsList[0] + withdrawalsList[1] + withdrawalsList[3]);
  if (capitalization == false) {
    for (int i = 0; i < depositTerm; i++) {
      currentInterest = depositAmount * percent * 30.417 / 365 / 100;
      taxAmount += currentInterest * taxRate / 100;
      interest += currentInterest;
    }
    outputAmount = depositAmount;
  } else {
    int period;
    if (frequency == Frequency::MONTHLY) {
      period = 1;
    } else if (frequency == Frequency::QUARTERLY) {
      period = 3;
    } else if (frequency == Frequency::ANNUAL) {
      period = 12;
    }
    double prevInterest = 0;
    for (int i = 0; i < depositTerm; i++) {
      if (i % period == 0) {
        prevInterest = interest;
      }
      currentInterest =
          ((depositAmount + prevInterest) * percent * 30.417 / 365 / 100);
      taxAmount += currentInterest * taxRate / 100;
      currentInterest -= currentInterest * taxRate / 100;
      interest += currentInterest;
    }
    outputAmount = depositAmount + interest;
    interest += taxAmount;
  }
  return 0;
}
