#include <windows.h>
#include "GeneralShapes.h"
#include "Common.h"
#include "Lines.h"

void drawSquare(HDC hdc, Point* points, int pointsNum, COLORREF color){

}

void drawRectangle(HDC hdc, Point* points, int pointsNum, COLORREF color){

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