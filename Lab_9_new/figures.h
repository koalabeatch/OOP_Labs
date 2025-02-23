#ifndef FIGURES_H
#define FIGURES_H

#include "AbstractFigure.h"

class Rectangle: public AbstractFigure{
public:
    Rectangle(int left, int top, int width, int height);

    void drawFigure(QPainter& p) override;

private:
    int left;
    int top;
    int width;
    int height;
};

class Ellipse: public AbstractFigure{
public:
    Ellipse(int xCentre, int yCentre, int width, int height);

    void drawFigure(QPainter& p) override;

private:
    int xCentre;
    int yCentre;
    int width;
    int height;
};

class Triangle: public AbstractFigure{
public:
    Triangle(QPoint point1, QPoint point2, QPoint point3);
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3);

    void drawFigure(QPainter& p) override;

private:
    QPoint point1;
    QPoint point2;
    QPoint point3;
    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
};
#endif // FIGURES_H
