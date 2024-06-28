#include "calculator.h"

double parser(char *input_str, double x_value) {
  setlocale(LC_NUMERIC, "C");
  Stack *input_stack = calloc(1, sizeof(Stack));
  double result = 0;
  int size_input_str = strlen(input_str);
  char *temp_str = calloc(MAX_STR_LENGHT, sizeof(char));
  int is_number_flag = 0;
  int temp_str_index = 0;
  if (temp_str) {
    for (int i = 0; i <= size_input_str; i++) {
      switch (input_str[i]) {
        case 'x':
          push_stack(&input_stack, x_value, 0, 0);
          break;
        case '.':
        case '0' ... '9':
          numbers_to_str(&temp_str, input_str[i], &is_number_flag,
                         &temp_str_index);
          break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case 'm':
          operations(&input_stack, &temp_str, input_str[i], &is_number_flag,
                     &temp_str_index, &i, input_str);
          break;
        case 'c':
        case 's':
        case 't':
        case 'a':
        case 'l':
          functions(&input_stack, input_str[i], input_str, &i);
          break;
        case '(':
          push_stack(&input_stack, 0, LEFT_BRACKET, BRACKET);
          break;
        case ')':
          check_numbers(&input_stack, temp_str, &is_number_flag,
                        &temp_str_index);
          push_stack(&input_stack, 0, RIGHT_BRACKET, BRACKET);
          temp_str[0] = '\0';
          break;
        default:
          check_numbers(&input_stack, temp_str, &is_number_flag,
                        &temp_str_index);
          temp_str[0] = '\0';
          break;
      }
    }
    free(temp_str);
  }
  reverse_stack(&input_stack);
  shunting_yard(&input_stack);
  reverse_stack(&input_stack);
  result = calculation(&input_stack);
  destroy_stack(&input_stack);
  return result;
}

double calculation(Stack **input) {
  Stack *support = calloc(1, sizeof(Stack));
  double result = 0;
  double a = 0;
  double b = 0;
  int operand_count = 2;
  while ((*input)->next != NULL) {
    if ((*input)->priority == 0) {
      push_stack(&support, (*input)->value, 0, 0);
    } else if ((*input)->type == UNARY_MINUS) {
      support->value *= -1;
    } else if (((*input)->priority > 0) &&
               ((*input)->type < COS && (*input)->type > 0)) {
      while (support->next) {
        if (operand_count == 2) {
          b = support->value;
        } else if (operand_count == 1) {
          a = support->value;
        } else if (operand_count == 0) {
          break;
        }
        operand_count--;
        pop_stack(&support);
      }
      if (operand_count == 0) {
        push_stack(&support, binary_operations(a, b, (*input)->type), 0, 0);
      }
      operand_count = 2;
    } else if (((*input)->priority > 0) &&
               ((*input)->type > MOD && (*input)->type < LEFT_BRACKET)) {
      while (support->next) {
        if (operand_count == 2) {
          b = support->value;
        } else if (operand_count == 1) {
          break;
        }
        operand_count--;
        pop_stack(&support);
      }
      if (operand_count == 1) {
        push_stack(&support, unary_operations(b, (*input)->type), 0, 0);
      }
      operand_count = 2;
    }
    pop_stack(input);
  }
  pop_stack(input);
  if (support != NULL) {
    result = support->value;
  }
  destroy_stack(&support);
  return result;
}

void reverse_stack(Stack **input) {
  Stack *reverse_stack = calloc(1, sizeof(Stack));
  while ((*input)->next != NULL) {
    push_stack(&reverse_stack, (*input)->value, (*input)->type,
               (*input)->priority);
    pop_stack(input);
  }
  pop_stack(input);
  *input = reverse_stack;
}

