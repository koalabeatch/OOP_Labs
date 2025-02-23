#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Point.h"
#include "QString"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


template<typename T>
T ArithmeticMean(std::vector<T> vec)
{
    T sum = T(0);
    for (T& i: vec){
        sum += i;
    }
    return sum/vec.size();
}
void MainWindow::calculateArithmeticMean()
{
    ui->lineXRes->clear();
    ui->lineYRes->clear();
    if(ui->radioButtonInt->isChecked()){
        int A = ui->lineXA->text().toInt();
        int B = ui->lineXB->text().toInt();
        std::vector<int> vec;
        vec.push_back(A);
        vec.push_back(B);
        ui->lineXRes->setText(QString::number(ArithmeticMean(vec)));
    }
    else if(ui->radioButtonFloat->isChecked()){
        double A = ui->lineXA->text().toDouble();
        double B = ui->lineXB->text().toDouble();
        std::vector<double> vec;
        vec.push_back(A);
        vec.push_back(B);
        ui->lineXRes->setText(QString::number(ArithmeticMean(vec)));
    }
    else{
        Point<double,double> A(ui->lineXA->text().toDouble(),ui->lineYA->text().toDouble());
        Point<double,double> B(ui->lineXB->text().toDouble(),ui->lineYB->text().toDouble());
        std::vector<Point<double,double>> vec;
        vec.push_back(A);
        vec.push_back(B);
        ui->lineXRes->setText(QString::number(ArithmeticMean(vec).getX()));
        ui->lineYRes->setText(QString::number(ArithmeticMean(vec).getY()));
    }


}

void MainWindow::changeLineEdits()
{
    if (ui->radioButtonInt->isChecked() or ui->radioButtonFloat->isChecked()){
        ui->lineYA->clear();
        ui->lineYB->clear();
        ui->lineYRes->clear();
        ui->lineYA->setReadOnly(true);
        ui->lineYB->setReadOnly(true);
    }
    else{
        ui->lineYA->setReadOnly(false);
        ui->lineYB->setReadOnly(false);
    }
}
