#ifndef SRC_CALC_H
#define SRC_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0
#define OK 1
#define MEMORY_ERROR 4

typedef struct Node {
  double data;
  int type;
  int priority;
  struct Node* next;
} Node;

typedef struct Stack {
  Node* top;
} Stack;

typedef enum type_operation {
  NUM,
  X,
  L_BRACKET,
  R_BRACKET,
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
} type_operation;

void print_stack(Stack* stack);

void initStack(Stack* stack);
int push(Stack* stack, double data, int type, int priority);
double pop(Stack* stack);

int validateStr(char* str);
int checkDots(char* str);
int validateBrackets(char* str);
int validateBracketsPosition(char* str);
int validateOperators(char* str);
int validateTrig(char* str);

int inputStrToStack(char* str, Stack* stack);
int getNumber(char* str, Stack* stack, char* buffer, int* i, int* minusSign, int* plusSign);

int processZeroPriority(char* str, Stack* stack, int i);
int processFirstPriority(char* str, Stack* stack, int i, int* minusSign, int* plusSign);
int processSecondPriority(char* str, Stack* stack, int* i);
int processThirdPriority(char* str, Stack* stack, int i);
int processFourthPriority(char* str, Stack* stack, int* i);

void infixToPostfix(Stack* infixStack, Stack* bufferStack, Stack* postfixStack);
int reverseForRpn(Stack* inputStack, Stack* reversedStack);
int processing(char* str, double* result, double x);
double calculateResult(Stack* inputRpnList, double x);
#endif  // SRC_CALC_H
