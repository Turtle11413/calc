#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this); ui->lineEdit->setReadOnly(true);

    connect(ui->Button_number_1, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_2, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_3, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_4, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_5, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_6, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_7, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_8, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_number_9, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->Button_AC, SIGNAL(clicked()), this, SLOT(clear_all()));
    connect(ui->Button_CE, SIGNAL(clicked()), this, SLOT(on_pushButton_CE()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->lineEdit->text() + button->text();
  ui->lineEdit->setText(new_label);
}

void MainWindow::pushButtonAC() { ui->lineEdit->setText(""); }

void MainWindow::pushButtonCE() {
  QString text = ui->lineEdit->text();
  if (!text.isEmpty()) {
    text.chop(1);
    ui->lineEdit->setText(text);
  }
}

void MainWindow::arithmeticsOperations() {
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}
