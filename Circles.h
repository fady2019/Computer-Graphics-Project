#ifndef CIRCLES_H_INCLUDED
#define CIRCLES_H_INCLUDED

#include <windows.h>
#include "Common.h"

void circleDirect(HDC, Point*, int, COLORREF);
void circlePolar(HDC, Point*, int, COLORREF);
void circleIterativePolar(HDC, Point*, int, COLORREF);
void circleMidpoint(HDC, Point*, int, COLORREF);
void circleModifiedMidpoint(HDC, Point*, int, COLORREF);
Window* getCircleWindow(HDC, Point*, int, COLORREF);

#endif
