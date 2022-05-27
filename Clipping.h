#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include <windows.h>
#include "Common.h"

void clippingPointWithSquareWindow(HDC, Point*, int, COLORREF);
void clippingLineWithSquareWindow(HDC, Point*, int, COLORREF);

#endif
