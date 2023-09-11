#include "backend/calc.h"

int main() {

  char *str = "sqrt(1)";
  double cur = sqrt(1);
  double res = 0;
  int err = from_answer(str, &res, 0);
  printf("res = %.10f\n", res);
  printf("cur = %.10f\n", cur);
  printf("ok = %d\n", err);
}

//#include "backend/credit.h"
//
//int main() {
//
//  double loan = 500000;
//  int period = 10;
//  double annual_perc = 7.9;
//  int mod = 1;
//  calculate(loan, period, annual_perc, mod);
//
//}