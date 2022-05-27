#ifndef ELLIPSES_H_INCLUDED
#define ELLIPSES_H_INCLUDED

#include <windows.h>
#include "Common.h"

void ellipseDirect(HDC, Point*, int, COLORREF);
void ellipsePolar(HDC, Point*, int, COLORREF);
void ellipseMidpoint(HDC, Point*, int, COLORREF);

#endif
