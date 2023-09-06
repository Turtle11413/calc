#include "calc.h"

int processing(char* str, double* result, double x) {
  int status = OK;
  Stack infix;
  initStack(&infix);

  Stack reversed;
  initStack(&reversed);

  Stack buffer;
  initStack(&buffer);

  if (validateStr(str) == OK && 0 < strlen(str) && strlen(str) <= 255) {
    if (inputStrToStack(str, &infix)) {
      reverseForRpn(&infix, &reversed);
      infixToPostfix(&reversed, &buffer, &infix);
      reverseForRpn(&infix, &reversed);
      *result = calculateResult(&reversed, x);
    } else {
      status = ERROR;
      *result = 0;
    }
  } else {
    status = ERROR;
    *result = 0;
  }
  if (isnan(*result)) {
    *result = 0;
    status = ERROR;
  }
  if (isinf(*result)) {
    *result = 0;
    status = ERROR;
  }
  return status;
}

int inputStrToStack(char* str, Stack* stack) {
  char buffer[260] = {0};
  int strLength = (int)strlen(str);
  int status = OK;
  int minusSign = 0;
  int plusSign = 0;
  for (int i = 0; i < strLength && status == OK; i++) {
    if (getNumber(str, stack, buffer, &i, &minusSign, &plusSign) == ERROR) {
      status = ERROR;
    } else {
      processZeroPriority(str, stack, i);
      processFirstPriority(str, stack, i, &minusSign, &plusSign);
      processSecondPriority(str, stack, &i);
      processThirdPriority(str, stack, i);
      processFourthPriority(str, stack, &i);
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
      status = ERROR;
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

int reverseForRpn(Stack* inputStack, Stack* reversedStack) {
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

void infixToPostfix(Stack* infixStack, Stack* bufferStack, Stack* postfixStack) {
	int status = OK;
  while (infixStack->top != NULL && status == OK) {
    if (infixStack->top->type == NUM || infixStack->top->type == X) {
      status = push(postfixStack, infixStack->top->data, infixStack->top->type, infixStack->top->priority);
    } else if (infixStack->top->priority == 4 || infixStack->top->type == L_BRACKET) {
      status = push(bufferStack, infixStack->top->data, infixStack->top->type, infixStack->top->priority);
    } else if (infixStack->top->type == R_BRACKET) {
      while (bufferStack->top != NULL && bufferStack->top->type != L_BRACKET) {
        status = push(postfixStack, bufferStack->top->data, bufferStack->top->type, bufferStack->top->priority);
        pop(bufferStack);
      }
      if (bufferStack->top != NULL) {
        pop(bufferStack);
      }
    } else if (bufferStack->top == NULL || (infixStack->top->priority > bufferStack->top->priority)) {
      status = push(bufferStack, infixStack->top->data, infixStack->top->type, infixStack->top->priority);
    } else if ((bufferStack->top != NULL) && (infixStack->top->priority <= bufferStack->top->priority) && infixStack->top->type != R_BRACKET) {
      if (bufferStack->top->priority == 3 && infixStack->top->priority == 3) {
        status = push(bufferStack, infixStack->top->data, infixStack->top->type, infixStack->top->priority);
      } else {
        while ((bufferStack->top != NULL) && (infixStack->top->priority <= bufferStack->top->priority)) {
          status = push(postfixStack, bufferStack->top->data, bufferStack->top->type, bufferStack->top->priority);
          pop(bufferStack);
        }
        status = push(bufferStack, infixStack->top->data, infixStack->top->type, infixStack->top->priority);
      }
    }
    pop(infixStack);
  }

  if (infixStack->top == NULL && bufferStack->top != NULL) {
    while (bufferStack->top != NULL) {
      status = push(postfixStack, bufferStack->top->data, bufferStack->top->type, bufferStack->top->priority);
      pop(bufferStack);
    }
  }
}


double calculateResult(Stack* inputRpnStack, double x) {
  double res_value = 0;
	int status = OK;

  Stack bufferStack;
  initStack(&bufferStack);

  while (inputRpnStack->top != NULL && status == OK) {
    if (inputRpnStack->top->type == NUM || inputRpnStack->top->type == X) {
      if (inputRpnStack->top->type == X) {
        status = push(&bufferStack, x, X, inputRpnStack->top->priority);
      } else {
        status = push(&bufferStack, inputRpnStack->top->data, inputRpnStack->top->type, inputRpnStack->top->priority);
      }
      pop(inputRpnStack);
    } else if (inputRpnStack->top->type != NUM) {
      double result = 0;
      if (inputRpnStack->top->priority == 4) {
        if (inputRpnStack->top->type == SIN)  result = sin(bufferStack.top->data);
        if (inputRpnStack->top->type == ASIN) result = asin(bufferStack.top->data);
        if (inputRpnStack->top->type == COS)  result = cos(bufferStack.top->data);
        if (inputRpnStack->top->type == ACOS) result = acos(bufferStack.top->data);
        if (inputRpnStack->top->type == TAN)  result = tan(bufferStack.top->data);
        if (inputRpnStack->top->type == ATAN) result = atan(bufferStack.top->data);
        if (inputRpnStack->top->type == SQRT) result = sqrt(bufferStack.top->data);
        if (inputRpnStack->top->type == LOG)  result = log10(bufferStack.top->data);
        if (inputRpnStack->top->type == LN)   result = log(bufferStack.top->data);
        pop(&bufferStack);
        pop(inputRpnStack);
        status = push(&bufferStack, result, NUM, 0);
      } else {
        double firstLexeme = pop(&bufferStack);
        double secondLexeme = pop(&bufferStack);
        if (inputRpnStack->top->type == PLUS)  result = secondLexeme + firstLexeme;
        if (inputRpnStack->top->type == MINUS) result = secondLexeme - firstLexeme;
        if (inputRpnStack->top->type == MULT)  result = secondLexeme * firstLexeme;
        if (inputRpnStack->top->type == DIV)   result = secondLexeme / firstLexeme;
        if (inputRpnStack->top->type == MOD)   result = fmod(secondLexeme, firstLexeme);
        if (inputRpnStack->top->type == EXP)   result = pow(secondLexeme, firstLexeme);
        pop(inputRpnStack);
        push(&bufferStack, result, NUM, 0);
      }
    }
  }
  res_value = bufferStack.top->data;
  pop(&bufferStack);
  return res_value;
}
