#ifndef FILLING_H_INCLUDED
#define FILLING_H_INCLUDED

#include <windows.h>
#include "Common.h"

void recursiveFloodFill(HDC, Point*, int, COLORREF);
void nonRecursiveFloodFill(HDC, Point*, int, COLORREF);

#endif
