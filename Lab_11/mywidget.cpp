#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}


void MyWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    int k = 0;
    for (std::shared_ptr<AbstractFigure> i : figureList) {
        if (selectedFiguresVector[k]) brush = QBrush(Qt::lightGray,Qt::SolidPattern);
        else                          brush = QBrush(Qt::gray,Qt::SolidPattern);
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
    if (mouseHold) {
        if (draggedFigure!=nullptr){
            draggedFigure->moveTo(event->position().x(),event->position().y());
            update();
        }
    }
}

void MyWidget::deleteFigure()
{
    figureList.erase(deleteFigListIt);
    deleteFigListIt = figureList.begin();

    selectedFiguresVector.erase(deleteSelectedFigListIt);
    deleteSelectedFigListIt = selectedFiguresVector.begin();

    update();
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mouseHold = true;
        unsigned k = 0;
        for (std::shared_ptr<AbstractFigure> i : figureList) {
            if (selectedFiguresVector[k]){
                draggedFigure = i;
                emit figureClicked();
                break;
            }
            else draggedFigure = nullptr;
            k++;
        }
    }
//        while (k < selectedFiguresVector.size()){
//            if (selectedFiguresVector[k]){

//                emit figureClicked();
//            }
//            k++;



    if (event->button() == Qt::RightButton){
        unsigned k = 0;
        bool isFigurePointed = false;
        while (k < selectedFiguresVector.size()){
            if (selectedFiguresVector[k]){
                isFigurePointed = true;
                break;
            }
            k++;
        }
        if (isFigurePointed){
            deleteFigListIt = std::next(figureList.begin(), k);
            deleteSelectedFigListIt = std::next(selectedFiguresVector.begin(), k);
            std::unique_ptr<QMenu> figureMenu = std::make_unique<QMenu>();
            figureMenu->addAction("Удалить", this, SLOT(deleteFigure()));
            figureMenu->exec(this->mapToGlobal(event->pos()));
        }

    }

}

void MyWidget::mouseReleaseEvent(QMouseEvent *event){
    mouseHold = false;
}
