#include <windows.h>
#include <gl/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

template<typename T>
struct Point
{
    T x,y;
    Point(){}

    Point(T x,T y){
        this->x=x;
        this->y=y;
    }
};
Point<float> p1,p2;


void drawPixel(Point<float> p)
{
    glBegin(GL_POINTS);
    glVertex2i(p.x, p.y);
    glEnd();
}

void DDALineDrawingAlgo(Point<float> p1, Point<float> p2){
    float dy, dx, step, incX, incY;
    dx = p2.x - p1.x;
    dy = p2.y - p1.y;
    cout<<abs(dx)<<" "<<abs(dy)<<endl;
    if (abs(dx) >= abs(dy))
    {
        step = abs(dx);
    }
    else
    {
        step = abs(dy);
    }

    incX = dx / step; // if abs(dx) >= abs(dy) then incX=1
    incY = dy / step; // if abs(dx) < abs(dy) then incY=1

    Point<float> p(p1.x,p1.y);
    drawPixel(p);
    cout<<incX<<incY;
    for (int k = 1; k <= step; k++)
    {
        p.x = p.x + incX;
        p.y = p.y + incY;
        drawPixel(p);
    }
}



void display()
{
    DDALineDrawingAlgo(p1,p2);
    glFlush();
}

void init(void)
{
    glClearColor(0.7, 0.7, 0.7, 0.7);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char **argv)
{
    cout<<"Enter the value of x1, y1, x2 , y2 : \n";
    cin>>p1.x>>p1.y>>p2.x>>p2.y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Algo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}