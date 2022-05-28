#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <iostream>
#include <tchar.h>
#include <windows.h>

#include "Menus.h"
#include "Common.h"
#include "Lines.h"
#include "Circles.h"
#include "Ellipses.h"
#include "Curves.h"
#include "Filling.h"
#include "Clipping.h"
#include "Files.h"
#include "ShapesWindow.h"

using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

void createOwnMenu(HWND);

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_HAND); /**Change cursor to hand**/
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); /**Change bg to white**/

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("The Shaper"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


System<void> sys;
System<Window*> windowSys;
Window* window;

void callShaper(HDC hdc){
    Point* points = 0;
    int pointsSize = 0;

    if(window != 0){
        points = mergeTwoArray(window->points, window->pointsNum, sys.points, sys.count);
        pointsSize = window->pointsNum + sys.count;
    }else{
        points = sys.points;
        pointsSize = sys.count;
    }

    sys.shaper(hdc, points, pointsSize, sys.color);
    sys.count = 0;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
        {
            switch(wParam)
            {
                /// File Menu
                case CLEAR_MENU:{clearScreen(hwnd); return 0;}
                case SAVE_MENU:{return 0;}
                case LOAD_MENU:{return 0;}
                /// Color Menu
                case COLOR_BLACK:{windowSys.color = sys.color = BLACK_COLOR; return 0;}
                case COLOR_RED:{windowSys.color = sys.color = RED_COLOR; return 0;}
                case COLOR_YELLOW:{windowSys.color = sys.color = YELLOW_COLOR; return 0;}
                case COLOR_ORANGE:{windowSys.color = sys.color = ORANGE_COLOR; return 0;}
                case COLOR_GREEN:{windowSys.color = sys.color = GREEN_COLOR; return 0;}
                case COLOR_BLUE:{windowSys.color = sys.color = BLUE_COLOR; return 0;}
                case COLOR_PURPLE:{windowSys.color = sys.color = PURPLE_COLOR; return 0;}
                case COLOR_TAEL:{windowSys.color = sys.color = TAEL_COLOR; return 0;}
                case COLOR_GRAY:{windowSys.color = sys.color = GRAY_COLOR; return 0;}
                case COLOR_CYAN:{windowSys.color = sys.color = CYAN_COLOR; return 0;}
                case COLOR_GOLD:{windowSys.color = sys.color = GOLD_COLOR; return 0;}
                case COLOR_SILVER:{windowSys.color = sys.color = SILVER_COLOR; return 0;}
            }

            window = 0;

            windowSys.shaper=0;
            windowSys.count=0;
            windowSys.mode = (MenuIDs)wParam;

            sys.shaper = 0;
            sys.count = 0;
            sys.mode = (MenuIDs)wParam;

            cout<<"Current Mode Number: "<<sys.mode<<endl;
            switch(wParam)
            {
                /// Line Menu
                case LINE_DDA_MENU:{sys.maxCount=2; sys.shaper=&lineDDA; break;}
                case LINE_MID_MENU:{sys.maxCount=2; sys.shaper=&lineMidpoint; break;}
                case LINE_PARA_MENU:{sys.maxCount=2; sys.shaper=&lineParametric; break;}
                /// Circle Menu
                case CIR_DIRECT_MENU: {sys.maxCount=2; sys.shaper=&circleDirect; break;}
                case CIR_POLAR_MENU: {sys.maxCount=2; sys.shaper=&circlePolar; break;}
                case CIR_ITER_POLAR_MENU: {sys.maxCount=2; sys.shaper=&circleIterativePolar; break;}
                case CIR_MID_MENU: {sys.maxCount=2; sys.shaper=&circleMidpoint; break;}
                case CIR_MOD_MID_MENU: {sys.maxCount=2; sys.shaper=&circleModifiedMidpoint; break;}
                /// Ellipse Menu
                case ELL_DIRECT_MENU: {sys.maxCount=3; sys.shaper=&ellipseDirect; break;}
                case ELL_POLAR_MENU: {sys.maxCount=3; sys.shaper=&ellipsePolar; break;}
                case ELL_MID_MENU: {sys.maxCount=3; sys.shaper=&ellipseMidpoint; break;}
                /// Curve Menu
                case CURVE_HERMIT_MENU: {sys.maxCount=4; sys.shaper=&hermitCurve; break;}
                case CURVE_BEZIER_MENU: {sys.maxCount=4; sys.shaper=&bezierCurve; break;}
                case CURVE_CAR_SPL_MENU: {sys.maxCount=INT_MAX; sys.shaper=&cardinalSplineCurve; break;}
                /// Filling Menu
                case FILLING_CIR_WITH_LINES_Q1_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter1ByLines; break;}
                case FILLING_CIR_WITH_LINES_Q2_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter2ByLines; break;}
                case FILLING_CIR_WITH_LINES_Q3_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter3ByLines; break;}
                case FILLING_CIR_WITH_LINES_Q4_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter4ByLines; break;}
                case FILLING_CIR_WITH_CIRS_Q1_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter1ByCircles; break;}
                case FILLING_CIR_WITH_CIRS_Q2_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter2ByCircles; break;}
                case FILLING_CIR_WITH_CIRS_Q3_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter3ByCircles; break;}
                case FILLING_CIR_WITH_CIRS_Q4_MENU: {sys.maxCount=2; sys.shaper=&fillingQuarter4ByCircles; break;}
                case FILLING_SQUARE_WITH_HERMIT_MENU: {sys.maxCount=2; sys.shaper=&fillingSquareWithHermitCurve; break;}
                case FILLING_REC_WITH_BEZIER_MENU: {sys.maxCount=3; sys.shaper=&fillingRectangleWithBezierCurve; break;}
                case FILLING_CONVEX_MENU: {sys.maxCount=INT_MAX; sys.shaper=&fillingPolygonConvex; break;}
                case FILLING_NON_CONVEX_MENU: {sys.maxCount=INT_MAX; sys.shaper=&fillingPolygonNonConvex; break;}
                case FILLING_RECUR_FF_MENU: {sys.maxCount=2; sys.shaper=&recursiveFloodFill; break;}
                case FILLING_NON_RECUR_FF_MENU: {sys.maxCount=2; sys.shaper=&nonRecursiveFloodFill; break;}
                /// Clipping Menu
                case CLIPPING_REC_WIN_POINT_MENU: {
                    windowSys.maxCount=3; windowSys.shaper=getRectangleWindow;
                    sys.maxCount=1; sys.shaper=&clippingPointWithSquareOrRectangleWindow;
                    break;
                }
                case CLIPPING_REC_WIN_LINE_MENU: {
                    windowSys.maxCount=3; windowSys.shaper=getRectangleWindow;
                    sys.maxCount=2; sys.shaper=&clippingLineWithSquareOrRectangleWindow;
                    break;
                }
                case CLIPPING_REC_WIN_POL_MENU: {
                    windowSys.maxCount=3; windowSys.shaper=getRectangleWindow;
                    sys.maxCount=INT_MAX; sys.shaper=&clippingPolygonWithRectangleWindow;
                    break;
                }
                case CLIPPING_SQUARE_WIN_POINT_MENU: {
                    windowSys.maxCount=2; windowSys.shaper=getSquareWindow;
                    sys.maxCount=1; sys.shaper=&clippingPointWithSquareOrRectangleWindow;
                    break;
                }
                case CLIPPING_SQUARE_WIN_LINE_MENU: {
                    windowSys.maxCount=2; windowSys.shaper=getSquareWindow;
                    sys.maxCount=2; sys.shaper=&clippingLineWithSquareOrRectangleWindow;
                    break;
                }
                case CLIPPING_CIR_WIN_POINT_MENU: {
                    windowSys.maxCount=2; windowSys.shaper=getCircleWindow;
                    sys.maxCount=1; sys.shaper=&clippingPointWithCircleWindow;
                    break;
                }
                case CLIPPING_CIR_WIN_LINE_MENU: {
                    windowSys.maxCount=2; windowSys.shaper=getCircleWindow;
                    sys.maxCount=2; sys.shaper=&clippingLineWithCircleWindow;
                    break;
                }
            }
            break;
        }

        case WM_LBUTTONDOWN:{
            int x=LOWORD(lParam);
            int y=HIWORD(lParam);

            Point enteredPoint = Point(x,y);
            enteredPoint.print();

            SetPixel(hdc, x, y, sys.color);

            if(windowSys.shaper != 0){
                windowSys.points[windowSys.count++] = enteredPoint;
                if(windowSys.count == windowSys.maxCount){
                    window = windowSys.shaper(hdc, windowSys.points, windowSys.count, windowSys.color);
                    windowSys.shaper = 0;
                }

                break;
            }

            sys.points[sys.count++] = enteredPoint;
            if(sys.count == sys.maxCount){
                callShaper(hdc);
            }

            break;
        }
        case WM_RBUTTONDOWN:{
            if(sys.shaper){
                callShaper(hdc);
            }

            break;
        }
        case WM_CREATE:
            createOwnMenu(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
