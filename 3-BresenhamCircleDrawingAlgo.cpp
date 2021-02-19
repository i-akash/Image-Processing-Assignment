#include <windows.h>
#include <gl/glut.h>
#include <iostream>
#include <cmath>
#include "./custom-headers/Point.h"
#include "./openGL-comp/HelperDrawerMethod.h"
#include "./algos/3-BresenhamCircleAlgo.h"

using namespace std;

int cx1=0, cy1=0, r;

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glColor3f(0.0, 0.0, 0.0);
}

void myDisplay() {
	int offsetX=250,offsetY=250; // origin at (250,250)
    RGBColor color(0,0,0,1);
	auto points=bresenhamCircleAlgo(r);
	drawPixels<int>(points,color,cx1+offsetX,cy1+offsetY);
	glFlush();
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        cx1 = x, cy1 = y;
		glutPostRedisplay();
    }
}

int main(int argc, char **argv) {

	cout << "Enter the coordinates of the center:\n\n" << endl;

	cout << "X-coordinate   : "; cin >> cx1;
	cout << "\nY-coordinate : "; cin >> cy1;
	cout << "\nEnter radius : "; cin >> r;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Circle Drawing");
	myInit();
	glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
	glutMainLoop();

	return 0;
}