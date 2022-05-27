#ifndef LINES_H_INCLUDED
#define LINES_H_INCLUDED

#include <windows.h>
#include "Common.h"

void lineDDA(HDC, Point*, int, COLORREF);
void lineParametric(HDC, Point*, int, COLORREF);
void lineMidpoint(HDC, Point*, int, COLORREF);

#endif
