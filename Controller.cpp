#include <iostream>

#include "Controller.h"
#include "Common.h"
#include "Menus.h"

#include "Lines.h"
#include "Circles.h"
#include "Ellipses.h"
#include "Curves.h"
#include "Filling.h"
#include "Clipping.h"
#include "ShapesWindow.h"

using namespace std;

void setShaper(MenuIDs mode, System<void>& sys, System<Window*>& windowSys){
    cout<<"Current Mode Number: "<<mode<<endl;
    
    switch(mode)
    {
        /// Line Menu
        case LINE_DDA_MENU:{
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&lineDDA;
            break;
        }
        case LINE_MID_MENU:{
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&lineMidpoint;
            break;
        }
        case LINE_PARA_MENU:{
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&lineParametric;
            break;
        }
        /// Circle Menu
        case CIR_DIRECT_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&circleDirect;
            break;
        }
        case CIR_POLAR_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&circlePolar;
            break;
        }
        case CIR_ITER_POLAR_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&circleIterativePolar;
            break;
        }
        case CIR_MID_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&circleMidpoint;
            break;
        }
        case CIR_MOD_MID_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&circleModifiedMidpoint;
            break;
        }
        /// Ellipse Menu
        case ELL_DIRECT_MENU: {
            sys.minCount = sys.maxCount = 3;
            sys.shaper=&ellipseDirect;
            break;
        }
        case ELL_POLAR_MENU: {
            sys.minCount = sys.maxCount = 3;
            sys.shaper=&ellipsePolar;
            break;
        }
        case ELL_MID_MENU: {
            sys.minCount = sys.maxCount = 3;
            sys.shaper=&ellipseMidpoint;
            break;
        }
        /// Curve Menu
        case CURVE_HERMIT_MENU: {
            sys.minCount = sys.maxCount = 4;
            sys.shaper=&hermitCurve;
            break;
        }
        case CURVE_BEZIER_MENU: {
            sys.minCount = sys.maxCount = 4;
            sys.shaper=&bezierCurve;
            break;
        }
        case CURVE_CAR_SPL_MENU: {
            sys.minCount = 2;
            sys.maxCount=INT_MAX;
            sys.shaper=&cardinalSplineCurve; break;
        }
        /// Filling Menu
        case FILLING_CIR_WITH_LINES_Q1_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter1ByLines;
            break;
        }
        case FILLING_CIR_WITH_LINES_Q2_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter2ByLines;
            break;
        }
        case FILLING_CIR_WITH_LINES_Q3_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter3ByLines;
            break;
        }
        case FILLING_CIR_WITH_LINES_Q4_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter4ByLines;
            break;
        }
        case FILLING_CIR_WITH_CIRS_Q1_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter1ByCircles;
            break;
        }
        case FILLING_CIR_WITH_CIRS_Q2_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter2ByCircles;
            break;
        }
        case FILLING_CIR_WITH_CIRS_Q3_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter3ByCircles;
            break;
        }
        case FILLING_CIR_WITH_CIRS_Q4_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingQuarter4ByCircles;
            break;
        }
        case FILLING_SQUARE_WITH_HERMIT_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&fillingSquareWithHermitCurve;
            break;
        }
        case FILLING_REC_WITH_BEZIER_MENU: {
            sys.minCount = sys.maxCount = 3;
            sys.shaper=&fillingRectangleWithBezierCurve;
            break;
        }
        case FILLING_CONVEX_MENU: {
            sys.minCount = 3;
            sys.maxCount = INT_MAX;
            sys.shaper=&fillingPolygonConvex;
            break;
        }
        case FILLING_NON_CONVEX_MENU: {
            sys.minCount = 3;
            sys.maxCount = INT_MAX;
            sys.shaper=&fillingPolygonNonConvex;
            break;
        }
        case FILLING_RECUR_FF_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&recursiveFloodFill;
            break;
        }
        case FILLING_NON_RECUR_FF_MENU: {
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&nonRecursiveFloodFill;
            break;
        }
        /// Clipping Menu
        case CLIPPING_REC_WIN_POINT_MENU: {
            windowSys.minCount = windowSys.maxCount = 3;
            windowSys.shaper=&getRectangleWindow;
            sys.minCount = sys.maxCount = 1;
            sys.shaper=&clippingPointWithSquareOrRectangleWindow;
            break;
        }
        case CLIPPING_REC_WIN_LINE_MENU: {
            windowSys.minCount = windowSys.maxCount=3;
            windowSys.shaper=&getRectangleWindow;
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&clippingLineWithSquareOrRectangleWindow;
            break;
        }
        case CLIPPING_REC_WIN_POL_MENU: {
            windowSys.minCount = windowSys.maxCount = 3;
            windowSys.shaper=&getRectangleWindow;
            sys.minCount = 3;
            sys.maxCount = INT_MAX;
            sys.shaper=&clippingPolygonWithRectangleWindow;
            break;
        }
        case CLIPPING_SQUARE_WIN_POINT_MENU: {
            windowSys.minCount = windowSys.maxCount = 2;
            windowSys.shaper=&getSquareWindow;
            sys.minCount = sys.maxCount = 1;
            sys.shaper=&clippingPointWithSquareOrRectangleWindow;
            break;
        }
        case CLIPPING_SQUARE_WIN_LINE_MENU: {
            windowSys.minCount = windowSys.maxCount = 2;
            windowSys.shaper=&getSquareWindow;
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&clippingLineWithSquareOrRectangleWindow;
            break;
        }
        case CLIPPING_CIR_WIN_POINT_MENU: {
            windowSys.minCount = windowSys.maxCount = 2;
            windowSys.shaper=&getCircleWindow;
            sys.minCount = sys.maxCount = 1;
            sys.shaper=&clippingPointWithCircleWindow;
            break;
        }
        case CLIPPING_CIR_WIN_LINE_MENU: {
            windowSys.minCount = windowSys.maxCount = 2;
            windowSys.shaper=&getCircleWindow;
            sys.minCount = sys.maxCount = 2;
            sys.shaper=&clippingLineWithCircleWindow;
            break;
        }
    }
}