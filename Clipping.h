#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include <windows.h>
#include "Common.h"

void clippingPointWithSquareWindow(HDC, Point*, int, COLORREF);
void clippingLineWithSquareWindow(HDC, Point*, int, COLORREF);
Window* getSquareWindow(HDC, Point*, int, COLORREF);
void clippingPointWithCircleWindow(HDC, Point*, int, COLORREF);
Window* getCircleWindow(HDC, Point*, int, COLORREF);

#endif
