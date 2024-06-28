#ifndef _SRC_SMARTCALC_V1_H_
#define _SRC_SMARTCALC_V1_H_

#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LENGHT 50

typedef double Data;

typedef enum {
  NUMBER = 1,
  X = 2,
  PLUS = 3,
  MINUS = 4,
  MUL = 5,
  DIV = 6,
  POW = 7,
  MOD = 8,
  COS = 9,
  SIN = 10,
  TAN = 11,
  ACOS = 12,
  ASIN = 13,
  ATAN = 14,
  SQRT = 15,
  LN = 16,
  LOG = 17,
  LEFT_BRACKET = 18,
  RIGHT_BRACKET = 19,
  UNARY_MINUS = 20
} type_op;

typedef enum {
  BRACKET = -1,
  NUM = 0,
  LOW = 1,
  MIDDLE = 2,
  HIGH = 3
} priority_op;

typedef struct Stack {
  Data value;
  type_op type;
  priority_op priority;
  struct Stack *next;
} Stack;

typedef struct Credit {
  double credit_amount;  // общая сумма кредита
  double percent;        // процентная ставка
  int credit_term;       // срок кредита
  int type_of_credit;  // тип кредита (аннуитетный, дифференцированный)
  double monthly_payment[600];  // ежемесячный платеж
  double overpayment;           // переплата по кредиту
  double total_payout;          // общая выплата
} Credit;

typedef struct Deposit {
  double deposit_amount;  // сумма вклада
  double percent;         // процентная ставка
  double tax;             // налоговая ставка
  int deposit_term;       // срок размещения
  int frequency;  // периодичность выплат (0 - ежемесячно, 1 - ежеквартально, 2
                  // - ежегодно)
  int capitalization;  // капитализация процентов (0 - нет, 1 - да)
  double add_list[600];          // список пополнений
  double withdrawals_list[600];  // список частичных выплат
  double interest;               // начисленные проценты
  double tax_amount;             // сумма налога
  double output_amount;  // сумма на вкладе к концу срока
} Deposit;

/* Основные функции для калькулятора */
double parser(char *input_str, double x_value);
double calculation(Stack **input);
void shunting_yard(Stack **input);
int credit_calculator(Credit *calc);
int deposit_calculator(Deposit *calc);

/* Фунции для работы со стеком */
void push_stack(Stack **head, Data value, int type, int priority);
Stack pop_stack(Stack **head);
void destroy_stack(Stack **head);

/* Вспомогательные функции */
void check_numbers(Stack **input_stack, char *temp_str, int *is_number_flag,
                   int *temp_str_index);
void reverse_stack(Stack **input);
void numbers_to_str(char **temp_str, char sym, int *is_number_flag,
                    int *temp_str_index);
void operations(Stack **input_stack, char **temp_str, char math_operator,
                int *is_number_flag, int *temp_str_index, int *i,
                char *input_str);
void functions(Stack **input_stack, char function, char *input_str, int *i);

/* Математические функции */
double binary_operations(double a, double b, int operation);
double unary_operations(double a, int operation);

#endif
