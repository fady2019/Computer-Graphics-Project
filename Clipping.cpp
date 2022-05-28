#include <iostream>
#include "Clipping.h"
#include "Common.h"
#include "Lines.h"
#include "Circles.h"

using namespace std;

Window* getSquareWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 2){
        return 0;
    }

    Point p1 = points[0];
    Point p2 = points[1];

    int dist = getLineLen(p1, p2);
    Point smallPoint = getSmallPoint(p1, p2);

    Point* sp = new Point[4];
    sp[0] = smallPoint;
    sp[1] = Point(smallPoint.x+dist, smallPoint.y);
    sp[2] = Point(smallPoint.x+dist, smallPoint.y+dist);
    sp[3] = Point(smallPoint.x, smallPoint.y+dist);

    for(int i=0; i<4; i++){
        Point line[2] = {Point(sp[i].x, sp[i].y)};

        if(i == 3){
            line[1] = Point(sp[0].x, sp[0].y);
        }else{
            line[1] = Point(sp[i+1].x, sp[i+1].y);
        }

        lineDDA(hdc, line, 2, color);
    }

    Window* win = new Window;
    win->points = sp;
    win->pointsNum = 4;

    return win;
}
Window* getRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum<3)
        return 0;
    Point p1 = points[0];
    Point p2 = points[1];
    Point p3 = points[2];
    Point smallPoint1 = getSmallPoint(p1, p2);
    Point smallPoint2=getSmallPoint(smallPoint1,p3);
    int dist=0;
    int dist2=0;
    if((smallPoint2.x==p1.x)&&(smallPoint2.y=p1.y))
    {
        dist = getLineLen(p2, p3);
        dist2=getLineLen(smallPoint2,p2);
    }
    else if((smallPoint2.x==p2.x)&&(smallPoint2.y=p2.y))
    {
        dist = getLineLen(p1, p3);
        dist2=getLineLen(smallPoint2,p2);

    }
    else if((smallPoint2.x==p3.x)&&(smallPoint2.y=p3.y))
    {
        dist = getLineLen(p1, p2);
        dist2=getLineLen(smallPoint2,p1);
    }
    Point* sp = new Point[4];
    sp[0] = smallPoint2;
    sp[1] = Point(smallPoint2.x+dist, smallPoint2.y);
    sp[2] = Point(smallPoint2.x+dist, smallPoint2.y+dist);
    sp[3] = Point(smallPoint2.x, smallPoint2.y+dist);
    for(int i=0; i<4; i++){
        Point line[2] = {Point(sp[i].x, sp[i].y)};
        if(i == 3){
            line[1] = Point(sp[0].x, sp[0].y);
        }else{
            line[1] = Point(sp[i+1].x, sp[i+1].y);
        }
        lineDDA(hdc, line, 2, color);
    }
    Window* win = new Window;
    win->points = sp;
    win->pointsNum = 4;

    return win;
}
void clippingPointSquareWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 5){
        return;
    }

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

OutCode getOutCode(Point point, int left, int right, int bottom, int top)
{
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

void VIntersect(Point p1, Point p2, int xEdge, Point& pIn)
{
    pIn.y = p1.y + (xEdge - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
    pIn.x = xEdge;
}

void HIntersect(Point p1, Point p2, int yEdge, Point& pIn)
{
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

void clippingLineWithSquareWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 6){
        return;
    }

    Point sqWin[] = {points[0], points[1], points[2], points[3]};

    Point point1 = points[4];
    Point point2 = points[5];

    if(clipLine(sqWin, point1, point2)){
        Point line[2] = {Point(point1.x, point1.y), Point(point2.x, point2.y)};
        lineDDA(hdc, line, 2, color);
    }
}
void clippingLineWithRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 6){
        return;
    }

    Point sqWin[] = {points[0], points[1], points[2], points[3]};

    Point point1 = points[4];
    Point point2 = points[5];

    if(clipLine(sqWin, point1, point2)){
        Point line[2] = {Point(point1.x, point1.y), Point(point2.x, point2.y)};
        lineDDA(hdc, line, 2, color);
    }
}

/// circle clipping
Window* getCircleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 2){
        return 0;
    }

    circleDirect(hdc, points, 2, color);

    Window* win = new Window;
    win->points = points;
    win->pointsNum = 2;

    return win;
}

void clippingPointWithCircleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 3){
        return;
    }

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


