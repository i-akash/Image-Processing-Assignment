#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "./custom-headers/Line.h"
#include "./custom-headers/Point.h"
#include "./custom-headers/Polygone.h"
#include "./algos/SutherlandHodgmanPolygonClippingAlgo.h"
#include "./openGL-comp/HelperDrawerMethod.h"

using namespace std;
vector<Point<double>> points;
int d=150; 
struct State
{
    Polygone<double> polygonTobeClipped;
    Polygone<double> clipperWindow;
    Polygone<double> showWindow;
};


void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}

State getInitState(){
    double xmin = 150, ymin = 150, xmax = 250, ymax = 250;
    double xwmin = xmin+d, ywmin = ymin+d, xwmax = xmax+d, ywmax = ymax+d;
    State state;
    state.polygonTobeClipped=Polygone<double>(points);
    
    state.clipperWindow.addPoint(Point<double>(xmin,ymin));
    state.clipperWindow.addPoint(Point<double>(xmin,ymax));
    state.clipperWindow.addPoint(Point<double>(xmax,ymax));
    state.clipperWindow.addPoint(Point<double>(xmax,ymin));

    state.showWindow.addPoint(Point<double>(xwmin, ywmin));
    state.showWindow.addPoint(Point<double>(xwmax, ywmin));
    state.showWindow.addPoint(Point<double>(xwmax, ywmax));
    state.showWindow.addPoint(Point<double>(xwmin, ywmax));
    
    return state;
}

void myDisplay()
{
    
    State state = getInitState();
    glClear(GL_COLOR_BUFFER_BIT);
    drawBluePolygon(state.clipperWindow.points);
    drawRedPolygon(state.polygonTobeClipped.points);
    
    //display clipped window
    drawRedPolygon(state.showWindow.points);
    if(state.polygonTobeClipped.points.size()>=3){
        state.polygonTobeClipped=suthHodgClip<double>(state.polygonTobeClipped, state.clipperWindow);
        for(int index =0;index < state.polygonTobeClipped.points.size();index++){
            state.polygonTobeClipped.addPointOffset(index,d,d);
        } 
        // drawRedPolygon(state.polygonTobeClipped.points);
        for(int index =0;index < state.polygonTobeClipped.points.size();index++){
            int nIndex=(index+1)%state.polygonTobeClipped.points.size();
            drawLine<double>(state.polygonTobeClipped.getConnectedLine(index,nIndex));   
        }
    }

    glFlush();
}

void key(unsigned char key_t, int x, int y)
{
    if (key_t == 'c')
    {
        points.clear();
        glutPostRedisplay();
    }
}

void myMouse(int button, int state, int x, int y)
{
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        points.push_back(Point<double>(x,y));
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
    glutKeyboardFunc(key);
    glutMainLoop();
    return 0;
}