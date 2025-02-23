#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include "csvreader.h"
// #include "AbstractReader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void opener(AbstractReader* abs);
    //QColor rusColorToQColor(QString rusColor);

public slots:
    void browse();
    void search();
    void add_fig();
    void add_film();
    void checkYears();
private:
    enum colors {Blue = 0, Green = 1, Red = 2, Black = 3 };
    enum genres {Romantic = 0, Thriller = 1, Fantasy = 2, Action = 3 };
    int flip = 0;
    unsigned max_id = 1;
    Ui::MainWindow *ui;
    std::vector<flm> films;
    QString fileName;
};
#endif // MAINWINDOW_H
