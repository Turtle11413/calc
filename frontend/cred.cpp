#include "cred.h"

#include "ui_cred.h"

Cred::Cred(QWidget *parent) : QWidget(parent), ui(new Ui::Cred) {
  ui->setupUi(this);
  QWidget::setWindowTitle("Credit calculator");
}

Cred::~Cred() { delete ui; }

void Cred::on_pushButton_calculator_clicked() {
  this->close();
  emit firstWindow();
}

void Cred::on_pushButton_clicked() {
  double loan = ui->doubleSpinBox_loan->text().toDouble();
  double rate = ui->doubleSpinBox_rate->text().toDouble();
  int period = ui->spinBox_period->text().toInt();

  if (ui->radioButton_Annuity->isChecked()) {
    double monthly_payment = 0;
    double overpayment = 0;
    double total = 0;

    annuity_loan(loan, period, rate, &monthly_payment, &overpayment, &total);

    ui->label_monthly_payment->setText(
        QString("%L1").arg(monthly_payment, 0, 'f', 2));
    ;
    ui->label_overpayment->setText(QString("%L1").arg(overpayment, 0, 'f', 2));
    ui->label_total->setText(QString("%L1").arg(total, 0, 'f', 2));

  } else if (ui->radioButton_Diff->isChecked()) {
    double first_payment = 0;
    double last_payment = 0;
    double overpayment = 0;
    double total = 0;

    diff_loan(loan, period, rate, &first_payment, &last_payment, &overpayment,
              &total);

    ui->label_monthly_payment->setText(
        QString("%L1").arg(first_payment, 0, 'f', 2) + " ... " +
        QString("%L1").arg(last_payment, 0, 'f', 2));
    ui->label_overpayment->setText(QString("%L1").arg(overpayment, 0, 'f', 2));
    ui->label_total->setText(QString("%L1").arg(total, 0, 'f', 2));
  }
}
