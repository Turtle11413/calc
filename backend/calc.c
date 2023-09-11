#include "calc.h"

int from_answer(char* str, double* result, double x) {
  int status = OK;
  *result = 0;
  Stack infix;
  Stack reversed;
  Stack buffer;

  status = validateStr(str);

  if (status == OK) {
    initStack(&infix);
    status = parseToStack(str, &infix);
  }
  if (status == OK) {
    initStack(&reversed);
    status = reverseStack(&infix, &reversed);
  }
  if (status == OK) {
    initStack(&buffer);
    status = getPostfix(&reversed, &buffer, &infix);
  }
  if (status == OK) {
    status = reverseStack(&infix, &reversed);
  }
  if (status == OK) {
    status = calculateResult(&reversed, x, result);
    if (isnan(*result)) {
      *result = NAN;
      status = NAN_RESULT;
    }
    if (isinf(*result)) {
      *result = INFINITY;
      status = INF_RESULT;
    }
  }
  return status;
}

int parseToStack(char* str, Stack* stack) {
  int status = OK;
  int unaryPlus = 0, unaryMinus = 0;
  int len = (int)strlen(str);
  for (int i = 0; i < len && status == OK; i++) {
    status = getNumber(str, stack, &i, &unaryMinus, &unaryPlus);
    if (status == OK) {
      setZeroPriority(str, stack, i);
      setFirstPriority(str, stack, i, &unaryMinus, &unaryPlus);
      setSecondPriority(str, stack, &i);
      setThirdPriority(str, stack, i);
      setFourthPriority(str, stack, &i);
    }
  }
  return status;
}

int getNumber(char* str, Stack* stack, int* i, int* unaryMinus,
              int* unaryPlus) {
  char buffer[256] = {0};
  int status = OK;
  double num = 0;
  if (isdigit(str[*i])) {
    int dot_count = 0;
    int buffer_index = 0;
    while ((isdigit(str[*i])) || (str[*i] == '.')) {
      if (str[*i] == '.') {
        dot_count++;
      }
      if (dot_count <= 1) {
        buffer[buffer_index++] = str[(*i)++];
      }
    }
    num = atof(buffer);
    if (*unaryMinus == 1) {
      num *= -1;
    }
    Lexeme tmpLexeme = {num, NUM, 0};
    status = push(stack, tmpLexeme);
  }
  *unaryMinus = 0;
  *unaryPlus = 0;
  return status;
}

int reverseStack(Stack* inputStack, Stack* reversedStack) {
  int status = OK;
  while (inputStack->top != NULL) {
    status = push(reversedStack, inputStack->top->lexeme);
    pop(inputStack);
  }
  return status;
}

int getPostfix(Stack* infix, Stack* buffer, Stack* postfix) {
  int status = OK;
  while (infix->top != NULL && status == OK) {
    if (infix->top->lexeme.type == NUM || infix->top->lexeme.type == X) {
      status = push(postfix, infix->top->lexeme);
    } else if (infix->top->lexeme.priority == 4 ||
               infix->top->lexeme.type == LEFT_BRACKET) {
      status = push(buffer, infix->top->lexeme);
    } else if (infix->top->lexeme.type == RIGHT_BRACKET) {
      while (buffer->top != NULL && buffer->top->lexeme.type != LEFT_BRACKET) {
        status = push(postfix, buffer->top->lexeme);
        pop(buffer);
      }
      if (buffer->top != NULL) {
        pop(buffer);
      }
    } else if (buffer->top == NULL ||
               (infix->top->lexeme.priority > buffer->top->lexeme.priority)) {
      status = push(buffer, infix->top->lexeme);
    } else if ((buffer->top != NULL) &&
               (infix->top->lexeme.priority <= buffer->top->lexeme.priority) &&
               infix->top->lexeme.type != RIGHT_BRACKET) {
      if (buffer->top->lexeme.priority == 3 &&
          infix->top->lexeme.priority == 3) {
        status = push(buffer, infix->top->lexeme);
      } else {
        while ((buffer->top != NULL) &&
               (infix->top->lexeme.priority <= buffer->top->lexeme.priority)) {
          status = push(postfix, buffer->top->lexeme);
          pop(buffer);
        }
        status = push(buffer, infix->top->lexeme);
      }
    }
    pop(infix);
  }

  if (infix->top == NULL && buffer->top != NULL) {
    while (buffer->top != NULL) {
      status = push(postfix, buffer->top->lexeme);
      pop(buffer);
    }
  }
  return status;
}

int calculateResult(Stack* rpn, double x, double* result) {
  int status = OK;
  Stack buffer;
  initStack(&buffer);
  while (rpn->top != NULL && status == OK) {
    if (rpn->top->lexeme.type == NUM || rpn->top->lexeme.type == X) {
      if (rpn->top->lexeme.type == X) {
        Lexeme tmpLexeme = {x, NUM, 0};
        status = push(&buffer, tmpLexeme);
      } else {
        status = push(&buffer, rpn->top->lexeme);
      }
      pop(rpn);
    } else if (rpn->top->lexeme.type != NUM) {
      double result = 0;
      if (rpn->top->lexeme.priority == 4) {
        Lexeme operation = rpn->top->lexeme;
        Lexeme number = buffer.top->lexeme;
        result = calculateTrig(&operation, &number);
        pop(&buffer);
        pop(rpn);
        Lexeme tmpLexeme = {result, NUM, 0};
        status = push(&buffer, tmpLexeme);
      } else {
        Lexeme operation = rpn->top->lexeme;
        double firstNumber = pop(&buffer);
        double secondNumber = pop(&buffer);
        result =
            calculateSimpleOperation(&operation, firstNumber, secondNumber);
        pop(rpn);
        Lexeme tmpLexeme = {result, NUM, 0};
        push(&buffer, tmpLexeme);
      }
    }
  }
  *result = buffer.top->lexeme.value;
  pop(&buffer);
  return status;
}

double calculateTrig(Lexeme* operation, Lexeme* number) {
  double result = 0;
  if (operation->type == SIN) result = sin(number->value);
  if (operation->type == ASIN) result = asin(number->value);
  if (operation->type == COS) result = cos(number->value);
  if (operation->type == ACOS) result = acos(number->value);
  if (operation->type == TAN) result = tan(number->value);
  if (operation->type == ATAN) result = atan(number->value);
  if (operation->type == SQRT) result = sqrt(number->value);
  if (operation->type == LOG) result = log10(number->value);
  if (operation->type == LN) result = log(number->value);
  return result;
}

double calculateSimpleOperation(Lexeme* operation, double firstNumber,
                                double secondNumber) {
  double result = 0;
  if (operation->type == PLUS) result = firstNumber + secondNumber;
  if (operation->type == MINUS) result = secondNumber - firstNumber;
  if (operation->type == MULT) result = firstNumber * secondNumber;
  if (operation->type == DIV) result = secondNumber / firstNumber;
  if (operation->type == MOD) result = fmod(secondNumber, firstNumber);
  if (operation->type == EXP) result = pow(secondNumber, firstNumber);
  return result;
}
