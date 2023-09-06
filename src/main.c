#include "backend/calc.h"

int main() {

  char *str = "1 + 1";
  double cur = 01. + 2;
  double res = 0;
  int err = processing(str, &res, 0);
  printf("res = %.10f\n", res);
  printf("cur = %.10f\n", cur);
  printf("ok = %d\n", err);

}
