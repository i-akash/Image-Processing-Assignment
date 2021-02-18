#if !defined(HELPER_DRAWER)
#define HELPER_DRAWER
#include <windows.h>
#include <gl/glut.h>
#include "../custom-headers/Point.h"
#include "../custom-headers/Line.h"
#include<vector>

int offset=250;

template<typename T>
void drawPixel(Point<T> p, bool exchanged=false)
{
    glColor3f(0.0, 0.0, 1.0);
    if (exchanged)
    {
        p.swap();
    }
    glBegin(GL_POINTS);
    glVertex2i(p.x+offset, p.y+offset);
    glEnd();
}

template<typename T>
void drawPixels(std :: vector<Point<T>> points, bool exchanged=false)
{   
    for(Point<T> point : points){
        drawPixel<T>(point,exchanged);
    }
}

void drawBluePolygon(std::vector<Point<double>> points){
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for(Point<double> point : points ){
        glVertex2f(point.x,point.y);
    }
    glEnd();
}

void drawRedPolygon(std::vector<Point<double>> points){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for(Point<double> point : points ){
        glVertex2f(point.x,point.y);
    }
    glEnd();
}

template<typename T>
void drawLine(Line<T> line){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(line.getStartX(), line.getStartY());
    glVertex2f(line.getEndX(), line.getEndY());
    glEnd();
}
#endif // HELPER_DRAWER
