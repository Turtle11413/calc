#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cred.h>

#include <QMainWindow>

extern "C" {
#include <../backend/calc.h>
#include <../backend/credit.h>
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void pushButton();
  void pushButtonAC();
  void pushButtonCE();
  void pushBUttonTrig();
  void pushButton_EQ();

  void on_pushButton_credit_clicked();
  void on_pushButton_graph_clicked();

  //    double xBegin, xEnd, h, X;
  //    int N;

  //    QVector<double> x, y;

 private:
  Ui::MainWindow *ui;
  Cred *credit;
};

#endif  // MAINWINDOW_H
