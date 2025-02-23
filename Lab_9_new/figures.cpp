#include "figures.h"


Rectangle::Rectangle(int left, int top, int width, int height)
{
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
}

Ellipse::Ellipse(int xCentre, int yCentre, int width, int height)
{
    this->xCentre = xCentre;
    this->yCentre = yCentre;
    this->width = width;
    this->height = height;
}

Triangle::Triangle(QPoint point1, QPoint point2, QPoint point3)
{
    this->point1 = point1;
    this->point2 = point2;
    this->point3 = point3;
    this->x1 = point1.x();
    this->y1 = point1.y();
    this->x2 = point2.x();
    this->y2 = point2.y();
    this->x3 = point3.x();
    this->y3 = point3.y();
}

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->x3 = x3;
    this->y3 = y3;
    this->point1 = QPoint(x1,y1);
    this->point2 = QPoint(x2,y2);
    this->point3 = QPoint(x3,y3);
}


void Rectangle::drawFigure(QPainter& p)
{
    p.drawRect(left, top, width, height);
}

void Ellipse::drawFigure(QPainter &p)
{
    QPoint Center = QPoint(xCentre,yCentre);
    p.drawEllipse(Center, width/2, height/2);
}

void Triangle::drawFigure(QPainter &p)
{
    static const QPoint points[3] = {
        point1,
        point2,
        point3
    };
    p.drawPolygon(points, 3);
}
