#include "figures.h"
#include "math.h"

Rectangle::Rectangle(int xLeft, int yTop, int width, int height)
{
    this->xLeft = xLeft;
    this->yTop = yTop;
    this->width = width;
    this->height = height;

    rectangle = QRect(xLeft, yTop, width, height);
}

Ellipse::Ellipse(int xLeft, int yTop, int width, int height)
{
    this->xLeft = xLeft;
    this->yTop = yTop;
    this->width = width;
    this->height = height;
    this->xCenter = xLeft + width/2;
    this->yCenter = yTop + height/2;

    ellipse = QRect(xLeft, yTop, width, height);
}

Triangle::Triangle(std::array<QPoint, 3> points)
{
    this->points = points;
    this->xA = points[0].x();
    this->yA = points[0].y();
    this->xB = points[1].x();
    this->yB = points[1].y();
    this->xC = points[2].x();
    this->yC = points[2].y();

    QVector<QPoint> vec;
    for (QPoint i: points){
        vec.push_back(i);
    }

    polygon = QPolygon(vec);
}

Triangle::Triangle(int xA, int yA, int xB, int yB, int xC, int yC)
{
    this->xA = xA;
    this->yA = yA;
    this->xB = xB;
    this->yB = yB;
    this->xC = xC;
    this->yC = yC;

    this->points = {QPoint(xA,yA),QPoint(xB,yB),QPoint(xC,yC)};

    QVector<QPoint> vec;
    for (QPoint i: points){
        vec.push_back(i);
    }

    polygon = QPolygon(vec);
}

float Triangle::triSquare(int Ax, int Ay, int Bx, int By, int Cx, int Cy)
{
    return abs(Bx*Cy - Cx*By - Ax*Cy + Cx*Ay + Ax*By - Bx*Ay);
}

void Rectangle::drawFigure(QPainter& p)
{
    p.drawRect(rectangle);
}

void Ellipse::drawFigure(QPainter &p)
{
    p.drawEllipse(ellipse);
}

void Triangle::drawFigure(QPainter &p)
{
    p.drawPolygon(polygon);
}

bool Rectangle::isPointInside(int x, int y)
{
    if ( x >= xLeft and
         x <= xLeft + width and
         y >= yTop and
         y <= yTop + height){ return true;}
    else {return false;}
}

bool Ellipse::isPointInside(int x, int y)
{
    int a = width/2;
    int b = height/2;
    int yc = yCenter;
    int xc = xCenter;
    if ( 4 * ( pow((x-xc)/a,2) + pow((y-yc)/b,2)) <= 1 ){ return true;}
    else {return false;}
}

bool Triangle::isPointInside(int aPx, int aPy)
{

    float s = triSquare(aPx, aPy, xA, yA, xB, yB) + triSquare(aPx, aPy, xB, yB, xC, yC) +
        triSquare(aPx, aPy, xC, yC, xA, yA);
    if ( abs(s - triSquare(xA,yA,xB,yB,xC,yC))<= 0.01){return true;}
    else{return false;}

}

QString Rectangle::getInformation()
{
    return QString::fromStdString(std::string("Прямоугольник\nКоординаты верхнего левого угла: (" + std::to_string(xLeft)
                                              + ";" + std::to_string(yTop) + ")\n" + "Ширина: " + std::to_string(width) +
                                              "\nВысота: " + std::to_string(height)));
}

QString Ellipse::getInformation(){
    return QString::fromStdString(std::string("Эллипс\nКоординаты центра: (" + std::to_string(xCenter)
                                              + ";" + std::to_string(yCenter) + ")\n" + "Ширина: " + std::to_string(width) +
                                              "\nВысота: " + std::to_string(height) + "\n"));
}

QString Triangle::getInformation(){
    return QString::fromStdString(std::string("Треугольник\nТочка А: (" + std::to_string(xA)
                                              + ";" + std::to_string(yA) + ")\nТочка B: ("
                                              + std::to_string(xB) + ";" + std::to_string(yB)
                                              + ")\nТочка C: (" + std::to_string(xC) + ";" + std::to_string(yC)
                                              + ")\nПлощадь: " + std::to_string(triSquare(xA,yA,xB,yB,xC,yC)) + "\n"));
}

void Rectangle::move(int deltaX, int deltaY){
    this->xLeft += deltaX;
    this->yTop += deltaY;

    rectangle = QRect(xLeft, yTop, width, height);
}

void Ellipse::move(int deltaX, int deltaY){
    this->xCenter += deltaX;
    this->xLeft += deltaX;
    this->yCenter += deltaY;
    this->yTop += deltaY;

    ellipse = QRect(xLeft, yTop, width, height);
}

void Triangle::move(int deltaX, int deltaY){

    this->points[0] = QPoint(points[0].x() + deltaX,points[0].y() + deltaY);
    this->points[1] = QPoint(points[1].x() + deltaX,points[1].y() + deltaY);
    this->points[2] = QPoint(points[2].x() + deltaX,points[2].y() + deltaY);

    this->xA = points[0].x();
    this->yA = points[0].y();
    this->xB = points[1].x();
    this->yB = points[1].y();
    this->xC = points[2].x();
    this->yC = points[2].y();

    QVector<QPoint> vec;
    for (QPoint i: points){
        vec.push_back(i);
    }

    polygon = QPolygon(vec);
}

void Rectangle::moveTo(int X, int Y){
    this->xLeft = X - width/2;
    this->yTop = Y - height/2;

    rectangle = QRect(xLeft, yTop, width, height);
}

void Ellipse::moveTo(int X, int Y){
    this->xCenter = X;
    this->yCenter = Y;
    this->xLeft = xCenter - width/2;
    this->yTop = yCenter - height/2;

    ellipse = QRect(xLeft, yTop, width, height);
}

void Triangle::moveTo(int X, int Y){
    int centerX = (xA + xB + xC)/3;
    int centerY = (yA + yB + yC)/3;
    int deltaXA = xA - centerX;
    int deltaYA = yA - centerY;
    int deltaXB = xB - centerX;
    int deltaYB = yB - centerY;
    int deltaXC = xC - centerX;
    int deltaYC = yC - centerY;

    this->points[0] = QPoint(X + deltaXA,Y + deltaYA);
    this->points[1] = QPoint(X + deltaXB,Y + deltaYB);
    this->points[2] = QPoint(X + deltaXC,Y + deltaYC);

    this->xA = points[0].x();
    this->yA = points[0].y();
    this->xB = points[1].x();
    this->yB = points[1].y();
    this->xC = points[2].x();
    this->yC = points[2].y();

    QVector<QPoint> vec;
    for (QPoint i: points){
        vec.push_back(i);
    }

    polygon = QPolygon(vec);
}
