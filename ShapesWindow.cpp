#include <windows.h>
#include "ShapesWindow.h"
#include "Circles.h"
#include "Lines.h"
#include "GeneralShapes.h"


Window* getSquareOrRectangleWindow(HDC hdc, Point point, int width, int height, COLORREF color){  
    Point* points = new Point[4];
    points[0] = point;
    points[1] = Point(point.x+width, point.y);
    points[2] = Point(point.x+width, point.y+height);
    points[3] = Point(point.x, point.y+height);

    drawSquareOrRectangle(hdc, points, 4, color);

    Window* win = new Window;
    win->points = points;
    win->pointsNum = 4;

    return win;
}

Window* getSquareWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Point p1 = points[0];
    Point p2 = points[1];

    int sideLen = getLineLen(p1, p2);
    Point nearestPoint = getNearestPoint(p1, p2);

    return getSquareOrRectangleWindow(hdc, nearestPoint, sideLen, sideLen, color);
}

Window* getRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Point p1 = points[0];
    Point p2 = points[1];
    Point p3 = points[2];

    Point nearestPoint = getNearestPoint(p1, p2);
    nearestPoint = getNearestPoint(nearestPoint,p3);

    int width=0;
    int height=0;

    if((nearestPoint.x==p1.x)&&(nearestPoint.y=p1.y))
    {
        width = getLineLen(p1, p2);
        height = getLineLen(p1, p3);
    }
    else if((nearestPoint.x==p2.x)&&(nearestPoint.y=p2.y))
    {
        width = getLineLen(p2, p1);
        height = getLineLen(p2,p3);

    }
    else if((nearestPoint.x==p3.x)&&(nearestPoint.y=p3.y))
    {
        width = getLineLen(p3, p1);
        height = getLineLen(p3,p2);
    }

    return getSquareOrRectangleWindow(hdc, nearestPoint, width, height, color);
}

Window* getCircleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    circleDirect(hdc, points, 2, color);

    Window* win = new Window;
    win->points = points;
    win->pointsNum = 2;

    return win;
}
