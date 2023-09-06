#include "calc.h"

void initStack(Stack* stack) { stack->top = NULL; }

int push(Stack* list, double data, int type, int priority) {
  int status = OK;
  Node* newNode = malloc(sizeof(Node));
  if (newNode != NULL) {
    newNode->data = data;
    newNode->type = type;
    newNode->priority = priority;
    newNode->next = list->top;
    list->top = newNode;
  } else {
    status = MEMORY_ERROR;
  }
  return status;
}

double pop(Stack* stack) {
  if (stack->top == NULL) {
    return 0;
  }
  double data = stack->top->data;
  Node* temp = stack->top;
  stack->top = stack->top->next;
  free(temp);
  return data;
}
