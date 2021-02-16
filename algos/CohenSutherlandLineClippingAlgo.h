#if !defined(COHEN_SUTH)
#define COHEN_SUTH

#include "../custom-headers/Line.h"
#include "../custom-headers/Point.h"

const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
template<typename T>
int computeCode(Point<T> point,T xmin, T ymin,T xmax, T ymax)
{
    int code = 0;
    if (point.x < xmin)
        code |= LEFT;
    else if (point.x > xmax)
        code |= RIGHT;

    if (point.y < ymin)
        code |= BOTTOM;
    else if (point.y > ymax)
        code |= TOP;

    return code;
}

template<typename T>
bool cohenSutherland(Line<T> &pLine,T xmin, T ymin,T xmax, T ymax)
{
    int outcode0 = computeCode<T>(pLine.pStart, xmin,  ymin, xmax,  ymax);
    int outcode1 = computeCode<T>(pLine.pEnd, xmin,  ymin, xmax,  ymax);
    bool accept = false;

    while (true)
    {
        if (!(outcode0 | outcode1))
        { //Bitwise OR is 0, accept it since the points lie completely inside the clip window
            accept = true;
            break;
        }
        else if (outcode0 & outcode1) //Bitwise AND is not 0, reject it since the points lie completely outside the clip window
            break;
        else
        {
            //calculate line segment to clip from an outside point to an intersection with clip edge
            int outcodeOut = outcode0 ? outcode0 : outcode1;
            double x, y;
            double slope;
            slope = pLine.getSlope();

            if (outcodeOut & TOP)
            {
                x = pLine.getXgivenY(ymax);
                y = ymax;
            }
            else if (outcodeOut & BOTTOM)
            {
                x = pLine.getXgivenY(ymin);
                y = ymin;
            }
            else if (outcodeOut & RIGHT)
            {
                y = pLine.getYgivenX(xmax);
                x = xmax;
            }
            else
            {
                y = pLine.getYgivenX(xmin);
                x = xmin;
            }

            if (outcodeOut == outcode0)
            {

                pLine.setStartPoint(Point<T>(x,y));
                outcode0 = computeCode<T>(pLine.pStart, xmin,  ymin, xmax,  ymax);
            }
            else
            {
                pLine.setEndPoint(Point<T>(x,y));
                outcode1 = computeCode<T>(pLine.pEnd, xmin,  ymin, xmax,  ymax);
            }
        }
    }
    return accept;
}

#endif // COHEN_SUTH