void shunting_yard(Stack **input) {
  Stack *output = calloc(1, sizeof(Stack));
  Stack *support = calloc(1, sizeof(Stack));
  while ((*input)->next != NULL) {
    switch ((*input)->priority) {
      case 0:
        push_stack(&output, (*input)->value, 0, 0);
        break;
      default:
        if (support != NULL) {
          if ((((*input)->priority >= support->priority) ||
               ((*input)->type == LEFT_BRACKET)) &&
              (*input)->type != RIGHT_BRACKET) {
            if ((*input)->priority == support->priority &&
                (*input)->type != POW && support->type != LEFT_BRACKET &&
                (*input)->type != UNARY_MINUS) {
              push_stack(&output, 0, support->type, support->priority);
              pop_stack(&support);
            }
            push_stack(&support, 0, (*input)->type, (*input)->priority);
          } else {
            if ((*input)->type == RIGHT_BRACKET) {
              while (support->next && (support->type != LEFT_BRACKET)) {
                push_stack(&output, 0, support->type, support->priority);
                pop_stack(&support);
              }
            } else {
              while (support->next != NULL &&
                     (support->priority >= (*input)->priority)) {
                push_stack(&output, 0, support->type, support->priority);
                pop_stack(&support);
              }
              if (support->type != LEFT_BRACKET) {
                pop_stack(&support);
              }
            }
            push_stack(&support, 0, (*input)->type, (*input)->priority);
            if (output->type < COS) {
              if (support->type == RIGHT_BRACKET) {
                pop_stack(&support);
              }
              if (support->type == LEFT_BRACKET) {
                pop_stack(&support);
              }
            }
          }
        }
        break;
    }
    pop_stack(input);
  }
  destroy_stack(input);
  while (support->next != NULL) {
    if (support->type != LEFT_BRACKET && support->type != RIGHT_BRACKET) {
      push_stack(&output, 0, support->type, support->priority);
    }
    pop_stack(&support);
  }
  if (support->type == MINUS || support->type == PLUS || support->type == DIV) {
    push_stack(&output, 0, support->type, support->priority);
  }
  destroy_stack(&support);
  *input = output;
}

void numbers_to_str(char **temp_str, char sym, int *is_number_flag,
                    int *temp_str_index) {
  (*temp_str)[*temp_str_index] = sym;
  (*temp_str_index)++;
  (*temp_str)[*temp_str_index] = '\0';
  *is_number_flag = 1;
}

void operations(Stack **input_stack, char **temp_str, char math_operator,
                int *is_number_flag, int *temp_str_index, int *i,
                char *input_str) {
  switch (math_operator) {
    case '+':
      if (input_str[*i - 1] == '(') {
        (*temp_str)[*temp_str_index++] = math_operator;
        (*temp_str)[*temp_str_index] = '\0';
      } else {
        check_numbers(input_stack, *temp_str, is_number_flag, temp_str_index);
        push_stack(input_stack, 0, PLUS, LOW);
        (*temp_str)[*temp_str_index] = '\0';
      }
      break;
    case '-':
      if ((*i == 0 || strchr("(+-*/^m", input_str[*i - 1]))) {
        push_stack(input_stack, 0, UNARY_MINUS, HIGH);
        (*temp_str)[*temp_str_index] = '\0';
      } else {
        check_numbers(input_stack, *temp_str, is_number_flag, temp_str_index);
        push_stack(input_stack, 0, MINUS, LOW);
        (*temp_str)[*temp_str_index] = '\0';
      }
      break;
    case '*':
      check_numbers(input_stack, *temp_str, is_number_flag, temp_str_index);
      push_stack(input_stack, 0, MUL, MIDDLE);
      (*temp_str)[0] = '\0';
      break;
    case '/':
      check_numbers(input_stack, *temp_str, is_number_flag, temp_str_index);
      push_stack(input_stack, 0, DIV, MIDDLE);
      (*temp_str)[*temp_str_index] = '\0';
      break;
    case '^':
      check_numbers(input_stack, *temp_str, is_number_flag, temp_str_index);
      push_stack(input_stack, 0, POW, HIGH);
      (*temp_str)[*temp_str_index] = '\0';
      break;
    case 'm':
      if (input_str[*i + 1] == 'o' ? input_str[*i + 2] == 'd' ? 1 : 0 : 0) {
        *i += 2;
        check_numbers(input_stack, *temp_str, is_number_flag, temp_str_index);
        push_stack(input_stack, 0, MOD, HIGH);
        (*temp_str)[*temp_str_index] = '\0';
      }
      break;
  }
}

