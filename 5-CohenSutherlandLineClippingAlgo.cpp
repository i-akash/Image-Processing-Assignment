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
    double xmin, ymin, xmax, ymax;
    double translateXY = 150;
    State()
    {

        xmin = 150, ymin = 150, xmax = 250, ymax = 250;
        double xwmin = xmin + translateXY, ywmin = ymin + translateXY, xwmax = xmax + translateXY, ywmax = ymax + translateXY;

        lineTobeClipped.pStart = Point<double>(0, 0);

        clipperWindow.addPoint(Point<double>(xmin, ymin));
        clipperWindow.addPoint(Point<double>(xmin, ymax));
        clipperWindow.addPoint(Point<double>(xmax, ymax));
        clipperWindow.addPoint(Point<double>(xmax, ymin));

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
    state.lineTobeClipped = userLine;
    //display clipping window
    drawIPolygon(state.clipperWindow.points, RGBColor(0, 0, 1, 1));
    //display line
    drawLine(state.lineTobeClipped, RGBColor(0, 0, 0, 1));

    //display clipped window
    drawIPolygon(state.showWindow.points, RGBColor(1, 0, 0, 1));

    bool accept = cohenSutherland<double>(state.lineTobeClipped, state.xmin, state.ymin, state.xmax, state.ymax);
    if (accept)
    {
        drawLine(state.lineTobeClipped, RGBColor(0, 0, 0, 1), state.translateXY, state.translateXY);
    }
    glFlush();
}

void myMouse(int button, int state, int x, int y)
{
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        userLine.pStart = userLine.pEnd;
        userLine.pEnd.x = x;
        userLine.pEnd.y = y;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("- Cohen-Sutherland -");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}