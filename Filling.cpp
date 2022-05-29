#include <iostream>
#include <windows.h>
#include <math.h>
#include <stack>
#include <list>
#include "Common.h"
#include "Filling.h"
#include "Circles.h"
#include "Lines.h"
#include "GeneralShapes.h"
#include "ShapesWindow.h"
#include "Curves.h"

using namespace std;

/// FloodFill (Recursive and Non Recursive)
void nonRecursiveFloodFillAlgorithm(HDC hdc, int x, int y, COLORREF bc, COLORREF fc)
{
    stack<Point> points;

    points.push(Point(x,y));

    while(!points.empty())
    {
        Point p = points.top();
        points.pop();
        COLORREF pixelColor = GetPixel(hdc, p.x, p.y);

        if(pixelColor == bc || pixelColor == fc)
        {
            continue;
        }

        SetPixel(hdc, p.x, p.y, fc);

        points.push(Point(p.x+1, p.y));
        points.push(Point(p.x-1, p.y));
        points.push(Point(p.x, p.y+1));
        points.push(Point(p.x, p.y-1));
    }
}

void recursiveFloodFillAlgorithm(HDC hdc, int x, int y, COLORREF bc, COLORREF fc)
{
    COLORREF pixelColor = GetPixel(hdc, x, y);

    if(pixelColor == bc || pixelColor == fc)
    {
        return;
    }

    SetPixel(hdc, x, y, fc);

    recursiveFloodFillAlgorithm(hdc, x+1, y, bc, fc);
    recursiveFloodFillAlgorithm(hdc, x-1, y, bc, fc);
    recursiveFloodFillAlgorithm(hdc, x, y+1, bc, fc);
    recursiveFloodFillAlgorithm(hdc, x, y-1, bc, fc);
}

void recursiveFloodFill(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    circleModifiedMidpoint(hdc, points, pointsNum, color);
    recursiveFloodFillAlgorithm(hdc, points[0].x+1, points[0].y, color, color);
}

void nonRecursiveFloodFill(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    circleModifiedMidpoint(hdc, points, pointsNum, color);
    nonRecursiveFloodFillAlgorithm(hdc, points[0].x+1, points[0].y, color, color);
}

/// filling circle by lines
void fillingQuarterByLine(HDC hdc, Point* p, int q, COLORREF color)
{
    if(q==1)
    {
        p[0].y = -p[0].y;
    }
    else if(q==2)
    {
        p[0].y = -p[0].y;
        p[0].x = -p[0].x;
    }
    else if(q==3)
    {
        p[0].x = -p[0].x;
    }
    SetPixel(hdc, p[1].x+p[0].x, p[1].y+p[0].y, color);
    Point points[2] = {p[1], Point(p[1].x+p[0].x, p[1].y+p[0].y)};
    lineParametric(hdc, points, 2, color);
    if(q==1 || q==3)
    {
        p[0].y = -p[0].y;
        p[0].x = -p[0].x;
    }
    SetPixel(hdc, p[1].x+p[0].y, p[1].y+p[0].x, color);
    points[0] = p[1];
    points[1] = Point(p[1].x+p[0].y, p[1].y+p[0].x);
    lineParametric(hdc, points, 2, color);
}

void fillingQuarterByLines(HDC hdc, Point* points, int quarter, COLORREF color)
{
    circleDirect(hdc, points, 2, color);

    int r = getLineLen(points[1], points[0]);
    int x=0;
    int y=r;
    double d=1-r;
    while(x<y)
    {
        if(d<=0)
        {
            d=d+2*x+3;
            x++;
        }
        else
        {
            d=d+2*(x-y)+5;
            x++;
            y--;
        }
        Point p[2] = {Point(x,y), points[0]};
        fillingQuarterByLine(hdc, p, quarter, color);
    }
}

void fillingQuarter1ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color){
    fillingQuarterByLines(hdc, points, 1, color);
}

void fillingQuarter2ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color){
    fillingQuarterByLines(hdc, points, 2, color);
}

void fillingQuarter3ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color){
    fillingQuarterByLines(hdc, points, 3, color);
}

void fillingQuarter4ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color){
    fillingQuarterByLines(hdc, points, 4, color);
}

/// filling circle by circles
void draw2Points(HDC hdc, Point center, int x, int y, int q, COLORREF color)
{
    int xc = center.x;
    int yc = center.y;

    if(q==1)
    {
        SetPixel(hdc, xc + x, yc - y, color);
        SetPixel(hdc, xc + y, yc - x, color);
    }
    else if(q==2)
    {
        SetPixel(hdc, xc - y, yc - x, color);
        SetPixel(hdc, xc - x, yc - y, color);
    }
    else if(q==3)
    {
        SetPixel(hdc, xc - x, yc + y, color);
        SetPixel(hdc, xc - y, yc + x, color);
    }
    else if(q==4)
    {
        SetPixel(hdc, xc + y, yc + x, color);
        SetPixel(hdc, xc + x, yc + y, color);
    }
}

void drawCircle(HDC hdc, Point center, int radius, int quarter, COLORREF color){
    float x = radius;
    float y = 0;
    float dTheta=1.0/radius;
    float cosDT=cos(dTheta);
    float sinDT=sin(dTheta);

    while(x >= y){
        draw2Points(hdc, center, round(x), round(y),quarter, color);
        float x1=x*cosDT - y*sinDT;
        y=y*cosDT + x*sinDT;
        x=x1;
    }
}

void fillingQuarterByCircles(HDC hdc, Point* points, int quarter, COLORREF color)
{
    circleDirect(hdc, points, 2, color);

    int radius = getLineLen(points[0], points[1]);

    for(int r=1; r<radius; r++)
    {
        drawCircle(hdc, points[0], r, quarter, color);
    }
}

