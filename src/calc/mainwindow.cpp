#include "mainwindow.h"
#include "ui_mainwindow.h"

//extern "C" {
//    #include "../github/calc/src/backend/calc.h"
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton_0,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_1,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_2,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_3,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_4,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_5,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_6,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_7,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_8,     SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_9,     SIGNAL(clicked()), this, SLOT(pushButton()));

    connect(ui->pushButton_plus,  SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_mult,  SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_div,   SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_exp,   SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_LBR,   SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_RBR,   SIGNAL(clicked()), this, SLOT(pushButton()));
    connect(ui->pushButton_dot,   SIGNAL(clicked()), this, SLOT(pushButton()));

    connect(ui->pushButton_sin,   SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_asin,  SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_cos,   SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_acos,  SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_tan,   SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_atan,  SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_log,   SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_ln,    SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_sqrt,  SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));
    connect(ui->pushButton_mod,   SIGNAL(clicked()), this, SLOT(pushBUttonTrig()));

    connect(ui->pushButton_AC,    SIGNAL(clicked()), this, SLOT(pushButtonAC()));
    connect(ui->pushButton_CE,    SIGNAL(clicked()), this, SLOT(pushButtonCE()));

//    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(pushButton_EQ()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


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

//void MainWindow::pushButton_EQ() {
//    std::string str = ui->label->text().toStdString();
//    //  std::string x_str = ui->value_x->text().toStdString();
//    char *expression = &str[0];
//    //  char *x_value = &x_str[0];
//    double res = 0.0;
//    double x = 0.0;
//    int check = OK;
//    check = processing(expression, &res, x);
//    QString num1 = QString::number(res, 'g', 9);
//    if (check == OK) {
//        ui->label->setText(num1);
//    } else {
//        ui->label->setText("ERROR");
//    }
//}
