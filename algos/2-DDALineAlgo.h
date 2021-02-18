#if !defined(DDA)
#define DDA
#include <cmath>
#include <vector>
#include "../custom-headers/Point.h"

std::vector<Point<int>> DDALineDrawingAlgo(Point<float> p1, Point<float> p2){
    float dy, dx, step, incX, incY;
    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    if (abs(dx) >= abs(dy))
    {
        step = abs(dx);
    }
    else
    {
        step = abs(dy);
    }

    incX = dx / step; // if abs(dx) >= abs(dy) then step = dx and incX = 1 and incY = dy/dx 
    incY = dy / step; // if abs(dx) <  abs(dy) then step = dy and incX = dx/dy and incY = 1  

    std::vector<Point<int>> points;
    Point<int> p(p1.x,p1.y);
    points.push_back(p);
    for (int k = 1; k <= step; k++)
    {
        p.x = p.x + incX;
        p.y = p.y + incY;
        points.push_back(p);
    }
    return points;
}

#endif // DDA
