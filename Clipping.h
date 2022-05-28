#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED

#include <windows.h>
#include "Common.h"

union OutCode
{
    unsigned all:4;
    struct
    {
        unsigned left:1, right:1, bottom:1, top:1;
    };
};


void clippingPointWithSquareOrRectangleWindow(HDC, Point*, int, COLORREF);
void clippingLineWithSquareOrRectangleWindow(HDC, Point*, int, COLORREF);
void clippingPolygonWithRectangleWindow(HDC, Point*, int, COLORREF);
void clippingPointWithCircleWindow(HDC, Point*, int, COLORREF);
void clippingLineWithCircleWindow(HDC, Point*, int, COLORREF);

#endif
