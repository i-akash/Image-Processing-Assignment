#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "./custom-headers/Line.h"
#include "./custom-headers/Point.h"
#include "./custom-headers/Polygone.h"

using namespace std;

double xmin = 150, ymin = 150, xmax = 250, ymax = 250;
double xwmin = 300, ywmin = 300, xwmax = 400, ywmax = 400;
Polygone<double> polygon;
bool doClip=false;

template<typename T>
void clip(Polygone<T> &polygone,Line<T> clipperLine) 
{ 
    vector<Point<T>> clippedPolygon; 
    for (int i = 0; i < polygone.points.size(); i++) 
    { 
        int k = (i+1) % polygone.points.size();
        Line<T> currentLine = polygone.getConnectedLine(i,k);
  
        // Calculating position of point 
        // w.r.t. clipper line 
        int i_pos = clipperLine.getPositionOfPoint(currentLine.pStart); 
        int k_pos = clipperLine.getPositionOfPoint(currentLine.pEnd); 
  
        // Case 1 : When both points are inside
        if (i_pos < 0  && k_pos < 0) 
        { 
            //Only second point is added 
            clippedPolygon.push_back(currentLine.pEnd);
        } 
        // Case 2: When only first point is outside 
        else if (i_pos >= 0  && k_pos < 0) 
        { 
            // Point of intersection with edge 
            // and the second point is added 
            Point<T> p=clipperLine.getIntersectOfLines(currentLine);
            clippedPolygon.push_back(p);
            clippedPolygon.push_back(currentLine.pEnd);
        } 
        // Case 3: When only second point is outside 
        else if (i_pos < 0  && k_pos >= 0) 
        { 
            //Only point of intersection with edge is added 
            Point<T> p=clipperLine.getIntersectOfLines(currentLine);
            clippedPolygon.push_back(p); 
        } 
        // Case 4: When both points are outside 
        else
        { 
            //No points are added 
        } 
    }
    polygone.points=clippedPolygon; 
} 
  

template<typename T>
void suthHodgClip(Polygone<T> &polygone, Polygone<T> window) 
{ 
    //i and k are two consecutive indexes 
    for (int i=0; i<window.points.size(); i++) 
    { 
        int k = (i+1) % window.points.size(); 
        // We pass the current array of vertices, it's size 
        // and the end points of the selected clipper line
        Line<T> clipperLine= window.getConnectedLine(i,k); 
        clip<double>(polygone, clipperLine);
    } 
} 

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}

void myDisplay()
{
    cout<<"called\n";

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    //display clipped window
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xwmin, ywmin);
    glVertex2f(xwmax, ywmin);
    glVertex2f(xwmax, ywmax);
    glVertex2f(xwmin, ywmax);
    glEnd();

    Polygone<double> window;
    window.addPoint(Point<double>(xmin,ymin));
    window.addPoint(Point<double>(xmin,ymax));
    window.addPoint(Point<double>(xmax,ymax));
    window.addPoint(Point<double>(xmax,ymin));

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    while (polygon.hasNext())
    {
        auto point = polygon.getNext();
        glVertex2f(point.x,point.y);
    }
    polygon.resetIterator();
    glEnd();

    // Defining clipper polygone vertices in clockwise order 
    // 1st Example with square clipper 
    cout<<doClip<<"\n";
    if(polygon.points.size()>=3 && doClip){
        suthHodgClip<double>(polygon, window); 
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);
        while (polygon.hasNext())
        {
            auto point = polygon.getNext();
            double vx1 = xwmin + (point.x - xmin) ;
            double vy1 = ywmin + (point.y - ymin) ;
            glVertex2f(vx1,vy1);
        }
        polygon.resetIterator();
        glEnd();
        doClip=false;
    }

    glFlush();
}

void key(unsigned char key_t, int x, int y)
{
    cout<<key_t<<"\n";
    if (key_t == 'd')
    {
        doClip=true;
        glutPostRedisplay();
    }
    if (key_t == 'c')
    {
        polygon=Polygone<double>();
        glutPostRedisplay();
    }
}

void myMouse(int button, int state, int x, int y)
{
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        polygon.addPoint(Point<double>(x,y));
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen-Sutherland");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
}