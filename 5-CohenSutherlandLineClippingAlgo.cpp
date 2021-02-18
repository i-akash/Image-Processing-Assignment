#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "./custom-headers/Point.h"
#include "./custom-headers/Line.h"
#include "./algos/5-CohenSutherlandLineClippingAlgo.h"
#include "./openGL-comp/HelperDrawerMethod.h"
#include "./custom-headers/Polygone.h"

using namespace std;

struct State
{
    Line<double> lineTobeClipped;
    Polygone<double> clipperWindow;
    Polygone<double> showWindow;
    double xmin, ymin, xmax , ymax ;
    int d=150;
    State(){
        
        xmin = 150, ymin = 150, xmax = 250, ymax = 250;
        double xwmin = xmin+d, ywmin = ymin+d, xwmax = xmax+d, ywmax = ymax+d;

        lineTobeClipped.pStart = Point<double>(0,0);

        clipperWindow.addPoint(Point<double>(xmin,ymin));
        clipperWindow.addPoint(Point<double>(xmin,ymax));
        clipperWindow.addPoint(Point<double>(xmax,ymax));
        clipperWindow.addPoint(Point<double>(xmax,ymin));

        showWindow.addPoint(Point<double>(xwmin, ywmin));
        showWindow.addPoint(Point<double>(xwmax, ywmin));
        showWindow.addPoint(Point<double>(xwmax, ywmax));
        showWindow.addPoint(Point<double>(xwmin, ywmax));
    }
} state;
Line<double> userLine;

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}

void myDisplay()
{
    state.lineTobeClipped=userLine;
    //display line
    drawLine<double>(state.lineTobeClipped);
    //display clipping window
    drawBluePolygon(state.clipperWindow.points);
    //display clipped window
    drawRedPolygon(state.showWindow.points);

    bool accept = cohenSutherland<double>(state.lineTobeClipped, state.xmin,  state.ymin, state.xmax,  state.ymax);
    if(accept){
        state.lineTobeClipped.pStart.x+=state.d;
        state.lineTobeClipped.pStart.y+=state.d;
        state.lineTobeClipped.pEnd.x+=state.d;
        state.lineTobeClipped.pEnd.y+=state.d;  
        drawLine<double>(state.lineTobeClipped);
    }
    glFlush();
}

void myMouse(int button, int state, int x, int y)
{
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        userLine.pStart=userLine.pEnd;
        userLine.pEnd.x=x;
        userLine.pEnd.y=y;
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
    glutMainLoop();
    return 0;
}