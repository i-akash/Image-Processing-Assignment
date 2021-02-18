#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include "./custom-headers/Point.h"
#include "./openGL-comp/HelperDrawerMethod.h"

using namespace std;

int pntX1, pntY1, r;

void myInit (void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glColor3f(0.0, 0.0, 0.0);
}

void drawOctetPoints(Point<int> p) {
	int x=p.x,y=p.y;
	drawPixel<int>(Point<int>(x+pntX1, y+pntY1));
	drawPixel<int>(Point<int>(-x+pntX1, y+pntY1));
	drawPixel<int>(Point<int>(x+pntX1, -y+pntY1));
	drawPixel<int>(Point<int>(-x+pntX1, -y+pntY1));
	drawPixel<int>(Point<int>(y+pntY1, x+pntX1));
	drawPixel<int>(Point<int>(-y+pntY1, x+pntX1));
	drawPixel<int>(Point<int>(y+pntY1, -x+pntX1));
	drawPixel<int>(Point<int>(-y+pntY1, -x+pntX1));
}

void midPointCircleAlgo()
{
	Point<int> p(0,r);
	float decision = 1 - r;
	drawPixel<int>(p);

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
	midPointCircleAlgo();
	glFlush ();
}

int main(int argc, char** argv)
{	
	cout << "Enter the coordinates of the center:\n\n" << endl;

	cout << "X-coordinate  : "; cin >> pntX1;
	cout << "\nY-coordinate : "; cin >> pntY1;
	cout << "\nEnter radius : "; cin >> r;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow ("-- Midpoint Circle Drawing --");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
    return 0;
    
}