#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include <windows.h>
#include "Common.h"

void clippingPointWithSquareOrRectangleWindow(HDC, Point*, int, COLORREF);
void clippingLineWithSquareOrRectangleWindow(HDC, Point*, int, COLORREF);
void clippingPolygonWithRectangleWindow(HDC, Point*, int, COLORREF);
void clippingPointWithCircleWindow(HDC, Point*, int, COLORREF);
void clippingLineWithCircleWindow(HDC, Point*, int, COLORREF);

#endif
