#include <windows.h>
#include "Common.h"
#include "Filling.h"
#include "Circles.h"
#include <stack>
#include "Lines.h"

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
    if(pointsNum < 2)
    {
        return;
    }

    circleModifiedMidpoint(hdc, points, pointsNum, color);
    recursiveFloodFillAlgorithm(hdc, points[0].x+1, points[0].y, color, color);
}

void nonRecursiveFloodFill(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }

    circleModifiedMidpoint(hdc, points, pointsNum, color);
    nonRecursiveFloodFillAlgorithm(hdc, points[0].x+1, points[0].y, color, color);
}


void lineFillingAlgorithm(HDC hdc,Point* p, int q,COLORREF color)
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
    lineParametric(hdc, points, 2,color);
}

void lineFilling(HDC hdc, Point* points, int pointsNum, COLORREF color)
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
        lineFillingAlgorithm(hdc, p, 3, color);
    }
}


