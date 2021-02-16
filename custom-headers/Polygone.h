#if !defined(POLYGONE)
#define POLYGONE

#include "./Point.h"
#include "./Line.h"
#include <vector>

template<typename T>
struct Polygone{
    std::vector<Point<T>> points;
    int iteratorIndex;
    Polygone(){
        iteratorIndex=0;
    }
    Polygone(std::vector<Point<T>> points){
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

#endif // POLYGONE
