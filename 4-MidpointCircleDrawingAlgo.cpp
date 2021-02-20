#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include "./custom-headers/Point.h"
#include "./openGL-comp/HelperDrawerMethod.h"
#include "./algos/4-MidPointCircleAlgo.h"

using namespace std;

int pntX1, pntY1, r;

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glColor3f(0.0, 0.0, 0.0);
}

void myDisplay(void)
{
	int offsetX = 250, offsetY = 250; // origin at (250,250)
	RGBColor color(0, 0, 0, 1);
	auto points = midPointCircleAlgo(r);
	drawPixels<int>(points, color, pntX1 + offsetX, pntY1 + offsetY, false);
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the coordinates of the center:\n\n"
		 << endl;

	cout << "X-coordinate  : ";
	cin >> pntX1;
	cout << "\nY-coordinate : ";
	cin >> pntY1;
	cout << "\nEnter radius : ";
	cin >> r;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("-- Midpoint Circle Drawing --");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}