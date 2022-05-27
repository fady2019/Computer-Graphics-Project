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
#include "Clipping.h"

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


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static System sys;
    static HDC hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
        {
            sys.shaper = 0;
            sys.mode = (MenuIDs)wParam;
            sys.count = 0;
            cout<<"Current Mode Number: "<<sys.mode<<endl;
            switch(wParam)
            {
                case CLEAR_MENU:{break;}
                case SAVE_MENU:{break;}
                case LOAD_MENU:{break;}
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
                case FILLING_CIR_WITH_LINES_MENU: {break;}
                case FILLING_CIR_WITH_CIRS_MENU: {break;}
                case FILLING_SQUARE_WITH_HERMIT_MENU: {break;}
                case FILLING_REC_WITH_BEZIER_MENU: {break;}
                case FILLING_CONVEX_MENU: {break;}
                case FILLING_NON_CONVEX_MENU: {break;}
                case FILLING_RECUR_FF_MENU: {break;}
                case FILLING_NON_RECUR_FF_MENU: {break;}
                /// Clipping Menu
                case CLIPPING_REC_WIN_POINT_MENU: {break;}
                case CLIPPING_REC_WIN_LINE_MENU: {break;}
                case CLIPPING_REC_WIN_POL_MENU: {break;}
                case CLIPPING_SQUARE_WIN_POINT_MENU: {sys.maxCount=INT_MAX; sys.shaper=&clippingPointWithSquareWindow; break;}
                case CLIPPING_SQUARE_WIN_LINE_MENU: {sys.maxCount=INT_MAX; sys.shaper=&clippingLineWithSquareWindow; break;}
                case CLIPPING_CIR_WIN_POINT_MENU: {break;}
                case CLIPPING_CIR_WIN_LINE_MENU: {break;}
            }
            break;
        }

        case WM_LBUTTONDOWN:{
            sys.points[sys.count++] = Point(LOWORD(lParam), HIWORD(lParam));
            SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), sys.color);
            if(sys.count == sys.maxCount){
                sys.shaper(hdc, sys.points, sys.count, sys.color);
                sys.count = 0;
            }

            break;
        }
        case WM_RBUTTONDOWN:{
            if(sys.shaper){
                sys.shaper(hdc, sys.points, sys.count, sys.color);
                sys.count = 0;
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
