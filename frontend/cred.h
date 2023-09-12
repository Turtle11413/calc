#ifndef CRED_H
#define CRED_H

#include <QWidget>

extern "C" {
#include <../backend/credit.h>
}

namespace Ui {
class Cred;
}

class Cred : public QWidget {
  Q_OBJECT

 public:
  explicit Cred(QWidget *parent = nullptr);
  ~Cred();

 signals:
  void firstWindow();

 private slots:

  void on_pushButton_calculator_clicked();
  void on_pushButton_clicked();

 private:
  Ui::Cred *ui;
};

#endif  // CRED_H
