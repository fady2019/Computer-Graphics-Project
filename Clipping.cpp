#include <iostream>
#include <windows.h>
#include "Clipping.h"
#include "Common.h"
#include "Lines.h"
#include <vector>
using namespace std;

typedef vector<Point> VertexList;
typedef bool (*IsInFunc)(Point v,int edge);
typedef Point (*IntersectFunc)(Point v1,Point v2,int edge);

/// Point Clipping with (Square & Rectangle) Window
void clippingPointWithSquareOrRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Point sqWin[] = {points[0], points[1], points[2], points[3]};

    Point point = points[4];

    if(
       point.x >= sqWin[0].x &&
       point.x <= sqWin[2].x &&
       point.y >= sqWin[0].y &&
       point.y <= sqWin[2].y
    ){
        cout<<"Point is inside"<<endl;
        SetPixel(hdc, point.x, point.y, color);
    }else{
        cout<<"Point is outside"<<endl;
        SetPixel(hdc, point.x, point.y, RGB(255,255,255));
    }
}

/// Line Clipping with (Square & Rectangle) Window
OutCode getOutCode(Point point, int left, int right, int bottom, int top){
    OutCode outCode;
    outCode.all = 0;

    if(point.x < left){
        outCode.left = 1;
    }else if(point.x > right){
        outCode.right = 1;
    }

    if(point.y < top){
        outCode.top = 1;
    }else if(point.y > bottom){
        outCode.bottom = 1;
    }

    return outCode;
}

void VIntersect(Point p1, Point p2, int xEdge, Point& pIn){
    pIn.y = p1.y + (xEdge - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
    pIn.x = xEdge;
}

void HIntersect(Point p1, Point p2, int yEdge, Point& pIn){
    pIn.x = p1.x + (yEdge - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
    pIn.y = yEdge;
}

bool clipLine(Point* window, Point& p1, Point& p2){
    OutCode outCode1 = getOutCode(p1, window[0].x, window[2].x, window[2].y, window[0].y);
    OutCode outCode2 = getOutCode(p2, window[0].x, window[2].x, window[2].y, window[0].y);

    while(true){
        if(outCode1.all & outCode2.all){
            return false;
        }

        if(!outCode1.all & !outCode2.all){
            return true;
        }

        if(outCode1.all)
        {
            if(outCode1.left){
                VIntersect(p1, p2, window[0].x, p1);
            }else if(outCode1.right){
                VIntersect(p1, p2, window[2].x, p1);
            }else if(outCode1.bottom){
                HIntersect(p1, p2, window[2].y, p1);
            }else{
                HIntersect(p1, p2, window[0].y, p1);
            }

            outCode1 = getOutCode(p1, window[0].x, window[2].x, window[2].y, window[0].y);
        }
        else
        {
            if(outCode2.left){
                VIntersect(p1, p2, window[0].x, p2);
            }else if(outCode2.right){
                VIntersect(p1, p2, window[2].x, p2);
            }else if(outCode2.bottom){
                HIntersect(p1, p2, window[2].y, p2);
            }else{
                HIntersect(p1, p2, window[0].y, p2);
            }

            outCode2 = getOutCode(p2, window[0].x, window[2].x, window[2].y, window[0].y);
        }
    }
}

void clippingLineWithSquareOrRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Point sqWin[] = {points[0], points[1], points[2], points[3]};

    Point point1 = points[4];
    Point point2 = points[5];

    if(clipLine(sqWin, point1, point2)){
        Point line[2] = {Point(point1.x, point1.y), Point(point2.x, point2.y)};
        lineDDA(hdc, line, 2, color);
    }
}


/// Polygon Clipping with Rectangle Window
VertexList ClipWithEdge(VertexList p,int edge,IsInFunc In,IntersectFunc Intersect)
{
    VertexList OutList;
    Point v1=p[p.size()-1];
    bool v1_in=In(v1,edge);
    for(int i=0;i<(int)p.size();i++)
    {
        Point v2=p[i];
        bool v2_in=In(v2,edge);
        if(!v1_in && v2_in)
        {
            OutList.push_back(Intersect(v1,v2,edge));
            OutList.push_back(v2);
        }
        else if(v1_in && v2_in)
            OutList.push_back(v2);
        else if(v1_in)
            OutList.push_back(Intersect(v1,v2,edge));
        else
        {
        }
        v1=v2;
        v1_in=v2_in;
    }
    return OutList;
}

bool InLeft(Point v,int edge)
{
    return v.x>=edge;
}

bool InRight(Point v,int edge)
{
    return v.x<=edge;
}

bool InTop(Point v,int edge)
{
    return v.y>=edge;
}

bool InBottom(Point v,int edge)
{
    return v.y<=edge;
}

Point VVIntersect(Point v1,Point v2,int xedge)
{
    Point res;
    res.x=xedge;
    res.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
    return res;
}

Point HHIntersect(Point v1,Point v2,int yedge)
{
    Point res;
    res.y=yedge;
    res.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
    return res;
}

void clippingPolygonWithRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    VertexList vlist;
    Point sqWin[] = {points[0], points[1], points[2], points[3]};

    Point* polygonPoints = new Point[pointsNum-4];

    for(int i=4; i<pointsNum; i++){
        polygonPoints[i-4] = points[i];
    }

    for(int i=0;i<pointsNum-4;i++)
    {
        vlist.push_back(Point(polygonPoints[i].x,polygonPoints[i].y));
    }
    vlist=ClipWithEdge(vlist,sqWin[0].x,InLeft,VVIntersect);
    if(vlist.size()==0)
    {
        cout<<"all Polygon points are outside"<<endl;
        return;
    }
    vlist=ClipWithEdge(vlist,sqWin[0].y,InTop,HHIntersect);
    if(vlist.size()==0)
    {
        cout<<"all Polygon points are outside"<<endl;
        return;
    }
    vlist=ClipWithEdge(vlist,sqWin[2].x,InRight,VVIntersect);
    if(vlist.size()==0)
    {
        cout<<"all Polygon points are outside"<<endl;
        return;
    }
    vlist=ClipWithEdge(vlist,sqWin[2].y,InBottom,HHIntersect);
    if(vlist.size()==0)
    {
        cout<<"all Polygon points are outside"<<endl;
        return;
    }
    Point v1=vlist[vlist.size()-1];

    for(int i=0;i<(int)vlist.size();i++)
    {
        Point v2=vlist[i];
        Point line[2] = {Point(roundNum(v1.x), roundNum(v1.y)), Point(roundNum(v2.x), roundNum(v2.y))};
        lineDDA(hdc, line, 2, color);
        v1=v2;
    }
}
/// circle clipping
void clippingPointWithCircleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int R = getLineLen(points[0], points[1]);
    int r = getLineLen(points[0],points[2]);

    if(r <= R)
    {
        cout<<"Point is inside"<<endl;
        SetPixel(hdc, points[2].x, points[2].y, color);
    }else{
        cout<<"Point is outside"<<endl;
        SetPixel(hdc, points[2].x, points[2].y, RGB(255,255,255));
    }
}

void clippingLineWithCircleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int R = getLineLen(points[0], points[1]);

    Point p1 = points[2];
    Point p2 = points[3];
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    for(double t = 0; t < 1; t += 0.001) {
        int x = p1.x + (dx * t);
        int y = p1.y + (dy * t);
        int r = getLineLen(Point(x,y), points[0]);
        if(r <= R)
        {
            SetPixel(hdc, x, y, color);
        }
        else
        {
            SetPixel(hdc, x, y, RGB(255,255,255));
        }
    }

}
