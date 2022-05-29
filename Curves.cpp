#include "Curves.h"
#include "Common.h"

void drawHermitCurve(HDC hdc, Point p1, Point t1, Point p2, Point t2, COLORREF color){
    double alpha0 = p1.x;
    double alpha1 = t1.x;
    double alpha2 = (-3*p1.x) - (2*t1.x) + (3*p2.x) - (t2.x);
    double alpha3 = (2*p1.x) + (t1.x) - (2*p2.x) + (t2.x);

    double beta0 = p1.y;
    double beta1 = t1.y;
    double beta2 = -(3*p1.y) - (2*t1.y) + (3*p2.y) - (t2.y);
    double beta3 = (2*p1.y) + (t1.y) - (2*p2.y) + (t2.y);

    for(double t=0; t<=1; t+=0.001)
    {
        double x = alpha0 + (alpha1*t) + (alpha2*t*t) + (alpha3*t*t*t);
        double y = beta0 + (beta1*t) + (beta2*t*t) + (beta3*t*t*t);
        SetPixel(hdc, roundNum(x), roundNum(y), color);
    }
}

void hermitCurve(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Point T1(3 * (points[1].x - points[0].x), 3 * (points[1].y - points[0].y));
    Point T2(3 * (points[3].x - points[2].x), 3 * (points[3].y - points[2].y));

    drawHermitCurve(hdc, points[0], T1, points[3], T2, color);
}

void bezierCurve(HDC hdc, Point* points, int pointsNum, COLORREF color){
    Point p1 = points[0];
    Point p2 = points[1];
    Point p3 = points[2];
    Point p4 = points[3];

    double alpha0 = p1.x;
    double alpha1 = 3*(p2.x - p1.x);
    double alpha2 = (3*p1.x) - (6*p2.x) + (3*p3.x);
    double alpha3 = (-p1.x) + (3*p2.x) - (3*p3.x) + (p4.x);

    double beta0 = p1.y;
    double beta1 = 3*(p2.y - p1.y);
    double beta2 = (3*p1.y) - (6*p2.y) + (3*p3.y);
    double beta3 = (-p1.y) + (3*p2.y) - (3*p3.y) + (p4.y);

    for(double t=0; t<=1; t+=0.001){
        double x = alpha0 + (alpha1*t) + (alpha2*t*t) + (alpha3*t*t*t);
        double y = beta0 + (beta1*t) + (beta2*t*t) + (beta3*t*t*t);
        SetPixel(hdc, x, y, color);
    }
}

void cardinalSplineCurve(HDC hdc, Point* points, int pointsNum, COLORREF color){
    float c = 1.0;

    Point T[pointsNum];

    T[0] = (points[1] - points[0])*(c/2);
    for(int i=1; i<pointsNum-1; i++)
    {
        T[i] = (points[i+1] - points[i-1])*(c/2);
    }
    T[pointsNum-1] = (points[pointsNum-1] - points[pointsNum-2])*(c/2);

    for(int i=0; i<pointsNum-1; i++)
    {
        drawHermitCurve(hdc, points[i], T[i], points[i+1], T[i+1], color);
    }
}