void fillingQuarter1ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    fillingQuarterByCircles(hdc, points, 1, color);
}

void fillingQuarter2ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    fillingQuarterByCircles(hdc, points, 2, color);
}

void fillingQuarter3ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    fillingQuarterByCircles(hdc, points, 3, color);
}

void fillingQuarter4ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    fillingQuarterByCircles(hdc, points, 4, color);
}

/// Filling Square & Rectangle with Curves
void fillingSquareWithHermitCurve(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Window* sqWin = getSquareWindow(hdc, points, pointsNum, color);

    int startX = sqWin->points[0].x;
    int endX = sqWin->points[2].x;
    int startY = sqWin->points[0].y;
    int endY = sqWin->points[2].y;

    int h = (endX - startX)/4;

    for(int i=startX+1; i<endX; i++){
        Point curvePoints[] = {
            Point(i, startY),
            Point(i, startY+h),
            Point(i+1, endY-h),
            Point(i, endY)
        };

        hermitCurve(hdc, curvePoints, 4, color);
    }
}

void fillingRectangleWithBezierCurve(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Window* rqWin = getRectangleWindow(hdc, points, pointsNum, color);

    int startX = rqWin->points[0].x;
    int endX = rqWin->points[2].x;
    int startY = rqWin->points[0].y;
    int endY = rqWin->points[2].y;

    int w = (endX - startX)/4;

    for(int i=startY+1; i<endY; i++){
        Point curvePoints[] = {
            Point(startX, i),
            Point(startX+w, i),
            Point(endX-w, i+1),
            Point(endX, i)
        };

        bezierCurve(hdc, curvePoints, 4, color);
    }
}


/// FILLING POLYGON (CONVEX & NON CONVEX)
// CONVEX
void edgeToTableConvex(Point p1, Point p2, Edge table[]){
    if(p1.y == p2.y){
        return;
    }

    if(p1.y > p2.y){
        swapTwoPoints(p1, p2);
    }

    double minv = (double)(p2.x - p1.x) / (p2.y - p1.y);
    double x = p1.x;
    int y = p1.y;

    while(y < p2.y){
        if(x < table[y].xLeft){
            table[y].xLeft = (int)ceil(x);
        }

        if(x > table[y].xRight){
            table[y].xRight = (int)floor(x);
        }

        y++;
        x+=minv;
    }
}

void polygonToTableConvex(Point* points, int pointsNum, Edge table[]){
    Point p1 = points[pointsNum-1];

    for(int i=0; i<pointsNum; i++){
        Point p2 = points[i];
        edgeToTableConvex(p1, p2, table);
        p1 = points[i];
    }
}

void tableToScreenConvex(HDC hdc, Edge table[], COLORREF color){
    for(int i=0; i<EDGE_TABLE_SIZE; i++){
        if(table[i].xLeft < table[i].xRight){
            Point* line = new Point[2];
            line[0] = Point(table[i].xLeft, i);
            line[1] = Point(table[i].xRight, i);
            lineMidpoint(hdc, line, 2, color);
        }
    }
}

void fillingPolygonConvex(HDC hdc, Point* points, int pointsNum, COLORREF color){
    drawPolygon(hdc, points, pointsNum, color);

    Edge table[EDGE_TABLE_SIZE];

    polygonToTableConvex(points, pointsNum, table);

    tableToScreenConvex(hdc, table, color);
}

// NON CONVEX
void edgeToTableNonConvex(Point p1, Point p2, list<EdgeRecord> table[]){
    if(p1.y == p2.y){
        return;
    }

    if(p1.y > p2.y){
        swapTwoPoints(p1, p2);
    }

    double mInv = (double)(p2.x - p1.x) / (p2.y - p1.y);
    table[p1.y].push_back(EdgeRecord(p1.x, p2.y, mInv));
}

void polygonToTableNonConvex(Point* points, int pointsNum, list<EdgeRecord> table[]){
    Point p1 = points[pointsNum-1];

    for(int i=0; i<pointsNum; i++){
        Point p2 = points[i];
        edgeToTableNonConvex(p1, p2, table);
        p1 = points[i];
    }
}

void tableToScreenNonConvex(HDC hdc, list<EdgeRecord> table[], COLORREF color){
    int y=0;

    while(table[y].size() == 0){
        y++;
    }

    list<EdgeRecord> activeRecord = table[y];

    while(activeRecord.size() > 0 && y < EDGE_TABLE_SIZE){
        //1
        activeRecord.sort();

        //2
        for (auto it = activeRecord.begin(); it != activeRecord.end(); ++it){
            Point* line = new Point[2];
            line[0] = Point((int)ceil(it->x), y);

            if((++it) == activeRecord.end()){
                break;
            }

            line[1] = Point((int)floor(it->x), y);

            lineDDA(hdc, line, 2, color);
        }

        //3
        y++;

        //4 & 5
        for (auto it = activeRecord.begin(); it != activeRecord.end(); ++it){
            if(it->yMax == y){
                it = activeRecord.erase(it);
                --it;
            }else{
                it->x += it->mInv;
            }
        }

        // 6
        if(table[y].size() > 0){
            for(auto it = table[y].begin(); it != table[y].end(); ++it){
                activeRecord.push_back(*it);
            }
        }
    }
}

void fillingPolygonNonConvex(HDC hdc, Point* points, int pointsNum, COLORREF color){
    drawPolygon(hdc, points, pointsNum, color);

    list<EdgeRecord> table[EDGE_TABLE_SIZE];

    polygonToTableNonConvex(points, pointsNum, table);

    tableToScreenNonConvex(hdc, table, color);
}
