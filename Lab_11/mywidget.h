#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>
#include <QMenu>

#include "AbstractFigure.h"
//#include "ui_mainwindow.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

    std::list<std::shared_ptr<AbstractFigure>> figureList;
    std::vector<bool> selectedFiguresVector;

public slots:
    void deleteFigure();

signals:
     void figureClicked();


protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QBrush brush = QBrush(Qt::gray,Qt::SolidPattern);
    std::list<std::shared_ptr<AbstractFigure>>::iterator deleteFigListIt = figureList.begin();
    std::vector<bool>::iterator deleteSelectedFigListIt = selectedFiguresVector.begin();
    std::shared_ptr<AbstractFigure> draggedFigure = nullptr;
    bool mouseHold;

public slots:

};
#endif // MYWIDGET_H
