#include <windows.h>
#include <gl/glut.h>
#include <iostream>
#include <cmath>
#include "./custom-headers/Point.h"

using namespace std;


int cx1=0, cy1=0, r;

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glColor3f(0.0, 0.0, 0.0);
}

void drawOctetPoints(Point<int> p) {
	int x=p.x,y=p.y;
	glBegin(GL_POINTS);
	glVertex2i(x + cx1, y + cy1);
	glVertex2i(-x + cx1, y + cy1);
	glVertex2i(x + cx1, -y + cy1);
	glVertex2i(-x + cx1, -y + cy1);
	glVertex2i(y + cx1, x + cy1);
	glVertex2i(-y + cx1, x + cy1);
	glVertex2i(y + cx1, -x + cy1);
	glVertex2i(-y + cx1, -x + cy1);
	glEnd();
}

void drawCircle(int r) {
	int d = 3 - 2*r;
	Point<int> p(0,r);
	drawOctetPoints(p);
	while (p.x <= p.y) {
		if(d<0){
			d=d+4*p.x+6;
		}
		else{
			d=d+ 4*(p.x-p.y)+10;
			p.y--;
		}
		p.x++;
		drawOctetPoints(p);
	}
}

void myDisplay() {
	drawCircle(r);
	glFlush();
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        cx1 = x, cy1 = y;
		glutPostRedisplay();
    }
}

int main(int argc, char **argv) {

	cout << "Enter Circle Center (x1, y1) and radius (r)" << endl;
	cin >> cx1 >> cy1 >> r;

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