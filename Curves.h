#ifndef CURVES_H_INCLUDED
#define CURVES_H_INCLUDED

#include <windows.h>
#include "Common.h"

void hermitCurve(HDC, Point*, int, COLORREF);
void bezierCurve(HDC, Point*, int, COLORREF);
void cardinalSplineCurve(HDC, Point*, int, COLORREF);

#endif
