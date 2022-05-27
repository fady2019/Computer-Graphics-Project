#include <windows.h>
#include "Common.h"
#include "Filling.h"
#include "Circles.h"
#include <stack>

void nonRecursiveFloodFillAlgorithm(HDC hdc, int x, int y, COLORREF bc, COLORREF fc){
    stack<Point> points;

    points.push(Point(x,y));

    while(!points.empty()){
        Point p = points.top();
        points.pop();
        COLORREF pixelColor = GetPixel(hdc, p.x, p.y);

        if(pixelColor == bc || pixelColor == fc){
            continue;
        }

        SetPixel(hdc, p.x, p.y, fc);

        points.push(Point(p.x+1, p.y));
        points.push(Point(p.x-1, p.y));
        points.push(Point(p.x, p.y+1));
        points.push(Point(p.x, p.y-1));
    }
}

void recursiveFloodFillAlgorithm(HDC hdc, int x, int y, COLORREF bc, COLORREF fc){
    COLORREF pixelColor = GetPixel(hdc, x, y);

    if(pixelColor == bc || pixelColor == fc){
        return;
    }

    SetPixel(hdc, x, y, fc);

    recursiveFloodFillAlgorithm(hdc, x+1, y, bc, fc);
    recursiveFloodFillAlgorithm(hdc, x-1, y, bc, fc);
    recursiveFloodFillAlgorithm(hdc, x, y+1, bc, fc);
    recursiveFloodFillAlgorithm(hdc, x, y-1, bc, fc);
}

void recursiveFloodFill(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 2){
        return;
    }

    circleModifiedMidpoint(hdc, points, pointsNum, color);
    recursiveFloodFillAlgorithm(hdc, points[0].x+1, points[0].y, color, color);
}

void nonRecursiveFloodFill(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 2){
        return;
    }
    
    circleModifiedMidpoint(hdc, points, pointsNum, color);
    nonRecursiveFloodFillAlgorithm(hdc, points[0].x+1, points[0].y, color, color);
}
