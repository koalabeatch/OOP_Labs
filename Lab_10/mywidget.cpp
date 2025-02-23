#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}


void MyWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    int k = 0;
    for (std::shared_ptr<AbstractFigure> i : figureList) {
        if (selectedFiguresVector[k]) brush = QBrush(Qt::lightGray,Qt::SolidPattern);
        else                  brush = QBrush(Qt::gray,Qt::SolidPattern);
        painter.setBrush(brush);
        i->drawFigure(painter);
        k++;
    }
    painter.end();
}


void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    int k = 0;
    for (std::shared_ptr<AbstractFigure> i : figureList) {
        if(i->isPointInside(event->position().x(),event->position().y()))   selectedFiguresVector[k] = true;
        else                                                                selectedFiguresVector[k] = false;
        k++;
        update();
    }
}


void MyWidget::mousePressEvent(QMouseEvent *event)
{
    unsigned k = 0;
    while (k < selectedFiguresVector.size()){
        if (selectedFiguresVector[k]) emit figureClicked();
        k++;
    }
}

