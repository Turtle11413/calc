#include "credit.h"

double s21_pow(double value, int exp) {
  double result = value;
  for (int i = 0; i < exp; ++i) {
    result *= value;
  }
  return result;
}

void annuity_loan(double loan, int period, double annual_perc, double* monthly_payment, double* overpayment, double* total) {
  double monthly_perc = annual_perc / (12 * 100);
  *monthly_payment = loan * (monthly_perc + (monthly_perc) / (s21_pow(1 + monthly_perc, period - 1) - 1));
  *total = period * (*monthly_payment);
  *overpayment = *total - loan;
}

void diff_loan(double loan, int period, double annual_perc, double* first_payment, double* last_payment, double* overpayment, double* total) {
  double monthly_perc = annual_perc / (12 * 100);
  *first_payment = monthly_perc * loan + loan / period;
  *last_payment = (monthly_perc * loan) / period + loan / period;

  *total = (monthly_perc * loan * (period + 1) / 2) + loan;
  *overpayment = *total - loan;
}

void calculate(double loan, int period, double annual_perc, int mod) {
  double overpayment = 0;
  double total = 0;
  if (mod == 0) {
    double monthly_payment = 0;
    annuity_loan(loan, period, annual_perc, &monthly_payment, &overpayment, &total);
    printf("monthly = %f\n", monthly_payment);
    printf("overpay = %f\n", overpayment);
    printf("total = %f\n", total);
  }
  else if (mod == 1) {
    double first_payment = 0;
    double last_payment = 0;
    diff_loan(loan, period, annual_perc, &first_payment, &last_payment, &overpayment, &total);
    printf("monthly = %f ... %f\n", first_payment, last_payment);
    printf("overpay = %f\n", overpayment);
    printf("total = %f\n", total);
  }
}