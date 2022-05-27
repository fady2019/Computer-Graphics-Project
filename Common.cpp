#include "Common.h"
#include <cmath>

int roundNum(float num){
    return (int)(num+0.5);
}

void swapTwoPoints(Point& p1, Point& p2){
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

void draw8Points(HDC hdc, Point center, int x, int y, COLORREF color)
{
    int xc = center.x;
    int yc = center.y;

	SetPixel(hdc, xc + x, yc + y, color);
	SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc + x, yc - y, color);

    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc - y, yc - x, color);
	SetPixel(hdc, xc - x, yc - y, color);
}

void draw4Points(HDC hdc, Point center, int x, int y, COLORREF color)
{
    int xc = center.x;
    int yc = center.y;

	SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc + y, color);
	SetPixel(hdc, xc - x, yc - y, color);
}

int getLineLen(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    return sqrt((dx*dx) + (dy*dy));
}

Point getSmallPoint(Point p1, Point p2){
    return getLineLen(Point(0,0), p1) < getLineLen(Point(0,0), p2)? p1 : p2;
}

Point* mergeTwoArray(Point* points1, int points1Num, Point* points2, int points2Num){
    int arraySize = points1Num+points2Num;
    Point* mergedArray = new Point[arraySize];

    int j=0;

    for(int i=0; i<points1Num; i++){
        mergedArray[j] = points1[i];
        j++;
    }

    for(int i=0; i<points2Num; i++){
        mergedArray[j] = points2[i];
        j++;
    }

    return mergedArray;
}
