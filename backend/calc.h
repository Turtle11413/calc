#ifndef SRC_CALC_H
#define SRC_CALC_H

#ifdef __cplusplus

extern "C" {

#endif

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define CALCULATION_ERROR 1
#define MEMORY_ERROR 2
#define INCORRECT_INPUT 3
#define NAN_RESULT 4
#define INF_RESULT 5

typedef struct Lexeme {
  double value;
  int type;
  int priority;
} Lexeme;

typedef enum lexeme_type {
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
} lexeme_type;

typedef struct Node {
  Lexeme lexeme;
  struct Node* next;
} Node;

typedef struct Stack {
  Node* top;
} Stack;

// -------------------- stack --------------------------
void initStack(Stack* stack);
int push(Stack* stack, Lexeme addLexeme);
double pop(Stack* stack);
int isEmpty(Stack* stack);
void destroyStack(Stack* stack);
// -----------------------------------------------------

// -------------------- validate string ----------------
int validateStr(char* str);
int validateDots(char* str);
int validateBrackets(char* str);
int validateBracketsPosition(char* str);
int validateOperators(char* str);
int validateTrig(char* str);
int validateOtherFuncs(char* str);
int validateX(char* str);
// -----------------------------------------------------

// -------------------- set priority -------------------
int setZeroPriority(char* str, Stack* stack, int i);
int setFirstPriority(char* str, Stack* stack, int i, int* unaryMinus,
                     int* unaryPlus);
int setSecondPriority(char* str, Stack* stack, int* i);
int setThirdPriority(char* str, Stack* stack, int i);
int setFourthPriority(char* str, Stack* stack, int* i);
// -----------------------------------------------------

// --------------------- rpn ----------------------------
int parseToStack(char* str, Stack* stack);
int reverseStack(Stack* inputStack, Stack* reversedStack);
int getNumber(char* str, Stack* stack, int* i, int* unaryMinus, int* unaryPlus);
int getPostfix(Stack* infixStack, Stack* bufferStack, Stack* postfixStack);
// -------------------------------------------------------

// -------------------- calculate ------------------------
int calculateResult(Stack* rpn, double x, double* result);
double calculateTrig(Lexeme* operation, Lexeme* number);
double calculateSimpleOperation(Lexeme* operation, double firstNumber,
                                double secondNumber);
// -------------------------------------------------------

//-------------------------------------------------------
int from_answer(char* str, double* result, double x);
//-------------------------------------------------------

#ifdef __cplusplus
}

#endif

#endif
