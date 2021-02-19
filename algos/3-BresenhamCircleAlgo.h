#if !defined(BRESENHAM_CIRCLE)
#define BRESENHAM_CIRCLE
#include <vector>
#include "../custom-headers/Point.h"


void setOctetPoints(Point<int> p,std::vector<Point<int>> &points) {
	int x=p.x,y=p.y;
    points.push_back(Point<int>(x , y ));
	points.push_back(Point<int>(-x , y ));
	points.push_back(Point<int>(x , -y ));
	points.push_back(Point<int>(-x , -y ));
	points.push_back(Point<int>(y , x ));
	points.push_back(Point<int>(-y , x ));
	points.push_back(Point<int>(y , -x ));
	points.push_back(Point<int>(-y , -x ));
}

std::vector<Point<int>> bresenhamCircleAlgo(int r) {

	int d = 3 - 2*r;
	Point<int> point(0,r);
	std::vector<Point<int>> points;
    setOctetPoints(point,points);
	while (point.x <= point.y) {
		if(d<0){
			d=d+4*point.x+6;
		}
		else{
			d=d+ 4*(point.x-point.y)+10;
			point.y--;
		}
		point.x++;
		
        setOctetPoints(point,points);
	}
    return points;
}
#endif // BRESENHAM_CIRCLE
