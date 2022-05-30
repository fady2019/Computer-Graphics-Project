#include "Menus.h"

void createOwnMenu(HWND hwnd){
    HMENU hMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createFilePopupMenu(), "File");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createColorPopupMenu(), "Colors");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createLinePopupMenu() , "Line");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createCirclePopupMenu() , "Circle");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createEllipsePopupMenu() , "Ellipse");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createCurvePopupMenu() , "Curve");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createFillingPopupMenu() , "Filling");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)createClippingPopupMenu() , "Clipping");


    SetMenu(hwnd, hMenu);
}

HMENU createFilePopupMenu(){
    HMENU hFileMenu = CreateMenu();

    AppendMenu(hFileMenu, MF_STRING, CLEAR_MENU, "clear");
    AppendMenu(hFileMenu, MF_STRING, SAVE_MENU, "save");
    AppendMenu(hFileMenu, MF_STRING, LOAD_MENU, "load");

    return hFileMenu;
}

HMENU createColorPopupMenu(){
    HMENU hColorMenu = CreateMenu();

    AppendMenu(hColorMenu, MF_STRING, COLOR_BLACK, "black");
    AppendMenu(hColorMenu, MF_STRING, COLOR_RED, "red");
    AppendMenu(hColorMenu, MF_STRING, COLOR_YELLOW, "yellow");
    AppendMenu(hColorMenu, MF_STRING, COLOR_ORANGE, "orange");
    AppendMenu(hColorMenu, MF_STRING, COLOR_GREEN, "green");
    AppendMenu(hColorMenu, MF_STRING, COLOR_BLUE, "blue");
    AppendMenu(hColorMenu, MF_STRING, COLOR_PURPLE, "purple");
    AppendMenu(hColorMenu, MF_STRING, COLOR_TAEL, "tael");
    AppendMenu(hColorMenu, MF_STRING, COLOR_GRAY, "gray");
    AppendMenu(hColorMenu, MF_STRING, COLOR_CYAN, "cyan");
    AppendMenu(hColorMenu, MF_STRING, COLOR_GOLD, "gold");
    AppendMenu(hColorMenu, MF_STRING, COLOR_SILVER, "silver");


    return hColorMenu;
}

HMENU createLinePopupMenu(){
    HMENU hLineMenu = CreateMenu();

    AppendMenu(hLineMenu, MF_STRING, LINE_DDA_MENU, "DDA");
    AppendMenu(hLineMenu, MF_STRING, LINE_MID_MENU, "Midpoint");
    AppendMenu(hLineMenu, MF_STRING, LINE_PARA_MENU, "Parametric");

    return hLineMenu;
}

HMENU createCirclePopupMenu(){
    HMENU hCircleMenu = CreateMenu();

    AppendMenu(hCircleMenu, MF_STRING, CIR_DIRECT_MENU, "Direct");
    AppendMenu(hCircleMenu, MF_STRING, CIR_POLAR_MENU, "Polar");
    AppendMenu(hCircleMenu, MF_STRING, CIR_ITER_POLAR_MENU, "Iterative Polar");
    AppendMenu(hCircleMenu, MF_STRING, CIR_MID_MENU, "MidPoint");
    AppendMenu(hCircleMenu, MF_STRING, CIR_MOD_MID_MENU, "Modified MidPoint");

    return hCircleMenu;
}

HMENU createEllipsePopupMenu(){
    HMENU hEllipseMenu = CreateMenu();

    AppendMenu(hEllipseMenu, MF_STRING, ELL_DIRECT_MENU, "Direct");
    AppendMenu(hEllipseMenu, MF_STRING, ELL_POLAR_MENU, "Polar");
    AppendMenu(hEllipseMenu, MF_STRING, ELL_MID_MENU, "Midpoint");

    return hEllipseMenu;
}

HMENU createCurvePopupMenu(){
    HMENU hCurveMenu = CreateMenu();

    AppendMenu(hCurveMenu, MF_STRING, CURVE_HERMIT_MENU, "Hermit");
    AppendMenu(hCurveMenu, MF_STRING, CURVE_BEZIER_MENU, "Bezier");
    AppendMenu(hCurveMenu, MF_STRING, CURVE_CAR_SPL_MENU, "Cardinal Spline");

    return hCurveMenu;
}

