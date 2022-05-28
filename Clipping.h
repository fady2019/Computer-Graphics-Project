#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include <windows.h>
#include "Common.h"

Window* getSquareWindow(HDC, Point*, int, COLORREF);
Window* getRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color);
Window* getCircleWindow(HDC, Point*, int, COLORREF);

void clippingPointWithSquareOrRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color);
void clippingLineWithSquareOrRectangleWindow(HDC hdc, Point* points, int pointsNum, COLORREF color);
void clippingPointWithCircleWindow(HDC, Point*, int, COLORREF);

#endif
