#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"

#include <QFileDialog>
#include <QString>

enum {Romantic = 0, Thriller = 1, Fantasy = 2, Action = 3 };

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

void MainWindow::browse()
{
    QString fileName = QFileDialog::getOpenFileName(this,
      tr("Open Image"), "/home/jana", tr("Image Files (*.csv)"));
    //ui->textBrowser->append(fileName);
    int k = 0;
    CsvReader csv(fileName.toStdString());
    if (csv.is_open()) {
        films = csv.readAll();
    }
    for(auto f: films){
        ui->textBrowser->append(QString::number(f.id) + ";" + QString::fromStdString(f.name) + ";" + QString::number(f.genre) + ";" + QString::number(f.year_release));
        k++;
    }
}

void MainWindow::search()
{

    QString searchText = ui->lineSearch->text();
    ui->textBrowser->clear();
    if (searchText == "-1") {
        for (const auto& f: films) {
                    ui->textBrowser->append(QString::number(f.id) + ";" + QString::fromStdString(f.name) + ";" + QString::number(f.genre) + ";" + QString::number(f.year_release));
            }
    }
    else{
        for (const auto& f: films) {
                if ((QString::number(f.id) == searchText) or (QString::fromStdString(f.name) == searchText) or (QString::number(f.genre) == searchText) or (QString::number(f.year_release) == searchText)) {
                    ui->textBrowser->append(QString::number(f.id) + ";" + QString::fromStdString(f.name) + ";" + QString::number(f.genre) + ";" + QString::number(f.year_release));
                }
            }
    }
}

void MainWindow::magic()
{

    ui->textBrowser->clear();
    for (const auto& f: films) {
            if ((f.genre == Romantic) and (f.year_release > 2010)) {
                ui->textBrowser->append(QString::number(f.id) + ";" + QString::fromStdString(f.name) + ";" + QString::number(f.genre) + ";" + QString::number(f.year_release));
            }
        }
}

void MainWindow::yearSort()
{
    int block = 0;

    if ((flip == 1) and (block == 0)){
        std::sort(films.begin(),films.end(), [](const flm& lhs, const flm& rhs){
                return lhs.year_release > rhs.year_release;});
        flip = 0;
        block = 1;
    }
    if ((flip == 0) and (block == 0)){
        std::sort(films.begin(),films.end(), [](const flm& lhs, const flm& rhs){
                return lhs.year_release < rhs.year_release;});
        flip = 1;
        block = 1;
    }
    std::ofstream fout("films_sorted.csv");
    if (fout.is_open()){
        for (const auto& f: films) {
            fout << f.id << ";" << f.name << ";" << f.year_release << ";" << std::endl ;
        }
    }
    ui->textBrowser->clear();
    for (const auto& f: films) {
                ui->textBrowser->append(QString::number(f.id) + ";" + QString::fromStdString(f.name) + ";" + QString::number(f.genre) + ";" + QString::number(f.year_release));
        }
}

