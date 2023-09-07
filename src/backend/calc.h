#ifndef SRC_CALC_H
#define SRC_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define CALCULATION_ERROR 1
#define MEMORY_ERROR 2
#define INCORRECT_INPUT 3

typedef struct Node {
  double data;
  int type;
  int priority;
  struct Node* next;
} Node;

typedef struct Stack {
  Node* top;
} Stack;

typedef enum lexem_type {
  NUM,
  X,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  PLUS,
  MINUS,
  MULT,
  DIV,
  EXP,
  MOD,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG
} lexem_type;

// -------------------- stack --------------------
void initStack(Stack* stack);
int push(Stack* stack, double data, int type, int priority);
double pop(Stack* stack);
// ------------------------------------------------

// -------------------- validate string --------------------
int validateStr(char* str);
int validateDots(char* str);
int validateBrackets(char* str);
int validateBracketsPosition(char* str);
int validateOperators(char* str);
int validateTrig(char* str);
int validateOtherFuncs(char* str);
// ---------------------------------------------------------

// -------------------- set priority --------------------
int setZeroPriority(char* str, Stack* stack, int i);
int setFirstPriority(char* str, Stack* stack, int i, int* unaryMinus, int* unaryPlus);
int setSecondPriority(char* str, Stack* stack, int* i);
int setThirdPriority(char* str, Stack* stack, int i);
int setFourthPriority(char* str, Stack* stack, int* i);
// -------------------- calculate --------------------

// -------------------------------------------------------
int parseToStack(char* str, Stack* stack);
int reverseStack(Stack* inputStack, Stack* reversedStack);
int processing(char* str, double* result, double x);
int getNumber(char* str, Stack* stack, int* i, int* unaryMinus, int* unaryPlus);
int getPostfix(Stack* infixStack, Stack* bufferStack, Stack* postfixStack);
int getResult(Stack* inputRpnList, double x, double* result);
// ----------------------------------------------------

#endif  // SRC_CALC_H