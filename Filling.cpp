#include <windows.h>
#include "Common.h"
#include "Filling.h"
#include "Circles.h"
#include <stack>
#include "Lines.h"
#include "math.h"

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

void fillingQuarter1ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }

    fillingQuarterByLines(hdc, points, 1, color);
}

void fillingQuarter2ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }

    fillingQuarterByLines(hdc, points, 2, color);
}

void fillingQuarter3ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }

    fillingQuarterByLines(hdc, points, 3, color);
}

void fillingQuarter4ByLines(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }

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
    int radius = getLineLen(points[0], points[1]);

    for(int r=1; r<radius; r++)
    {
        drawCircle(hdc, points[0], r, quarter, color);
    }
}

void fillingQuarter1ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }
    fillingQuarterByCircles(hdc, points, 1, color);
}

void fillingQuarter2ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }
    fillingQuarterByCircles(hdc, points, 2, color);
}

void fillingQuarter3ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }
    fillingQuarterByCircles(hdc, points, 3, color);
}

void fillingQuarter4ByCircles(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    if(pointsNum < 2)
    {
        return;
    }
    fillingQuarterByCircles(hdc, points, 4, color);
}

