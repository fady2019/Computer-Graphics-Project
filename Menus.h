#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include <windows.h>

enum MenuIDs {
    CLEAR_MENU,
    SAVE_MENU,
    LOAD_MENU,

    /// Color Menu IDs
    COLOR_BLACK,
    COLOR_RED,
    COLOR_YELLOW,
    COLOR_ORANGE,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_PURPLE,
    COLOR_TAEL,
    COLOR_GRAY,
    COLOR_CYAN,
    COLOR_GOLD,
    COLOR_SILVER,

    /// Line Menu IDs
    LINE_DDA_MENU,
    LINE_MID_MENU,
    LINE_PARA_MENU,
    /// Circle Menu IDs
    CIR_DIRECT_MENU,
    CIR_POLAR_MENU,
    CIR_ITER_POLAR_MENU,
    CIR_MID_MENU,
    CIR_MOD_MID_MENU,
    /// Ellipse Menu IDs
    ELL_DIRECT_MENU,
    ELL_POLAR_MENU,
    ELL_MID_MENU,
    /// Curve Menu IDs
    CURVE_HERMIT_MENU,
    CURVE_BEZIER_MENU,
    CURVE_CAR_SPL_MENU,
    /// Filling Menu IDs
    FILLING_CIR_WITH_LINES_MENU,
    FILLING_CIR_WITH_CIRS_MENU,
    FILLING_SQUARE_WITH_HERMIT_MENU,
    FILLING_REC_WITH_BEZIER_MENU,
    FILLING_CONVEX_MENU,
    FILLING_NON_CONVEX_MENU,
    FILLING_RECUR_FF_MENU,
    FILLING_NON_RECUR_FF_MENU,
    /// Clipping Menu IDs
    CLIPPING_REC_WIN_POINT_MENU,
    CLIPPING_REC_WIN_LINE_MENU,
    CLIPPING_REC_WIN_POL_MENU,
    CLIPPING_SQUARE_WIN_POINT_MENU,
    CLIPPING_SQUARE_WIN_LINE_MENU,
    CLIPPING_CIR_WIN_POINT_MENU,
    CLIPPING_CIR_WIN_LINE_MENU,


};

void createOwnMenu(HWND hwnd);
HMENU createFilePopupMenu();

/// color menu
HMENU createColorPopupMenu();
/// line menu
HMENU createLinePopupMenu();
/// circle menu
HMENU createCirclePopupMenu();
/// ellipse menu
HMENU createEllipsePopupMenu();
/// curve menu
HMENU createCurvePopupMenu();
/// filling Menu
HMENU createFillingPopupMenu();
/// clipping menu
HMENU createClippingPopupMenu();
HMENU createClippingRecWinPopupMenu();
HMENU createClippingSquareWinPopupMenu();
HMENU createClippingCirWinPopupMenu();


#endif // MENUS_H_INCLUDED

