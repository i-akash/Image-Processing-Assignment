#if !defined(HELPER_DRAWER)
#define HELPER_DRAWER
#include <windows.h>
#include <gl/glut.h>
#include "../custom-headers/Point.h"
#include<vector>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void drawPixel(int x, int y, bool exchanged = false)
{
    if (exchanged)
    {
        swap(&x, &y);
    }
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawPixel(Point<float> p)
{
    glBegin(GL_POINTS);
    glVertex2i(p.x, p.y);
    glEnd();
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
