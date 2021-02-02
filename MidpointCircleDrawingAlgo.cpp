#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
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
int pntX1, pntY1, r;

void plot(Point<int> p)
{
	glBegin(GL_POINTS);
	glVertex2i(p.x+pntX1, p.y+pntY1);
	glEnd();
}


void myInit (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void drawOctetPoints(Point<int> p) {
	int x=p.x,y=p.y;
	plot(Point<int>(x, y));
	plot(Point<int>(-x, y));
	plot(Point<int>(x, -y));
	plot(Point<int>(-x, -y));
	plot(Point<int>(y, x));
	plot(Point<int>(-y, x));
	plot(Point<int>(y, -x));
	plot(Point<int>(-y, -x));
}

void midPointCircleAlgo()
{
	Point<int> p(0,r);
	float decision = 5/4 - r;
	plot(p);

	while (p.y > p.x)
	{
		if (decision < 0)
		{
			p.x++; 
			decision += 2*p.x+3;
		}
		else
		{
			p.y--;
			p.x++;
			decision += 2*(p.x-p.y)+5;
		}
		drawOctetPoints(p);
	}

}

void myDisplay(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(1.0);

	midPointCircleAlgo();

	glFlush ();
}

int main(int argc, char** argv)
{	
	cout << "Enter the coordinates of the center:\n\n" << endl;

	cout << "X-coordinate   : "; cin >> pntX1;
	cout << "\nY-coordinate : "; cin >> pntY1;
	cout << "\nEnter radius : "; cin >> r;


	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("Line Drawing Alogrithms");
	glutDisplayFunc(myDisplay);
	myInit ();
	glutMainLoop();
    return 0;
    
}