void functions(Stack **input_stack, char function, char *input_str, int *i) {
  switch (function) {
    case 'c':
      if (input_str[*i + 1] == 'o' ? input_str[*i + 2] == 's' ? 1 : 0 : 0) {
        *i += 2;
        push_stack(input_stack, 0, COS, HIGH);
      }
      break;
    case 's':
      if (input_str[*i + 1] == 'i' ? input_str[*i + 2] == 'n' ? 1 : 0 : 0) {
        *i += 2;
        push_stack(input_stack, 0, SIN, HIGH);
      }
      if (input_str[*i + 1] == 'q'
              ? input_str[*i + 2] == 'r' ? input_str[*i + 3] == 't' ? 1 : 0 : 0
              : 0) {
        *i += 3;
        push_stack(input_stack, 0, SQRT, HIGH);
      }
      break;
    case 't':
      if (input_str[*i + 1] == 'a' ? input_str[*i + 2] == 'n' ? 1 : 0 : 0) {
        *i += 2;
        push_stack(input_stack, 0, TAN, HIGH);
      }
      break;
    case 'a':
      if (input_str[*i + 1] == 'c'
              ? input_str[*i + 2] == 'o' ? input_str[*i + 3] == 's' ? 1 : 0 : 0
              : 0) {
        *i += 3;
        push_stack(input_stack, 0, ACOS, HIGH);
      }
      if (input_str[*i + 1] == 's'
              ? input_str[*i + 2] == 'i' ? input_str[*i + 3] == 'n' ? 1 : 0 : 0
              : 0) {
        *i += 3;
        push_stack(input_stack, 0, ASIN, HIGH);
      }
      if (input_str[*i + 1] == 't'
              ? input_str[*i + 2] == 'a' ? input_str[*i + 3] == 'n' ? 1 : 0 : 0
              : 0) {
        *i += 3;
        push_stack(input_stack, 0, ATAN, HIGH);
      }
      break;
    case 'l':
      if (input_str[*i + 1] == 'n' ? 1 : 0) {
        *i += 1;
        push_stack(input_stack, 0, LN, HIGH);
      }
      if (input_str[*i + 1] == 'o' ? input_str[*i + 2] == 'g' ? 1 : 0 : 0) {
        *i += 2;
        push_stack(input_stack, 0, LOG, HIGH);
      }
      break;
  }
}

void push_stack(Stack **head, Data value, int type, int priority) {
  Stack *t = calloc(1, sizeof(Stack));
  t->value = value;
  t->type = type;
  t->priority = priority;
  t->next = *head;
  *head = t;
}

Stack pop_stack(Stack **head) {
  Stack t = {0};
  Stack *ptr = NULL;
  ptr = (*head);
  t.value = ptr->value;
  t.type = ptr->type;
  t.priority = ptr->priority;
  (*head) = (*head)->next;
  free(ptr);
  return t;
}

void destroy_stack(Stack **head) {
  if (head != NULL) {
    while (*head != NULL) {
      pop_stack(head);
    }
  }
}

void check_numbers(Stack **input_stack, char *temp_str, int *is_number_flag,
                   int *temp_str_index) {
  if (*is_number_flag && temp_str) {
    push_stack(input_stack, atof(temp_str), 0, 0);
    *temp_str_index = 0;
    *is_number_flag = 0;
  }
}

double binary_operations(double a, double b, int operation) {
  double result = 0;
  switch (operation) {
    case PLUS:
      result = a + b;
      break;
    case MINUS:
      result = a - b;
      break;
    case MUL:
      result = a * b;
      break;
    case DIV:
      result = a / b;
      break;
    case POW:
      result = pow(a, b);
      break;
    case MOD:
      result = fmod(a, b);
      break;
  }
  return result;
}

