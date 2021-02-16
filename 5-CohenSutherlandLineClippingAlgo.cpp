#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "./custom-headers/Point.h"
#include "./custom-headers/Line.h"

using namespace std;

Line<double> line(Point<double>(0,0),Point<double>(100,100));
double xmin = 100, ymin = 100, xmax = 200, ymax = 200;
double xwmin = 300, ywmin = 300, xwmax = 400, ywmax = 400;

const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int cnt = 0;

template<typename T>
int computeCode(Point<T> point)
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
void cohenSutherland(Line<T> pLine)
{
    int outcode0 = computeCode<T>(pLine.pStart);
    int outcode1 = computeCode<T>(pLine.pEnd);
    cout<<pLine.pStart.x<<" "<<pLine.pStart.y<<"\n";
    cout<<pLine.pEnd.x<<" "<<pLine.pEnd.y<<"\n";
    cout<<outcode0<<"\n";
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
                outcode0 = computeCode<T>(pLine.pStart);
            }
            else
            {
                pLine.setEndPoint(Point<T>(x,y));
                outcode1 = computeCode<T>(pLine.pEnd);
            }
        }
    }

    if (accept)
    {
        double sx = (xwmax - xwmin) / (xmax - xmin);
        double sy = (ywmax - ywmin) / (ymax - ymin);
        double vx1 = xwmin + (pLine.getStartX() - xmin) * sx;
        double vy1 = ywmin + (pLine.getStartY() - ymin) * sy;
        double vx2 = xwmin + (pLine.getEndX() - xmin) * sx;
        double vy2 = ywmin + (pLine.getEndY() - ymin) * sy;

        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(vx1, vy1);
        glVertex2f(vx2, vy2);
        glEnd();
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
    //display line
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(line.getStartX(), line.getStartY());
    glVertex2f(line.getEndX(), line.getEndY());
    glEnd();

    //display clipping window
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

    cohenSutherland<double>(line);
    glFlush();
}

void myMouse(int button, int state, int x, int y)
{
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cnt++;
        if (cnt == 1)
            line.setStartPoint(x,y);
        else if (cnt == 2)
        {
            cnt = 0;
            line.setEndPoint(x,y);
            glutPostRedisplay();
        }
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