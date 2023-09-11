#include "calc.h"

int setZeroPriority(char* str, Stack* stack, int i) {
  int status = OK;
  if (str[i] == '(') {
    Lexeme tmpLexeme = {'(', LEFT_BRACKET, 0};
    status = push(stack, tmpLexeme);
  } else if (str[i] == ')') {
    Lexeme tmpLexeme = {')', RIGHT_BRACKET, 0};
    status = push(stack, tmpLexeme);
  } else if (str[i] == 'x') {
    Lexeme tmpLexeme = {'x', X, 0};
    status = push(stack, tmpLexeme);
  }
  return status;
}

int setFirstPriority(char* str, Stack* stack, int i, int* minusSign,
                     int* plusSign) {
  int status = OK;

  if (str[i] == '+') {
    if (i == 0 || (str[i - 1] == '(')) {
      *plusSign = 1;
    } else {
      Lexeme tmpLexeme = {'+', PLUS, 1};
      status = push(stack, tmpLexeme);
    }
  } else if (str[i] == '-') {
    if (i == 0 || (str[i - 1] == '(')) {
      Lexeme tmpLexeme = {0, NUM, 0};
      status = push(stack, tmpLexeme);
      tmpLexeme.value = '-';
      tmpLexeme.type = MINUS;
      tmpLexeme.priority = 1;
      status = push(stack, tmpLexeme);
      *minusSign = 0;
    } else {
      Lexeme tmpLexeme = {'-', MINUS, 1};
      status = push(stack, tmpLexeme);
    }
  }
  return status;
}

int setSecondPriority(char* str, Stack* stack, int* i) {
  int status = OK;
  if (str[*i] == '*') {
    Lexeme tmpLexeme = {'*', MULT, 2};
    status = push(stack, tmpLexeme);
  } else if (str[*i] == '/') {
    Lexeme tmpLexeme = {'/', DIV, 2};
    status = push(stack, tmpLexeme);
  } else if (str[*i] == 'm') {
    Lexeme tmpLexeme = {'m', MOD, 2};
    status = push(stack, tmpLexeme);
    *i = *i + 2;
  }
  return status;
}

int setThirdPriority(char* str, Stack* stack, int i) {
  int status = OK;
  if (str[i] == '^') {
    Lexeme tmpLexeme = {'^', EXP, 3};
    status = push(stack, tmpLexeme);
  }
  return status;
}

int setFourthPriority(char* str, Stack* stack, int* i) {
  int status = OK;
  if (str[*i] == 'c') {
    Lexeme tmpLexeme = {'c', COS, 4};
    status = push(stack, tmpLexeme);
    *i += 2;
  } else if (str[*i] == 't') {
    Lexeme tmpLexeme = {'t', TAN, 4};
    status = push(stack, tmpLexeme);
    *i += 2;
  } else if (str[*i] == 's') {
    if (str[*i + 1] == 'i') {
      Lexeme tmpLexeme = {'s', SIN, 4};
      status = push(stack, tmpLexeme);
      *i += 2;
    } else {
      Lexeme tmpLexeme = {'q', SQRT, 4};
      status = push(stack, tmpLexeme);
      *i += 3;
    }
  } else if (str[*i] == 'l') {
    if (str[*i + 1] == 'o') {
      Lexeme tmpLexeme = {'L', LOG, 4};
      status = push(stack, tmpLexeme);
      *i += 2;
    } else {
      Lexeme tmpLexeme = {'l', LN, 4};
      status = push(stack, tmpLexeme);
      *i += 1;
    }
  } else if (str[*i] == 'a') {
    if (str[*i + 1] == 's') {
      Lexeme tmpLexeme = {'S', ASIN, 4};
      status = push(stack, tmpLexeme);
    } else if (str[*i + 1] == 'c') {
      Lexeme tmpLexeme = {'C', ACOS, 4};
      status = push(stack, tmpLexeme);
    } else {
      Lexeme tmpLexeme = {0, ATAN, 4};
      status = push(stack, tmpLexeme);
    }
    *i += 3;
  }
  return status;
}