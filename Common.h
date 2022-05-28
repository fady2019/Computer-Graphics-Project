#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <iostream>
#include <windows.h>
#include "Menus.h"

#define BLACK_COLOR     RGB(0,0,0)
#define RED_COLOR       RGB(255,0,0)
#define ORANGE_COLOR    RGB(255,128,0)
#define YELLOW_COLOR    RGB(255,255,0)
#define GREEN_COLOR     RGB(0,255,0)
#define BLUE_COLOR      RGB(0,0,255)
#define PURPLE_COLOR    RGB(128,0,128)
#define TAEL_COLOR      RGB(0,128,128)
#define GRAY_COLOR      RGB(128,128,128)
#define CYAN_COLOR      RGB(0,255,255)
#define GOLD_COLOR      RGB(255,215,0)
#define SILVER_COLOR    RGB(192,192,192)

using namespace std;

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

    void print()
    {
        cout<<"Point ("<<this->x<<","<<this->y<<")"<<endl;
    }
};

template <typename T>
struct System
{
    Point points[100];
    int count=0;
    int maxCount=0;
    T (*shaper) (HDC, Point* , int, COLORREF) = 0;
    MenuIDs mode;
    COLORREF color = GOLD_COLOR;
};


int roundNum(float);
void swapTwoPoints(Point&, Point&);
void draw8Points(HDC, Point, int, int, COLORREF);
void draw4Points(HDC, Point, int, int, COLORREF);
int getLineLen(Point, Point);
Point getNearestPoint(Point, Point);
Point* mergeTwoArray(Point*, int, Point*, int);

#endif
