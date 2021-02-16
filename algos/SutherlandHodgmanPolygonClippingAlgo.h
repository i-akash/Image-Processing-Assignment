#if !defined(SUTH_HODG)
#define SUTH_HODG
#include "../custom-headers/Line.h"
#include "../custom-headers/Point.h"
#include "../custom-headers/Polygone.h"
#include <vector>

template<typename T>
Polygone<T> clip(Polygone<T> polygone,Line<T> clipperLine) 
{ 
    std :: vector<Point<T>> clippedPolygon; 
    for (int i = 0; i < polygone.points.size(); i++) 
    { 
        int k = (i+1) % polygone.points.size();
        Line<T> currentLine = polygone.getConnectedLine(i,k);
  
        // Calculating position of point acc clipper line 
        int i_pos = clipperLine.getPositionOfPoint(currentLine.pStart); 
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
            // Point of intersection with edge and the second point is added 
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
    return  polygone;
} 
  

template<typename T>
Polygone<T> suthHodgClip(Polygone<T> polygone, Polygone<T> window) 
{ 
    //i and k are two consecutive indexes 
    for (int i=0; i<window.points.size(); i++) 
    { 
        int k = (i+1) % window.points.size(); 
        // We pass the current array of vertices, it's size 
        // and the end points of the selected clipper line
        Line<T> clipperLine= window.getConnectedLine(i,k); 
        polygone = clip<double>(polygone, clipperLine);
    } 
    return polygone;
} 

#endif // SUTH_HODG
