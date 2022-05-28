#ifndef FILLING_H_INCLUDED
#define FILLING_H_INCLUDED

#include <windows.h>
#include "Common.h"

void recursiveFloodFill(HDC, Point*, int, COLORREF);
void nonRecursiveFloodFill(HDC, Point*, int, COLORREF);
void fillingQuarter1ByLines(HDC, Point*, int, COLORREF);
void fillingQuarter2ByLines(HDC, Point*, int, COLORREF);
void fillingQuarter3ByLines(HDC, Point*, int, COLORREF);
void fillingQuarter4ByLines(HDC, Point*, int, COLORREF);
void fillingQuarter1ByCircles(HDC, Point*, int, COLORREF);
void fillingQuarter2ByCircles(HDC, Point*, int, COLORREF);
void fillingQuarter3ByCircles(HDC, Point*, int, COLORREF);
void fillingQuarter4ByCircles(HDC, Point*, int, COLORREF);

#endif
