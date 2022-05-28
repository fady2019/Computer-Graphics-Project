#include <windows.h>
#include "GeneralShapes.h"
#include "Common.h"
#include "Lines.h"

void drawSquareOrRectangle(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 4){
        return;
    }

    for(int i=0; i<4; i++){
        Point line[2] = {Point(points[i].x, points[i].y)};

        if(i == 3){
            line[1] = Point(points[0].x, points[0].y);
        }else{
            line[1] = Point(points[i+1].x, points[i+1].y);
        }

        lineDDA(hdc, line, 2, color);
    }
}

void drawPolygon(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 3){
        return;
    }

    Point p1 = points[pointsNum-1];

    for(int i=0; i<pointsNum; i++){
        Point* line = new Point[2];
        line[0] = p1;
        line[1] = points[i];
        lineMidpoint(hdc, line, 2, color);
        p1 = points[i];
    }
}