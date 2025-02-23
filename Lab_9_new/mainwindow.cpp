#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include "mywidget.h"
#include "figures.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::list<AbstractFigure*> figures;

    figures.push_back(new Rectangle(150,150,100,100));
    figures.push_back(new Ellipse(200,50,100,100));
    figures.push_back(new Triangle(150,150,250,150,200,100));
    ui->centralwidget->figureList = figures;
}

MainWindow::~MainWindow()
{
    delete ui;
}


