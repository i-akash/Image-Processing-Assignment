#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "./custom-headers/Line.h"
#include "./custom-headers/Point.h"
#include "./custom-headers/Polygone.h"
#include "./algos/6-SutherlandHodgmanPolygonClippingAlgo.h"
#include "./openGL-comp/HelperDrawerMethod.h"

using namespace std;
vector<Point<double>> points;
struct State
{
    Polygone<double> polygonTobeClipped;
    Polygone<double> clipperWindow;
    Polygone<double> showWindow;
    double translateXY=150;
    State(){
        double xmin = 150, ymin = 150, xmax = 250, ymax = 250;
        double xwmin = xmin+translateXY, ywmin = ymin+translateXY, xwmax = xmax+translateXY, ywmax = ymax+translateXY;
        polygonTobeClipped=Polygone<double>(points);
        
        clipperWindow.addPoint(Point<double>(xmin,ymin));
        clipperWindow.addPoint(Point<double>(xmin,ymax));
        clipperWindow.addPoint(Point<double>(xmax,ymax));
        clipperWindow.addPoint(Point<double>(xmax,ymin));

        showWindow.addPoint(Point<double>(xwmin, ywmin));
        showWindow.addPoint(Point<double>(xwmax, ywmin));
        showWindow.addPoint(Point<double>(xwmax, ywmax));
        showWindow.addPoint(Point<double>(xwmin, ywmax));
    }
};


void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}

void myDisplay()
{
    
    State state;
    glClear(GL_COLOR_BUFFER_BIT);
    drawIPolygon(state.clipperWindow.points,RGBColor(0,0,1,1));
    drawIPolygon(state.polygonTobeClipped.points,RGBColor(0,0,0,1));
    
    //display clipped window
    drawIPolygon(state.showWindow.points,RGBColor(1,0,0,1));
    if(state.polygonTobeClipped.points.size()>=3){
        state.polygonTobeClipped=suthHodgClip<double>(state.polygonTobeClipped, state.clipperWindow);
        for(int index =0;index < state.polygonTobeClipped.points.size();index++){
            int nIndex=(index+1)%state.polygonTobeClipped.points.size();
            drawLine(state.polygonTobeClipped.getConnectedLine(index,nIndex),RGBColor(0,0,0,1),state.translateXY,state.translateXY);   
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