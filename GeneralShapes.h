#ifndef GENERAL_SHAPES_H_INCLUDED
#define GENERAL_SHAPES_H_INCLUDED

#include <windows.h>
#include "Common.h"

void drawSquare(HDC, Point*, int, COLORREF);
void drawRectangle(HDC, Point*, int, COLORREF);
void drawPolygon(HDC, Point*, int, COLORREF);

#endif
