#ifndef SHAPES_WINDOW_H_INCLUDED
#define SHAPES_WINDOW_H_INCLUDED

#include <windows.h>
#include "Common.h"

struct Window{
    Point* points=0;
    int pointsNum=0;
};

Window* getSquareWindow(HDC, Point*, int, COLORREF);
Window* getRectangleWindow(HDC, Point*, int, COLORREF);
Window* getCircleWindow(HDC, Point*, int, COLORREF);

#endif
