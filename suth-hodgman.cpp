#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct Point
{
    T x,y;
    Point(){
        x=0;
        y=0;
    }

    Point(T x,T y){
        this->x=x;
        this->y=y;
    }
};

template<typename T>
struct Line
{
    Point<T> pStart;
    Point<T> pEnd;
    Line(){}
    Line(T x1,T y1,T x2,T y2){
        this->pStart=Point<T>(x1,y1);
        this->pEnd=Point<T>(x2,y2);
    }
    Line(Point<T> p1,Point<T> p2){
        this->pStart=p1;
        this->pEnd=p2;
    }

    void setStartPoint(Point<T> p){
        this->pStart=p;
    }

    void setStartPoint(T x,T y){
        this->pStart.x=x;
        this->pStart.y=y;
    }

    void setEndPoint(Point<T> p){
        this->pEnd=p;
    }

    void setEndPoint(T x,T y){
        this->pEnd.x=x;
        this->pEnd.y=y;
    }

    double getSlope(){
        return (pEnd.y - pStart.y) / (pEnd.x - pStart.x);
    }

    T getStartX(){
        return pStart.x;
    }
    T getEndX(){
        return pEnd.x;
    }

    T getStartY(){
        return pStart.y;
    }
    T getEndY(){
        return pEnd.y;
    }

    T getXgivenY(T pY){
        // x1 = x + (1/slope) * (y1-y)
        return pStart.x + (1 / getSlope()) * (pY - pStart.y);
    }

    T getYgivenX(T pX){
        // y1 = y + slope (x1-x)
        return pStart.y + getSlope() * (pX - pStart.x);
    }

    Point<T> getIntersectOfLines(Line<T> pLine){
        T num = (pStart.x*pEnd.y - pStart.y*pEnd.x) * (pLine.pStart.x-pLine.pEnd.x) - (pStart.x-pEnd.x) * (pLine.pStart.x*pLine.pEnd.y - pLine.pStart.y*pLine.pEnd.x); 
        T den = (pStart.x-pEnd.x) * (pLine.pStart.y-pLine.pEnd.y) - (pStart.y-pEnd.y) * (pLine.pStart.x-pLine.pEnd.x);
        T x =num/den;

        num = (pStart.x*pEnd.y - pStart.y*pEnd.x) * (pLine.pStart.y-pLine.pEnd.y) - (pStart.y-pEnd.y) * (pLine.pStart.x*pLine.pEnd.y - pLine.pStart.y*pLine.pEnd.x); 
        den = (pStart.x-pEnd.x) * (pLine.pStart.y-pLine.pEnd.y) - (pStart.y-pEnd.y) * (pLine.pStart.x-pLine.pEnd.x);  
        T y= num/den;

        return Point<T>(x,y); 
    }

    int getPositionOfPoint(Point<T> point){
        return (pEnd.x-pStart.x) * (point.y-pStart.y) - (pEnd.y-pStart.y) * (point.x-pStart.x);
    }
};


template<typename T>
struct Polygone{
    vector<Point<T>> points;
    int iteratorIndex;
    Polygone(){
        iteratorIndex=0;
    }
    Polygone(vector<Point<T>> points){
        iteratorIndex=0;
        this->points=points;
    }

    void addPoint(Point<T> point){
        points.push_back(point);
    }

    void resetIterator(){
        iteratorIndex=0;
    }

    bool hasNext(){
        return iteratorIndex<points.size();   
    }

    Point<T> getNext(){
        if(!hasNext())
            return Point<T>();
        return points[iteratorIndex++];
    }   

     Point<T> getPoint(int index){
        if(index>=points.size())
            return Point<T>();
        return points[index++];
    }

    Line<T> getConnectedLine(int i, int j){
        return Line<T>(getPoint(i),getPoint(j));
    }    
};

double xmin = 150, ymin = 150, xmax = 250, ymax = 250;
double xwmin = 300, ywmin = 300, xwmax = 400, ywmax = 400;
Polygone<double> polygon;
bool doClip=false;

