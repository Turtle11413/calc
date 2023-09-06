#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

//    connect(ui->Button_number_1, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_2, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_3, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_4, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_5, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_6, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_7, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_8, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_number_9, SIGNAL(clicked()), this, SLOT(numbers()));
//    connect(ui->Button_AC, SIGNAL(clicked()), this, SLOT(clear_all()));
//    connect(ui->Button_CE, SIGNAL(clicked()), this, SLOT(on_pushButton_CE()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->label->text() + button->text();
  ui->label->setText(new_label);
}

void MainWindow::pushButtonAC() { ui->label->setText(""); }

void MainWindow::pushButtonCE() {
  QString text = ui->label->text();
  if (!text.isEmpty()) {
    text.chop(1);
    ui->label->setText(text);
  }
}

void MainWindow::arithmeticsOperations() {
    QPushButton *button = (QPushButton *)sender();
    ui->label->setText(ui->label->text() + button->text());
}