HMENU createFillingCircleWithLinesPopupMenu(){
    HMENU hFillingCircleWithLinesMenu = CreateMenu();

    AppendMenu(hFillingCircleWithLinesMenu, MF_STRING, FILLING_CIR_WITH_LINES_Q1_MENU, "Quarter1");
    AppendMenu(hFillingCircleWithLinesMenu, MF_STRING, FILLING_CIR_WITH_LINES_Q2_MENU, "Quarter2");
    AppendMenu(hFillingCircleWithLinesMenu, MF_STRING, FILLING_CIR_WITH_LINES_Q3_MENU, "Quarter3");
    AppendMenu(hFillingCircleWithLinesMenu, MF_STRING, FILLING_CIR_WITH_LINES_Q4_MENU, "Quarter4");

    return hFillingCircleWithLinesMenu;
}

HMENU createFillingPopupMenu(){
    HMENU hFillingMenu = CreateMenu();

    AppendMenu(hFillingMenu, MF_POPUP, (UINT_PTR)createFillingCircleWithLinesPopupMenu(), "Circle With Lines");
    AppendMenu(hFillingMenu, MF_STRING, FILLING_CIR_WITH_CIRS_MENU, "Circle With Circles");
    AppendMenu(hFillingMenu, MF_STRING, FILLING_SQUARE_WITH_HERMIT_MENU, "Square With Hermit");
    AppendMenu(hFillingMenu, MF_STRING, FILLING_REC_WITH_BEZIER_MENU, "Rectangle With Bezier");
    AppendMenu(hFillingMenu, MF_STRING, FILLING_CONVEX_MENU, "Convex");
    AppendMenu(hFillingMenu, MF_STRING, FILLING_NON_CONVEX_MENU, "Non Convex");
    AppendMenu(hFillingMenu, MF_STRING, FILLING_RECUR_FF_MENU, "Recursive FloodFill");
    AppendMenu(hFillingMenu, MF_STRING, FILLING_NON_RECUR_FF_MENU, "Non Recursive FloodFill");

    return hFillingMenu;
}

HMENU createClippingRecWinPopupMenu(){
    HMENU hClippingRecWinMenu = CreateMenu();

    AppendMenu(hClippingRecWinMenu, MF_STRING, CLIPPING_REC_WIN_POINT_MENU, "Point");
    AppendMenu(hClippingRecWinMenu, MF_STRING, CLIPPING_REC_WIN_LINE_MENU, "Line");
    AppendMenu(hClippingRecWinMenu, MF_STRING, CLIPPING_REC_WIN_POL_MENU, "Polygon");

    return hClippingRecWinMenu;
}

HMENU createClippingSquareWinPopupMenu(){
    HMENU hClippingSquareWinMenu = CreateMenu();

    AppendMenu(hClippingSquareWinMenu, MF_STRING, CLIPPING_SQUARE_WIN_POINT_MENU, "Point");
    AppendMenu(hClippingSquareWinMenu, MF_STRING, CLIPPING_SQUARE_WIN_LINE_MENU, "Line");

    return hClippingSquareWinMenu;
}

HMENU createClippingCirWinPopupMenu(){
    HMENU hClippingCirWinMenu = CreateMenu();

    AppendMenu(hClippingCirWinMenu, MF_STRING, CLIPPING_CIR_WIN_POINT_MENU, "Point");
    AppendMenu(hClippingCirWinMenu, MF_STRING, CLIPPING_CIR_WIN_LINE_MENU, "Line");

    return hClippingCirWinMenu;
}

HMENU createClippingPopupMenu(){
    HMENU hClippingMenu = CreateMenu();

    AppendMenu(hClippingMenu, MF_POPUP, (UINT_PTR)createClippingRecWinPopupMenu(), "Rectangle Window");
    AppendMenu(hClippingMenu, MF_POPUP, (UINT_PTR)createClippingSquareWinPopupMenu(), "Square Window");
    AppendMenu(hClippingMenu, MF_POPUP, (UINT_PTR)createClippingCirWinPopupMenu(), "Circle Window");

    return hClippingMenu;
}