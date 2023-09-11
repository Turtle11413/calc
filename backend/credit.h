#ifndef CREDIT_H
#define CREDIT_H

#include <stdio.h>

#define OK 0
#define ERR 1

void diff_loan(double loan, int period, double annual_perc,
               double* first_payment, double* last_payment, double* overpayment,
               double* total);
void annuity_loan(double loan, int period, double annual_perc,
                  double* monthly_payment, double* overpayment, double* total);
double s21_pow(double value, int exp);

#endif