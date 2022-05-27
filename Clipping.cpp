#include <iostream>
#include "Clipping.h"
#include "Common.h"
#include "Lines.h"

using namespace std;

Point* getSquareWindow(HDC hdc, Point p1, Point p2, COLORREF color){
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

    return sp;
}

void clippingPointWithSquareWindow(HDC hdc, Point* points, int pointsNum, COLORREF color){
    if(pointsNum < 3){
        return;
    }

    Point* sqWin = getSquareWindow(hdc, points[0], points[1], color);

    for(int i=2; i<pointsNum; i++){
        if(
           points[i].x >= sqWin[0].x &&
           points[i].x <= sqWin[2].x &&
           points[i].y >= sqWin[0].y &&
           points[i].y <= sqWin[2].y
        ){
            cout<<"Point is inside"<<endl;
            SetPixel(hdc, points[i].x, points[i].y, color);
        }else{
            cout<<"Point is outside"<<endl;
            //SetPixel(hdc, points[i].x, points[i].y, RGB(255,255,255));
        }
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
    if(pointsNum < 4){
        return;
    }

    Point* sqWin = getSquareWindow(hdc, points[0], points[1], color);

    for(int i=2; i<pointsNum; i+=2){
        if((i+1) < pointsNum){
            if(clipLine(sqWin, points[i], points[i+1])){
                Point line[2] = {Point(points[i].x, points[i].y), Point(points[i+1].x, points[i+1].y)};
                lineDDA(hdc, line, 2, color);
            }
        }
    }
}
