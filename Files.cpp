#include <windows.h>
#include "Files.h"

// Implement item to clear screen from shapes
void clearScreen(HWND hwnd){
    InvalidateRect (hwnd, NULL, TRUE);
}

