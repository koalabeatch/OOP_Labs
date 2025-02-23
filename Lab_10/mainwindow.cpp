#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figures.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::list<std::shared_ptr<AbstractFigure>> figures;
    std::vector<bool> selectedFiguresVector;

    std::shared_ptr<Rectangle> Rect_ptr = std::make_shared<Rectangle>(150,150,100,100);
    figures.push_back(Rect_ptr);
    selectedFiguresVector.push_back(false);

    std::shared_ptr<Ellipse> Ell_ptr = std::make_shared<Ellipse>(150,10,100,100);
    figures.push_back(Ell_ptr);
    selectedFiguresVector.push_back(false);

    std::shared_ptr<Triangle> Tri_ptr = std::make_shared<Triangle>(150,150,250,150,200,100);
    figures.push_back(Tri_ptr);
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

