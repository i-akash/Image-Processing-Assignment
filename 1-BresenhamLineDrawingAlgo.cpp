#include <windows.h>
#include <gl/glut.h>
#include <iostream>

using namespace std;


void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void draw_pixel(int x, int y, bool exchanged = false)
{
    if (exchanged)
    {
        swap(&x, &y);
    }
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


void BresenhamsLineDrawingAlgo(int x0, int x1, int y0, int y1, bool exchanged = false)
{
    int x = x0, y = y0;
    int dX = abs(x1 - x0), dY = abs(y1 - y0);
    int dT = 2 * (dY - dX), dS = 2 * dY;
    draw_pixel(x, y, exchanged);
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
        draw_pixel(x, y, exchanged);
    }
}

void draw_line(int x0, int x1, int y0, int y1)
{
    int dX = abs(x1 - x0), dY = abs(y1 - y0);
    if (dX > dY)
    {
        BresenhamsLineDrawingAlgo(x0, x1, y0, y1);
    }
    else
    {
        BresenhamsLineDrawingAlgo(y0, y1, x0, x1, true);
    }
}

int x1, x2, y1, y2;    
void myDisplay()
{
    
    draw_line(x1, x2, y1, y2);
    glFlush();
}

int main(int argc, char **argv)
{
    cout<<"Enter (x1, y1, x2, y2)\n";
    cin>>x1>>y1>>x2>> y2;
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