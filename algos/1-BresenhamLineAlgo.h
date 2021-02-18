#if !defined(BRESENHAM_LINE)
#define BRESENHAM_LINE
#include <cmath>
#include <vector>
#include "../custom-headers/Point.h"

std::vector<Point<int>> BresenhamsLineDrawingAlgo(int x0, int x1, int y0, int y1)
{
    int x = x0, y = y0;
    int dX = abs(x1 - x0), dY = abs(y1 - y0);
    int dT = 2 * (dY - dX), dS = 2 * dY;
    std::vector<Point<int>> points;
    points.push_back(Point<int>(x, y));
    int incX = 1;
    if (x1 < x0)
        incX *= -1;
    int incY = 1;
    if (y1 < y0)
        incY *= -1;
    int dK = 2 * dY - dX;
    for (int i = 0; i < dX; i++)
    {
        x += incX;
        if (dK >= 0)
        {
            y += incY;
            dK += dT;
        }
        else
        {
            dK += dS;
        }
        points.push_back(Point<int>(x, y));
    }
    return points;
}
#endif // BRESENHAM_LINE
