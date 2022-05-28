#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include <windows.h>
#include "Common.h"

void clippingPointSquareWindow(HDC hdc, Point* points, int pointsNum, COLORREF color);
void clippingLineWithSquareWindow(HDC hdc, Point* points, int pointsNum, COLORREF color);
Window* getSquareWindow(HDC, Point*, int, COLORREF);
void clippingPointWithCircleWindow(HDC, Point*, int, COLORREF);
Window* getCircleWindow(HDC, Point*, int, COLORREF);
Window* getRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color);
void clippingLineWithRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color);
#endif