double unary_operations(double a, int operation) {
  double result = 0;
  switch (operation) {
    case COS:
      result = cos(a);
      break;
    case SIN:
      result = sin(a);
      break;
    case TAN:
      result = tan(a);
      break;
    case ACOS:
      result = acos(a);
      break;
    case ASIN:
      result = asin(a);
      break;
    case ATAN:
      result = atan(a);
      break;
    case SQRT:
      result = sqrt(a);
      break;
    case LN:
      result = log(a);
      break;
    case LOG:
      result = log10(a);
      break;
  }
  return result;
}

int credit_calculator(Credit *calc) {
  calc->monthly_payment[0] = 0;
  calc->overpayment = 0;
  calc->total_payout = 0;
  double monthly_rate = calc->percent / 100 / 12;
  if (!calc->type_of_credit) {
    calc->monthly_payment[0] =
        calc->credit_amount *
        (monthly_rate +
         (monthly_rate / (pow(1 + monthly_rate, calc->credit_term) - 1)));
    calc->total_payout = calc->monthly_payment[0] * calc->credit_term;
    calc->overpayment = calc->total_payout - calc->credit_amount;
  } else {
    double monthly_amount;  // размер основного ежемесячного платежа
    double remaining_amount;  // оставшаяся сумма долга
    double interest_amount;  // сумма процентов, начисленная на оставшуюся сумму
                             // долга
    monthly_amount = calc->credit_amount / calc->credit_term;
    for (int i = 0; i < calc->credit_term; i++) {
      remaining_amount = calc->credit_amount - monthly_amount * i;
      interest_amount = remaining_amount * monthly_rate;
      calc->monthly_payment[i] = monthly_amount + interest_amount;
      calc->total_payout += calc->monthly_payment[i];
    }
    calc->overpayment = calc->total_payout - calc->credit_amount;
  }
  return 0;
}

int deposit_calculator(Deposit *calc) {
  calc->interest = 0;
  calc->tax_amount = 0;
  calc->output_amount = 0;
  double
      current_interest;  // переменная для хранения текущих начислений процентов
  // учитываем пополнения и частичные снятия
  calc->deposit_amount +=
      (calc->add_list[0] + calc->add_list[1] + calc->add_list[3]);
  calc->deposit_amount -=
      (calc->withdrawals_list[0] + calc->withdrawals_list[1] +
       calc->withdrawals_list[3]);
  if (!calc->capitalization) {  // без капитализации - расчитываем проценты
    for (int i = 0; i < calc->deposit_term; i++) {
      current_interest =
          calc->deposit_amount * calc->percent * 30.417 / 365 / 100;
      calc->tax_amount += current_interest * calc->tax / 100;
      calc->interest += current_interest;
    }
    calc->output_amount = calc->deposit_amount;
  } else {  // с капитализацией - выбор периодичности капитолизации
    int period;
    if (calc->frequency == 0) {
      period = 1;  // ежемесячная капитализация
    } else if (calc->frequency == 1) {
      period = 3;  // ежеквартальная капитализация
    } else if (calc->frequency == 2) {
      period = 12;  // ежегодная капитализация
    }
    double prev_interest;
    for (int i = 0; i < calc->deposit_term; i++) {
      if (!(i % period)) {
        prev_interest = calc->interest;  // Обновление процентов с учетом налога
      }
      current_interest = ((calc->deposit_amount + prev_interest) *
                          calc->percent * 30.417 / 365 / 100);
      calc->tax_amount += current_interest * calc->tax /
                          100;  // расчет процентов с учетом налога
      current_interest -= current_interest * calc->tax /
                          100;  // вычитаем налог из начисленных процентов
      calc->interest +=
          current_interest;  // обновляем текущие начисленных процентов
    }
    // итоговая сумма на вкладе с учетом начисленных процентов и налога
    calc->output_amount = calc->deposit_amount + calc->interest;
    calc->interest +=
        calc->tax_amount;  // добавляем налог к начисленным процентам
  }
  return 0;
}