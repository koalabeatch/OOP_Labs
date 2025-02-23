#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include "csvwriter.h"
#include "JSONReader.h"
#include <QFileDialog>
#include <QString>


bool operator==(const flm lhs, const flm rhs)
{
    unsigned lhsYear = lhs.yearRelease;
    unsigned rhsYear = rhs.yearRelease;
    if (lhsYear == rhsYear){ return true; }
    else                 { return false; }
}
bool operator>(const flm lhs, const flm rhs)
{
    unsigned lhsYear = lhs.yearRelease;
    unsigned rhsYear = rhs.yearRelease;
    if (lhsYear > rhsYear){ return true; }
    else                 { return false; }
}
bool operator<(const flm lhs, const flm rhs)
{
    unsigned lhsYear = lhs.yearRelease;
    unsigned rhsYear = rhs.yearRelease;
    if (lhsYear < rhsYear){ return true; }
    else                 { return false; }
}

void operator<<(QTextBrowser* brow, const QString text)
{
    brow->append(text);
}


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

QColor rusColorToQColor(QString rusColor)
{
    if (rusColor.toStdString() == "Черный")
    {
        return QColor(0,0,0);
    }
    else if (rusColor.toStdString() == "Красный")
    {
        return QColor(255,0,0);
    }
    else if (rusColor.toStdString() == "Зеленый")
    {
        return QColor(0,255,0);
    }
    else if (rusColor.toStdString() == "Синий")
    {
        return QColor(0,0,255);
    }
    else
    {
        return QColor(76,65,42);
    }
}


void MainWindow::opener(AbstractReader* abs)
{
    if (abs)
    {
        films = abs->readAll();
    }
}

void MainWindow::browse()
{
    fileName = QFileDialog::getOpenFileName(this,
      tr("Open Image"), "/home/films", tr("Image Files (*.json *.csv)"));
    //CsvWriter csw(fileName.toStdString());
    if (fileName.contains(".csv")){

        CsvReader csv(fileName.toStdString());
        try{
            opener(&csv);
        }
        catch (const std::exception& e) {
            ui->textBrowser->append(QString::fromStdString(std::string(("Exception caught: " + std::string(e.what()) +
                                                                        "\nin line: " + std::to_string(csv.getLineNum()) +
                                                                        "\nPlease, correct this error in your file.\n"))));
            films.clear();
        }
    }
    else if (fileName.contains(".json")){
        JSONReader jsn(fileName.toStdString());
        opener(&jsn);
    }
    max_id= films.size()+1;
    // ui->textBrowser->clear();
    QString browseColor = ui->comboBoxBrowseColor->currentText();

    for(auto f: films){
        ui->textBrowser << (QString::number(f.id) + ";" +
                           QString::fromStdString(f.name) + ";" +
                           QString::number(f.genre) + ";" +
                           QString::number(f.yearRelease));
    }

}

void MainWindow::search()
{

    QString searchText = ui->lineSearch->text();

    ui->textBrowser->clear();
    QString searchColor = ui->comboBoxSearchColor->currentText();

    if (searchText == "-1") {
        for (const auto& f: films) {
            ui->textBrowser->append(QString::number(f.id) + ";" +
                                    QString::fromStdString(f.name) + ";" +
                                    QString::number(f.genre) + ";" +
                                    QString::number(f.yearRelease),rusColorToQColor(searchColor));
            }
    }
    else{
        for (const auto& f: films) {
                if ((QString::number(f.id) == searchText) or
                        (QString::fromStdString(f.name) == searchText) or
                        (QString::number(f.genre) == searchText) or
                        (QString::number(f.yearRelease) == searchText)) {
                    ui->textBrowser->append(QString::number(f.id) + ";" +
                                            QString::fromStdString(f.name) + ";" +
                                            QString::number(f.genre) + ";" +
                                            QString::number(f.yearRelease),rusColorToQColor(searchColor));
                }
            }
    }
}

void MainWindow::add_film()
{
    CsvWriter csw(fileName.toLatin1().data());
    QString nameText = ui->lineName->text();
    QString genre = ui->comboBoxFilmGenre->currentText();
    QString yearRelease = ui->lineYearRelease->text();
    flm film;
    film.id = max_id;
    film.name = nameText.toStdString();
    film.genre = csw.rusGenreToEnum(genre);
    film.yearRelease = yearRelease.toInt();
    if (film.name.empty() or film.yearRelease<1888){
        //pass
    }
    else{
        films.push_back(film);
        max_id= films.size()+1;
        QString addColor = ui->comboBoxAddFigColor->currentText();
        ui->textBrowser->append(QString::number(film.id) + ";" +
                                QString::fromStdString(film.name) + ";" +
                                QString::number(film.genre) + ";" +
                                QString::number(film.yearRelease),rusColorToQColor(addColor));
    if (fileName.contains(".csv")){
        csw.writeAll(films);
    }
    }
}

void MainWindow::checkYears()
{
    QString lhsText = ui->lineLhs->text();
    QString rhsText = ui->lineRhs->text();
    QString compareSymbol = ui->comboBoxCompare->currentText();
    if (lhsText.isEmpty() or rhsText.isEmpty() or compareSymbol.isEmpty()){ ui->lineComparison->setText("Недостаточно информации");}
    else
    {
        bool lhsOk;
        bool rhsOk;
        int lhsId = lhsText.toInt(&lhsOk, 10);
        int rhsId = rhsText.toInt(&rhsOk, 10);
        if (!lhsOk or !rhsOk){ ui->lineComparison->setText("Это не номера фильмов");}
        else if (lhsId<0 or lhsId>=max_id or rhsId<0 or rhsId>=max_id){ ui->lineComparison->setText("Фильмов с такими номерами нет");}
        else
        {
            flm lhsFilm = films[lhsId-1];
            flm rhsFilm = films[rhsId-1];
            if (compareSymbol == ">")
            {
             if (lhsFilm>rhsFilm){ui->lineComparison->setText("Да");}
             else                {ui->lineComparison->setText("Нет");}
            }
            if (compareSymbol == "=")
            {
             if (lhsFilm==rhsFilm){ui->lineComparison->setText("Да");}
             else                {ui->lineComparison->setText("Нет");}
            }
            if (compareSymbol == "<")
            {
             if (lhsFilm<rhsFilm){ui->lineComparison->setText("Да");}
             else                {ui->lineComparison->setText("Нет");}
            }
        }
    }
}
void MainWindow::add_fig()
{

//    CsvWriter csw(fileName.toLatin1().data());

//    QString nameText = ui->lineName->text();
//    QString formText = ui->lineForm->text();
//    QString color = ui->comboBoxFigColor->currentText();

//    fig film;

//    film.id = max_id;
//    film.name = nameText.toStdString();
//    film.form = formText.toStdString();
//    film.color = csw.rusColortoEnum(color);
//    if (film.name.empty() or film.form.empty() or film.color == -1 ){
//        //pass
//    }
//    else{
//        films.push_back(film);
//        max_id= films.size()+1;

//        QString addColor = ui->comboBoxAddFigColor->currentText();

//        ui->textBrowser->append(QString::number(film.id) + ";" +
//                                QString::fromStdString(film.name) + ";" +
//                                QString::fromStdString(film.form) + ";" +
//                                QString::number(film.color),rusColorToQColor(addColor));
//    if (fileName.contains(".csv")){
//        csw.writeAll(films);
//    }
//    }
}


