#include <windows.h>
#include <gl/glut.h>
#include <iostream>
#include "./custom-headers/Point.h"
#include "./openGL-comp/HelperDrawerMethod.h"
#include "./algos/2-DDALineAlgo.h"

using namespace std;
Point<float> p1, p2;

void display()
{
    int offsetX = 250, offsetY = 250; // origin at (250,250)
    RGBColor color(0, 0, 0, 1);
    drawPixels(DDALineDrawingAlgo(p1, p2), color, offsetX, offsetY);
    glFlush();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}

int main(int argc, char **argv)
{
    cout << "Enter the value of x1, y1, x2 , y2 : \n";
    cin >> p1.x >> p1.y >> p2.x >> p2.y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("- DDA Line Algo -");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}