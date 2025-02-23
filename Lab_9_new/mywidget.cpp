#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}


void MyWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    for (AbstractFigure* i : figureList) {
        i->drawFigure(painter);
    }
    painter.end();
}



