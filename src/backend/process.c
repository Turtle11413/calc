#include "calc.h"

int setZeroPriority(char* str, Stack* stack, int i) {
	int status = OK;
  switch (str[i]) {
    case '(':
      status = push(stack, '(', LEFT_BRACKET, 0);
      break;
    case ')':
      status = push(stack, ')', RIGHT_BRACKET, 0);
      break;
    case 'x':
      status = push(stack, 'x', X, 0);
      break;
  }
	return status;
}

int setFirstPriority(char* str, Stack* stack, int i, int* minusSign, int* plusSign) {
	int status = OK;
  if (str[i] == '+') {
    if (i == 0 || (str[i - 1] == '(')) {
      *plusSign = 1;
    } else {
      status = push(stack, '+', PLUS, 1);
    }
  } else if (str[i] == '-') {
    if (i == 0 || (str[i - 1] == '(')) {
      status = push(stack, 0, NUM, 0);
      status = push(stack, '-', MINUS, 1);
      *minusSign = 0;
    } else {
      status = push(stack, '-', MINUS, 1);
    }
  }
	return status;
}

int setSecondPriority(char* str, Stack* stack, int* i) {
	int status = OK;
  if (str[*i] == '*') {
    status = push(stack, '*', MULT, 2);
  } else if (str[*i] == '/') {
    status = push(stack, '/', DIV, 2);
  } else if (str[*i] == 'm') {
    status = push(stack, 'm', MOD, 2);
    *i = *i + 2;
  }
	return status;
}

int setThirdPriority(char* str, Stack* stack, int i) {
	int status = OK;
  if (str[i] == '^') {
    status = push(stack, '^', EXP, 3);
  }
	return status;
}

int setFourthPriority(char* str, Stack* stack, int* i) {
	int status = OK;
  if (str[*i] == 'c') {
    status = push(stack, 'c', COS, 4);
    *i += 2;
  } else if (str[*i] == 't') {
    status = push(stack, 't', TAN, 4);
    *i += 2;
  } else if (str[*i] == 's') {
    if (str[*i + 1] == 'i') {
      status = push(stack, 's', SIN, 4);
      *i += 2;
    } else {
      status = push(stack, 'q', SQRT, 4);
      *i += 3;
    }
  } else if (str[*i] == 'l') {
    if (str[*i + 1] == 'o') {
      status = push(stack, 'L', LOG, 4);
      *i += 2;
    } else {
      status = push(stack, 'l', LN, 4);
      *i += 1;
    }
  } else if (str[*i] == 'a') {
    if (str[*i + 1] == 's') {
       status = push(stack, 'S', ASIN, 4);
    } else if (str[*i + 1] == 'c') {
      status = push(stack, 'C', ACOS, 4);
    } else {
      status = push(stack, 'T', ATAN, 4);
    }
    *i += 3;
  }
	return status;
}
