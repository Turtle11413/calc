#include "mainwindow.h"

#include <time.h>

#include <QVector>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QWidget::setWindowTitle("Calculator");

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(pushButton()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_exp, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_LBR, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_RBR, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(pushButton()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(pushButton()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(pushButtonAC()));
  connect(ui->pushButton_CE, SIGNAL(clicked()), this, SLOT(pushButtonCE()));

  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(pushButton_EQ()));

  credit = new Cred;
  connect(credit, &Cred::firstWindow, this, &MainWindow::show);
  ui->customPlot->xAxis->setRange(-10, 10);
  ui->customPlot->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::pushButton() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->label->text() + button->text();
  ui->label->setText(new_label);
}

void MainWindow::pushBUttonTrig() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->label->text() + button->text();
  ui->label->setText(new_label + "(");
}

void MainWindow::pushButtonAC() { ui->label->setText(""); }

void MainWindow::pushButtonCE() {
  QString text = ui->label->text();
  if (!text.isEmpty()) {
    text.chop(1);
    ui->label->setText(text);
  }
}

void MainWindow::pushButton_EQ() {
  std::string text = ui->label->text().toStdString();
  char *str = &text[0];
  if (strstr(str, "INCORRECT INPUT") == NULL && strstr(str, "nan") == NULL &&
      strstr(str, "inf") == NULL && strstr(str, "MEMORY ERROR") == NULL) {
    double x = ui->doubleSpinBox_x->text().toDouble();
    double result = 0;
    int status = from_answer(str, &result, x);
    if (status == OK) {
      QString new_label = QString::number(result);
      ui->label->setText(new_label);
    } else if (status == INCORRECT_INPUT) {
      QString new_label = "INCORRECT INPUT";
      ui->label->setText(new_label);
    } else if (status == CALCULATION_ERROR) {
      QString new_label = "CALCULATION ERROR";
      ui->label->setText(new_label);
    } else if (status == MEMORY_ERROR) {
      QString new_label = "MEMORY ERROR";
      ui->label->setText(new_label);
    } else if (status == NAN_RESULT) {
      QString new_label = "nan";
      ui->label->setText(new_label);
    } else if (status == INF_RESULT) {
      QString new_label = "inf";
      ui->label->setText(new_label);
    }
  } else {
    QString new_label = "INCORRECT INPUT";
    ui->label->setText(new_label);
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  credit->show();
  this->close();
}

void MainWindow::on_pushButton_graph_clicked() {
  ui->customPlot->addGraph();
  ui->customPlot->graph(0)->setPen(QPen(Qt::black));

  double minX = ui->doubleSpinBox_minX->text().toDouble();
  double maxX = ui->doubleSpinBox_maxX->text().toDouble();
  double minY = ui->doubleSpinBox_minY->text().toDouble();
  double maxY = ui->doubleSpinBox_maxY->text().toDouble();

  QVector<double> x, y;
  double yCur = 0;

  for (double xCur = minX; xCur < maxX; xCur += 0.1) {
    std::string text = ui->label->text().toStdString();
    char *str = &text[0];
    from_answer(str, &yCur, xCur);
    if (minY <= yCur && yCur <= maxY) {
      x.push_back(xCur);
      y.push_back(yCur);
    }
  }

  ui->customPlot->xAxis2->setVisible(true);
  ui->customPlot->xAxis2->setTickLabels(false);
  ui->customPlot->yAxis2->setVisible(true);
  ui->customPlot->yAxis2->setTickLabels(false);

  ui->customPlot->xAxis->setRange(minX, maxX);
  ui->customPlot->yAxis->setRange(minY, maxY);

  connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
          ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
          ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

  ui->customPlot->graph(0)->setData(x, y);
  ui->customPlot->graph(0)->rescaleAxes();

  ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                  QCP::iSelectPlottables);
  ui->customPlot->replot();
}
