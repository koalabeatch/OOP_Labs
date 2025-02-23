#ifndef Point_H
#define Point_H

template<typename T1, typename T2>
class Point{
public:
    Point(T1 x, T2 y){
        this->x = x;
        this->y = y;
    }
    Point(T1 x){
        this->x = x;
        this->y = x;
    }
    Point Sum(Point A, Point B){
        Point resPoint(A.x + B.x, A.y + B.y);
        return resPoint;
    }
    Point Divide(Point D, int divider){
        Point resPoint(D.x/divider, D.y/divider);
        return resPoint;
    }
    T1 getX(){
        return x;
    }
    T2 getY(){
        return y;
    }
    Point operator+(const Point rhs)
    {
        return Sum(Point(this->getX(),this->getY()),rhs);
    }
    Point operator/(const int divider)
    {
        return Divide(Point(this->getX(),this->getY()),divider);
    }
    Point& operator=(const int& num)
    {
        Point<double,double> resPoint(num,num);
        return resPoint;
    }
    Point& operator+=(Point& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

private:
    T1 x;
    T2 y;
};

#endif // Point_H
