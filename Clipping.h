#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include <windows.h>
#include "Common.h"

Window* getSquareWindow(HDC, Point*, int, COLORREF);
Window* getRectangleWindow(HDC, Point*, int, COLORREF);
Window* getCircleWindow(HDC, Point*, int, COLORREF);

void clippingPointWithSquareOrRectangleWindow(HDC, Point*, int, COLORREF);
void clippingLineWithSquareOrRectangleWindow(HDC, Point*, int, COLORREF);
void clippingPointWithCircleWindow(HDC, Point*, int, COLORREF);
void clippingLineWithCircleWindow(HDC, Point*, int, COLORREF);

#endif
