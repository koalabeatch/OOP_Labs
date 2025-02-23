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

Triangle::Triangle(QPoint pointA, QPoint pointB, QPoint pointC)
{
    this->pointA = pointA;
    this->pointB = pointB;
    this->pointC = pointC;

    this->xA = pointA.x();
    this->yA = pointA.y();
    this->xB = pointB.x();
    this->yB = pointB.y();
    this->xC = pointC.x();
    this->yC = pointC.y();

    QVector<QPoint> vec;
    vec.append(pointA);
    vec.append(pointB);
    vec.append(pointC);
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

    this->pointA = QPoint(xA,yA);
    this->pointB = QPoint(xB,yB);
    this->pointC = QPoint(xC,yC);

    QVector<QPoint> vec;
    vec.append(pointA);
    vec.append(pointB);
    vec.append(pointC);

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
