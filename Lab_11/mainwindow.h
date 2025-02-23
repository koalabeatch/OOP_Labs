#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>

#include "AbstractFigure.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void changeInformation();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::list<AbstractFigure*> figureList;
private:

    std::list<std::shared_ptr<AbstractFigure>> figures;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
