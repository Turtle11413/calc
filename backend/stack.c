#include "calc.h"

void initStack(Stack* stack) { stack->top = NULL; }

int push(Stack* list, Lexeme addLexeme) {
  int status = OK;
  Node* newNode = malloc(sizeof(Node));
  if (newNode != NULL) {
    newNode->lexeme = addLexeme;
    newNode->next = list->top;
    list->top = newNode;
  } else {
    status = MEMORY_ERROR;
  }
  return status;
}

double pop(Stack* stack) {
  double rtn = 0.;
  if (stack->top != NULL) {
    rtn = stack->top->lexeme.value;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
  }
  return rtn;
}