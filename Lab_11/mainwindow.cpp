#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figures.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<bool> selectedFiguresVector;

    figures.push_back(std::make_unique<Rectangle>(150,150,100,100));
    selectedFiguresVector.push_back(false);

    figures.push_back(std::make_unique<Ellipse>(150,10,100,100));
    selectedFiguresVector.push_back(false);

    figures.push_back(std::make_unique<Triangle>(150,150,250,150,200,100));
    selectedFiguresVector.push_back(false);

    ui->canvas->figureList = figures;
    ui->canvas->selectedFiguresVector = selectedFiguresVector;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeInformation(){
    ui->informationTable->clear();
    int k = 0;
    for (std::shared_ptr<AbstractFigure> i : ui->canvas->figureList) {
        if (ui->canvas->selectedFiguresVector[k])  ui->informationTable->append(i->getInformation());
        k++;
    }
}

