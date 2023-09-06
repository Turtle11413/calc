#include "calc.h"

int processing(char* str, double* result, double x) {
  int status = OK;
  *result = 0;
  Stack infix;
  initStack(&infix);

  Stack buffer;
  initStack(&buffer);

  Stack reversed;
  initStack(&reversed);

  status = validateStr(str);
  if (status == OK && 0 < strlen(str) && strlen(str) <= 255) {
    if (parseToStack(str, &infix) == OK) {
      reverseStack(&infix, &reversed);
      getPostfix(&reversed, &buffer, &infix);
      reverseStack(&infix, &reversed);
      *result = getResult(&reversed, x);
    }
    if (isnan(*result)) {
      *result = NAN;
      status = CALCULATION_ERROR;
    }
    if (isinf(*result)) {
      *result = INFINITY;
      status = CALCULATION_ERROR;
    }
  }
  return status;
}

int parseToStack(char* str, Stack* stack) {
  char buffer[256] = {0};
  int strLength = (int)strlen(str);
  int status = OK;
  int minusSign = 0;
  int plusSign = 0;
  for (int i = 0; i < strLength && status == OK; i++) {
    if (getNumber(str, stack, buffer, &i, &minusSign, &plusSign) == INCORRECT_INPUT) {
      status = INCORRECT_INPUT;
    } else {
      setZeroPriority(str, stack, i);
      setFirstPriority(str, stack, i, &minusSign, &plusSign);
      setSecondPriority(str, stack, &i);
      setThirdPriority(str, stack, i);
      setFourthPriority(str, stack, &i);
    }
  }
  return status;
}

int getNumber(char* str, Stack* stack, char* buffer, int* i, int* minusSign, int* plusSign) {
  int status = OK;
  double num = 0;
  if (isdigit(str[*i])) {
    int temp = *i;
    int x = 0;
    while ((isdigit(str[temp])) || (str[temp] == '.')) {
      buffer[x] = str[temp];
      x++;
      temp++;
    }
    *i = temp - 1;
    if (strlen(buffer) > 1 && buffer[0] == '0' && buffer[1] != '.') {
      status = INCORRECT_INPUT;
    } else {
      num = atof(buffer);
      if (*minusSign == 1) {
        num *= -1;
      }
      status = push(stack, num, NUM, 0);
      memset(buffer, '\0', (size_t)sizeof(buffer));
    }
  }
  *minusSign = 0;
  *plusSign = 0;
  return status;
}

int reverseStack(Stack* inputStack, Stack* reversedStack) {
	int status = OK;
  while (inputStack->top != NULL) {
    double data = inputStack->top->data;
    int type = inputStack->top->type;
    int priority = inputStack->top->priority;
    status = push(reversedStack, data, type, priority);
    pop(inputStack);
  }
	return status;
}

void getPostfix(Stack* infix, Stack* buffer, Stack* postfix) {
	int status = OK;
  while (infix->top != NULL && status == OK) {
    if (infix->top->type == NUM || infix->top->type == X) {
      status = push(postfix, infix->top->data, infix->top->type, infix->top->priority);
    } else if (infix->top->priority == 4 || infix->top->type == LEFT_BRACKET) {
      status = push(buffer, infix->top->data, infix->top->type, infix->top->priority);
    } else if (infix->top->type == RIGHT_BRACKET) {
      while (buffer->top != NULL && buffer->top->type != LEFT_BRACKET) {
        status = push(postfix, buffer->top->data, buffer->top->type, buffer->top->priority);
        pop(buffer);
      }
      if (buffer->top != NULL) {
        pop(buffer);
      }
    } else if (buffer->top == NULL || (infix->top->priority > buffer->top->priority)) {
      status = push(buffer, infix->top->data, infix->top->type, infix->top->priority);
    } else if ((buffer->top != NULL) && (infix->top->priority <= buffer->top->priority) && infix->top->type != RIGHT_BRACKET) {
      if (buffer->top->priority == 3 && infix->top->priority == 3) {
        status = push(buffer, infix->top->data, infix->top->type, infix->top->priority);
      } else {
        while ((buffer->top != NULL) && (infix->top->priority <= buffer->top->priority)) {
          status = push(postfix, buffer->top->data, buffer->top->type, buffer->top->priority);
          pop(buffer);
        }
        status = push(buffer, infix->top->data, infix->top->type, infix->top->priority);
      }
    }
    pop(infix);
  }

  if (infix->top == NULL && buffer->top != NULL) {
    while (buffer->top != NULL) {
      status = push(postfix, buffer->top->data, buffer->top->type, buffer->top->priority);
      pop(buffer);
    }
  }
}


double getResult(Stack* inputRpnStack, double x) {
  double res_value = 0;
	int status = OK;

  Stack buffer;
  initStack(&buffer);

  while (inputRpnStack->top != NULL && status == OK) {
    if (inputRpnStack->top->type == NUM || inputRpnStack->top->type == X) {
      if (inputRpnStack->top->type == X) {
        status = push(&buffer, x, X, inputRpnStack->top->priority);
      } else {
        status = push(&buffer, inputRpnStack->top->data, inputRpnStack->top->type, inputRpnStack->top->priority);
      }
      pop(inputRpnStack);
    } else if (inputRpnStack->top->type != NUM) {
      double result = 0;
      if (inputRpnStack->top->priority == 4) {
        if (inputRpnStack->top->type == SIN)  result = sin(buffer.top->data);
        if (inputRpnStack->top->type == ASIN) result = asin(buffer.top->data);
        if (inputRpnStack->top->type == COS)  result = cos(buffer.top->data);
        if (inputRpnStack->top->type == ACOS) result = acos(buffer.top->data);
        if (inputRpnStack->top->type == TAN)  result = tan(buffer.top->data);
        if (inputRpnStack->top->type == ATAN) result = atan(buffer.top->data);
        if (inputRpnStack->top->type == SQRT) result = sqrt(buffer.top->data);
        if (inputRpnStack->top->type == LOG)  result = log10(buffer.top->data);
        if (inputRpnStack->top->type == LN)   result = log(buffer.top->data);
        pop(&buffer);
        pop(inputRpnStack);
        status = push(&buffer, result, NUM, 0);
      } else {
        double firstLexeme = pop(&buffer);
        double secondLexeme = pop(&buffer);
        if (inputRpnStack->top->type == PLUS)  result = secondLexeme + firstLexeme;
        if (inputRpnStack->top->type == MINUS) result = secondLexeme - firstLexeme;
        if (inputRpnStack->top->type == MULT)  result = secondLexeme * firstLexeme;
        if (inputRpnStack->top->type == DIV)   result = secondLexeme / firstLexeme;
        if (inputRpnStack->top->type == MOD)   result = fmod(secondLexeme, firstLexeme);
        if (inputRpnStack->top->type == EXP)   result = pow(secondLexeme, firstLexeme);
        pop(inputRpnStack);
        push(&buffer, result, NUM, 0);
      }
    }
  }
  res_value = buffer.top->data;
  pop(&buffer);
  return res_value;
}
