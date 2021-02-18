#include <windows.h>
#include <gl/glut.h>
#include <iostream>
#include "./openGL-comp/HelperDrawerMethod.h"
#include "./algos/1-BresenhamLineAlgo.h"

using namespace std;


void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}



void draw_line(int x0, int x1, int y0, int y1)
{
    int dX = abs(x1 - x0), dY = abs(y1 - y0);
    if (dX > dY)
    {
        drawPixels(BresenhamsLineDrawingAlgo(y0, y1, x0, x1));
    }
    else
    {
        drawPixels(BresenhamsLineDrawingAlgo(y0, y1, x0, x1),true);
    }
}

int x1, x2, uy1, y2;    
void myDisplay()
{
    draw_line(x1, x2, uy1, y2);
    glFlush();
}



int main(int argc, char **argv)
{
    cout<<"Enter (x1, uy1, x2, y2)\n";
    cin>>x1>>uy1>>x2>> y2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}