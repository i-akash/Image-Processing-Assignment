#if !defined(MIDPOINT_CIRCLE)
#define MIDPOINT_CIRCLE
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

std::vector<Point<int>> midPointCircleAlgo(int r)
{
	Point<int> point(0,r);
	float decision = 1 - r;
	std::vector<Point<int>> points;
    setOctetPoints(point,points);

	while (point.y > point.x)
	{
		if (decision < 0)
		{
			point.x++; 
			decision += 2*point.x+3;
		}
		else
		{
			point.y--;
			point.x++;
			decision += 2*(point.x-point.y)+5;
		}
		setOctetPoints(point,points);
	}
    return points;
}
#endif // MIDPOINT_CIRCLE
