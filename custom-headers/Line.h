#if !defined(LINE)
#define LINE

#include "./Point.h"
template<typename T>
struct Line
{
    Point<T> pStart;
    Point<T> pEnd;
    Line(){}
    Line(T x1,T y1,T x2,T y2){
        this->pStart=Point<T>(x1,y1);
        this->pEnd=Point<T>(x2,y2);
    }
    Line(Point<T> p1,Point<T> p2){
        this->pStart=p1;
        this->pEnd=p2;
    }

    void setStartPoint(Point<T> p){
        this->pStart=p;
    }

    void setStartPoint(T x,T y){
        this->pStart.x=x;
        this->pStart.y=y;
    }

    void setEndPoint(Point<T> p){
        this->pEnd=p;
    }

    void setEndPoint(T x,T y){
        this->pEnd.x=x;
        this->pEnd.y=y;
    }

    double getSlope(){
        return (pEnd.y - pStart.y) / (pEnd.x - pStart.x);
    }

    T getStartX(){
        return pStart.x;
    }
    T getEndX(){
        return pEnd.x;
    }

    T getStartY(){
        return pStart.y;
    }
    T getEndY(){
        return pEnd.y;
    }

    T getXgivenY(T pY){
        // x1 = x + (1/slope) * (y1-y)
        return pStart.x + (1 / getSlope()) * (pY - pStart.y);
    }

    T getYgivenX(T pX){
        // y1 = y + slope (x1-x)
        return pStart.y + getSlope() * (pX - pStart.x);
    }

    Point<T> getIntersectOfLines(Line<T> pLine){
        T num = (pStart.x*pEnd.y - pStart.y*pEnd.x) * (pLine.pStart.x-pLine.pEnd.x) - (pStart.x-pEnd.x) * (pLine.pStart.x*pLine.pEnd.y - pLine.pStart.y*pLine.pEnd.x); 
        T den = (pStart.x-pEnd.x) * (pLine.pStart.y-pLine.pEnd.y) - (pStart.y-pEnd.y) * (pLine.pStart.x-pLine.pEnd.x);
        T x =num/den;

        num = (pStart.x*pEnd.y - pStart.y*pEnd.x) * (pLine.pStart.y-pLine.pEnd.y) - (pStart.y-pEnd.y) * (pLine.pStart.x*pLine.pEnd.y - pLine.pStart.y*pLine.pEnd.x); 
        den = (pStart.x-pEnd.x) * (pLine.pStart.y-pLine.pEnd.y) - (pStart.y-pEnd.y) * (pLine.pStart.x-pLine.pEnd.x);  
        T y= num/den;

        return Point<T>(x,y); 
    }

    int getPositionOfPoint(Point<T> point){
        return (pEnd.x-pStart.x) * (point.y-pStart.y) - (pEnd.y-pStart.y) * (point.x-pStart.x);
    }
};
#endif // LINE
