#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <tchar.h>
#include <windows.h>

#include "Menus.h"
#include "Common.h"
#include "ShapesWindow.h"
#include "Controller.h"

using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

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

HDC hdc;
System<void> sys;
System<Window*> windowSys;
Window* window;
vector<pair<int,System<void>>> systems;

void resetSys(){
    windowSys.shaper=0;
    windowSys.count=0;
    sys.shaper = 0;
    sys.count = 0;
}

void callShaper(bool saveSys=true){
    Point* points = 0;
    int windowPointsSize=0;
    int pointsSize = 0;
    int minExpectedPoints=0;

    if(windowSys.shaper != 0){
        minExpectedPoints = windowSys.minCount;
    }else{
        if(window != 0){
            points = mergeTwoArray(window->points, window->pointsNum, sys.points, sys.count);
            windowPointsSize = window->pointsNum;
        }else{
            points = sys.points;
        }

        pointsSize = sys.count;
        minExpectedPoints = sys.minCount;
    }

    if(pointsSize >= minExpectedPoints){
        if(saveSys){
            systems.push_back(make_pair(0, sys.copy()));
        }
        sys.shaper(hdc, points, pointsSize+windowPointsSize, sys.color);
        sys.count = 0;
    }else{
        cout<<"The Points You Entered Are Not Enough!"<<endl;
        cout<<"We Expected At Least "<<minExpectedPoints<<" Point(s)"<<endl;
    }
}

// --------------------------------------
// ---------- FILE FUNCTIONS ------------
// --------------------------------------
void clearScreen(HWND hwnd){
    InvalidateRect (hwnd, NULL, TRUE);
}

void writeOnFile(){
    ofstream MyFile("systems.txt");

    for(int i = 0 ; i < systems.size() ; i++)
    {
        MyFile << systems[i].first << " ";
        MyFile << systems[i].second.color << " ";  // color
        MyFile << systems[i].second.mode << " ";   // mode
        MyFile << systems[i].second.count << " ";  // count
        for(int j = 0 ; j < systems[i].second.count ; j++)
        {
            MyFile << systems[i].second.points[j].x << " " << systems[i].second.points[j].y << " ";
        }
        MyFile << "\n" ;
    }

    MyFile.close();
}

void readFromFile(){
    ifstream MyReadFile("systems.txt");

    int mode, type;

    while(MyReadFile >> type)
    {
        resetSys();

        if(type == 1)
        { // window sys
            MyReadFile >> windowSys.color;
            MyReadFile >> mode;
            windowSys.mode = (MenuIDs)mode;
            MyReadFile >> windowSys.count;

            for(int i = 0; i < windowSys.count ; i++)
            {
                MyReadFile >> windowSys.points[i].x ;
                MyReadFile >> windowSys.points[i].y ;
            }

            setShaper(windowSys.mode, sys, windowSys);

            window = windowSys.shaper(hdc, windowSys.points, windowSys.count, windowSys.color);

            systems.push_back(make_pair(type,windowSys.copy()));
        }
        else if(type == 0)
        { // shape sys
            MyReadFile >> sys.color;
            MyReadFile >> mode;
            sys.mode = (MenuIDs)mode;
            MyReadFile >> sys.count;

            for(int i = 0; i < sys.count ; i++)
            {
                MyReadFile >> sys.points[i].x ;
                MyReadFile >> sys.points[i].y ;
            }

            setShaper(sys.mode, sys, windowSys);

            if(windowSys.shaper == 0){
                window = 0;
            }else{
                windowSys.shaper = 0;
            }

            systems.push_back(make_pair(type, sys.copy()));

            callShaper(false);
        }
    }

    MyReadFile.close();
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
        {
            switch(wParam)
            {
                /// File Menu
                case CLEAR_MENU:{
                    clearScreen(hwnd);
                    systems.clear();
                    cout<<"Screen is Cleared Successfully!"<<endl;
                    return 0;
                }
                case SAVE_MENU:{
                    writeOnFile();
                    cout<<"Shapes is Saved Successfully!"<<endl;
                    return 0;
                }
                case LOAD_MENU:{
                    systems.clear();
                    readFromFile();
                    cout<<"Shapes is Loaded Successfully!"<<endl;
                    return 0;
                }
                /// Color Menu
                case COLOR_BLACK:{
                    windowSys.color = sys.color = BLACK_COLOR;
                    cout<<"Color is changed to Black"<<endl;
                    return 0;
                }
                case COLOR_RED:{
                    windowSys.color = sys.color = RED_COLOR;
                    cout<<"Color is changed to Red"<<endl;
                    return 0;
                }
                case COLOR_YELLOW:{
                    windowSys.color = sys.color = YELLOW_COLOR;
                    cout<<"Color is changed to Yellow"<<endl;
                    return 0;
                }
                case COLOR_ORANGE:{
                    windowSys.color = sys.color = ORANGE_COLOR;
                    cout<<"Color is changed to Orange"<<endl;
                    return 0;
                }
                case COLOR_GREEN:{
                    windowSys.color = sys.color = GREEN_COLOR;
                    cout<<"Color is changed to Green"<<endl;
                    return 0;
                }
                case COLOR_BLUE:{
                    windowSys.color = sys.color = BLUE_COLOR;
                    cout<<"Color is changed to Blue"<<endl;
                    return 0;
                }
                case COLOR_PURPLE:{
                    windowSys.color = sys.color = PURPLE_COLOR;
                    cout<<"Color is changed to Purple"<<endl;
                    return 0;
                }
                case COLOR_TAEL:{
                    windowSys.color = sys.color = TAEL_COLOR;
                    cout<<"Color is changed to Tael"<<endl;
                    return 0;
                }
                case COLOR_GRAY:{
                    windowSys.color = sys.color = GRAY_COLOR;
                    cout<<"Color is changed to Gray"<<endl;
                    return 0;
                }
                case COLOR_CYAN:{
                    windowSys.color = sys.color = CYAN_COLOR;
                    cout<<"Color is changed to Cyan"<<endl;
                    return 0;
                }
                case COLOR_GOLD:{
                    windowSys.color = sys.color = GOLD_COLOR;
                    cout<<"Color is changed to Gold"<<endl;
                    return 0;
                }
                case COLOR_SILVER:{
                    windowSys.color = sys.color = SILVER_COLOR;
                    cout<<"Color is changed to Silver"<<endl;
                    return 0;
                }
            }

            window = 0;
            resetSys();
            sys.mode =  windowSys.mode = (MenuIDs)wParam;
            setShaper((MenuIDs)wParam, sys, windowSys);

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
                    systems.push_back(make_pair(1,windowSys.copy()));
                    window = windowSys.shaper(hdc, windowSys.points, windowSys.count, windowSys.color);
                    windowSys.shaper = 0;
                }
                break;
            }

            sys.points[sys.count++] = enteredPoint;
            if(sys.count == sys.maxCount){
                callShaper();
            }
            break;
        }
        case WM_RBUTTONDOWN:{
            if(sys.shaper){
                callShaper();
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
