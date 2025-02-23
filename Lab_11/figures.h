#ifndef FIGURES_H
#define FIGURES_H

#include "AbstractFigure.h"
#include <QVector>

class Rectangle: public AbstractFigure{
public:
    Rectangle(int left, int top, int width, int height);

    void drawFigure(QPainter& p) override;
    bool isPointInside(int x, int y) override;
    QString getInformation() override;
    void move(int deltaX, int deltaY) override;
    void moveTo(int X, int Y) override;



private:
    int xLeft;
    int yTop;
    int width;
    int height;
    QRect rectangle;
};

class Ellipse: public AbstractFigure{
public:
    Ellipse(int xLeft, int yTop, int width, int height);

    void drawFigure(QPainter& p) override;
    bool isPointInside(int x, int y) override;
    QString getInformation() override;
    void move(int deltaX, int deltaY) override;
    void moveTo(int X, int Y) override;


private:
    int xLeft;
    int yTop;
    int xCenter;
    int yCenter;
    int width;
    int height;
    QRect ellipse;
};

class Triangle: public AbstractFigure{
public:
    Triangle(std::array<QPoint, 3> points);
    Triangle(int xA, int yA, int xB, int yB, int xC, int yC);

    float triSquare(int xA, int yA, int xB, int yB, int xC, int yC);

    void drawFigure(QPainter& p) override;
    bool isPointInside(int x, int y) override;
    QString getInformation() override;
    void move(int deltaX, int deltaY) override;
    void moveTo(int X, int Y) override;

private:
    std::array<QPoint, 3> points;
    int xA;
    int yA;
    int xB;
    int yB;
    int xC;
    int yC;
    QPolygon polygon;
};
#endif // FIGURES_H
