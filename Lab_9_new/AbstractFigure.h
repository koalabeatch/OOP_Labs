#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QPainter>

class AbstractFigure
{
public:
    void virtual drawFigure(QPainter& p) = 0;
};


#endif // ABSTRACTFIGURE_H
