#include "backend/calc.h"

int main() {

  char *str = "2 / (3 + 2) * 5";
  double cur = 2 / (3 + 2) * 5;
  double res = 0;
  int err = processing(str, &res, 0);
  printf("res = %.10f\n", res);
  printf("cur = %.10f\n", cur);
  printf("ok = %d\n", err);

//  char* str = "00.12";
//  printf("num = %f\n", strtod(str, &str));
}
