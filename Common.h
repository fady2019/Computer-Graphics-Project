#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <windows.h>
#include "Menus.h"

struct Point
{
    int x;
    int y;

    Point(int x=0, int y=0){
        this->x = x;
        this->y = y;
    }

    Point operator-(Point p2)
    {
        return Point(x-p2.x, y-p2.y);
    }

    Point operator*(float num)
    {
        return Point(x*num, y*num);
    }
};

struct System
{
    Point points[100];
    int count=0;
    int maxCount=0;
    void (*shaper) (HDC, Point* , int, COLORREF) = 0;
    MenuIDs mode;
    COLORREF color = RGB(0,0,0);
};

union OutCode
{
    unsigned all:4;
    struct
    {
        unsigned left:1, right:1, bottom:1, top:1;
    };
};

int roundNum(float);
void swapTwoPoints(Point&, Point&);
void draw8Points(HDC, Point, int, int, COLORREF);
void draw4Points(HDC, Point, int, int, COLORREF);
int getLineLen(Point, Point);
Point getSmallPoint(Point, Point);

#endif
