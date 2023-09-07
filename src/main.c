#include "backend/calc.h"

int main() {

  char *str = "2x^2 + 1";
  double cur = 0;
  double res = 0;
  int err = from_answer(str, &res, 5);
  printf("res = %.10f\n", res);
  printf("cur = %.10f\n", cur);
  printf("ok = %d\n", err);
}
