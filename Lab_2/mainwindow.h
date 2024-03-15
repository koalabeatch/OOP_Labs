#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "csvreader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void browse();
    void search();
    void magic();
    void yearSort();
private:
    int flip = 0;
    Ui::MainWindow *ui;
    std::vector<flm> films;
};
#endif // MAINWINDOW_H