// This functions clips all the edges w.r.t one clip 
// edge of clipping area 
template<typename T>
void clip(Polygone<T> &polygone,Line<T> clipperLine) 
{ 
    vector<Point<T>> clippedPolygon; 
    // (ix,iy),(kx,ky) are the co-ordinate values of 
    // the points 
    for (int i = 0; i < polygone.points.size(); i++) 
    { 
        // i and k form a line in polygone 
        int k = (i+1) % polygone.points.size();
        Line<T> currentLine = polygone.getConnectedLine(i,k);
  
        // Calculating position of first point 
        // w.r.t. clipper line 
        int i_pos = clipperLine.getPositionOfPoint(currentLine.pStart); 
  
        // Calculating position of second point 
        // w.r.t. clipper line 
        int k_pos = clipperLine.getPositionOfPoint(currentLine.pEnd); 
  
        // Case 1 : When both points are inside
        if (i_pos < 0  && k_pos < 0) 
        { 
            //Only second point is added 
            clippedPolygon.push_back(currentLine.pEnd);
        } 
  
        // Case 2: When only first point is outside 
        else if (i_pos >= 0  && k_pos < 0) 
        { 
            // Point of intersection with edge 
            // and the second point is added 
            Point<T> p=clipperLine.getIntersectOfLines(currentLine);
            clippedPolygon.push_back(p);
            clippedPolygon.push_back(currentLine.pEnd);
        } 

  
        // Case 3: When only second point is outside 
        else if (i_pos < 0  && k_pos >= 0) 
        { 
            //Only point of intersection with edge is added 
            Point<T> p=clipperLine.getIntersectOfLines(currentLine);
            clippedPolygon.push_back(p); 
        } 
  
        // Case 4: When both points are outside 
        else
        { 
            //No points are added 
        } 
    }
    polygone.points=clippedPolygon; 
} 
  
// Implements Sutherland–Hodgman algorithm 
template<typename T>
void suthHodgClip(Polygone<T> &polygone, Polygone<T> window) 
{ 
    //i and k are two consecutive indexes 
    for (int i=0; i<window.points.size(); i++) 
    { 
        int k = (i+1) % window.points.size(); 
  
        // We pass the current array of vertices, it's size 
        // and the end points of the selected clipper line
        Line<T> clipperLine= window.getConnectedLine(i,k); 
        clip<double>(polygone, clipperLine);
    } 
} 

void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}

void myDisplay()
{
    cout<<"called\n";

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    //display clipped window
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xwmin, ywmin);
    glVertex2f(xwmax, ywmin);
    glVertex2f(xwmax, ywmax);
    glVertex2f(xwmin, ywmax);
    glEnd();

    Polygone<double> window;
    window.addPoint(Point<double>(xmin,ymin));
    window.addPoint(Point<double>(xmin,ymax));
    window.addPoint(Point<double>(xmax,ymax));
    window.addPoint(Point<double>(xmax,ymin));

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    while (polygon.hasNext())
    {
        auto point = polygon.getNext();
        glVertex2f(point.x,point.y);
    }
    polygon.resetIterator();
    glEnd();

    // Defining clipper polygone vertices in clockwise order 
    // 1st Example with square clipper 
    cout<<doClip<<"\n";
    if(polygon.points.size()>=3 && doClip){
        suthHodgClip<double>(polygon, window); 
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);
        while (polygon.hasNext())
        {
            auto point = polygon.getNext();
            double vx1 = xwmin + (point.x - xmin) ;
            double vy1 = ywmin + (point.y - ymin) ;
            glVertex2f(vx1,vy1);
        }
        polygon.resetIterator();
        glEnd();
        doClip=false;
    }

    glFlush();
}

void key(unsigned char key_t, int x, int y)
{
    cout<<key_t<<"\n";
    if (key_t == 'd')
    {
        doClip=true;
        glutPostRedisplay();
    }
    if (key_t == 'c')
    {
        polygon=Polygone<double>();
        glutPostRedisplay();
    }
}

void myMouse(int button, int state, int x, int y)
{
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        polygon.addPoint(Point<double>(x,y));
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