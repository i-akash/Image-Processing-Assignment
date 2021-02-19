#if !defined(HELPER_DRAWER)
#define HELPER_DRAWER
#include <windows.h>
#include <gl/glut.h>
#include "../custom-headers/Color.h"
#include "../custom-headers/Point.h"
#include "../custom-headers/Line.h"
#include<vector>

template<typename T>
void drawPixel(Point<T> p,RGBColor color=RGBColor(0,0,0),T offsetX=0, T offsetY=0,bool exchanged=false)
{
    glColor4f(color.red,color.green,color.blue,color.alpha);
    if (exchanged)
    {
        p.swap();
    }
    glBegin(GL_POINTS);
    glVertex2i(p.x+offsetX, p.y+offsetY);
    glEnd();
}

template<typename T>
void drawPixels(std :: vector<Point<T>> points, RGBColor color=RGBColor(0,0,0),T offsetX=0, T offsetY=0,bool exchanged=false)
{   
    for(Point<T> point : points){
        drawPixel<T>(point,color,offsetX,offsetY,exchanged);
    }
}

template<typename T>
void drawIPolygon(std::vector<Point<T>> points,RGBColor color=RGBColor(0,0,0),T offsetX=0, T offsetY=0){
    glColor4f(color.red,color.green,color.blue,color.alpha);
    glBegin(GL_LINE_LOOP);
    for(Point<T> point : points ){
        glVertex2f(point.x+offsetX,point.y+offsetY);
    }
    glEnd();
}

template<typename T>
void drawLine(Line<T> line,RGBColor color=RGBColor(0,0,0),T offsetX=0, T offsetY=0){
    glColor4f(color.red,color.green,color.blue,color.alpha);
    glBegin(GL_LINES);
    glVertex2f(line.getStartX()+offsetX, line.getStartY()+offsetY);
    glVertex2f(line.getEndX()+offsetX, line.getEndY()+offsetY);
    glEnd();
}
#endif // HELPER_DRAWER
