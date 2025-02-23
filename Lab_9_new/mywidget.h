#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QPainter>
#include <QWidget>

#include "AbstractFigure.h"
//#include "mainwindow.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void getList(std::list<AbstractFigure*> figureList);
    std::list<AbstractFigure*> figureList;
protected:
    void paintEvent(QPaintEvent* event) override;

public slots:

};
#endif // MYWIDGET_H
