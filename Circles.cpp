#include "Circles.h"
#include "Common.h"
#include <cmath>

void circleDirect(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int R = getLineLen(points[0], points[1]);
    int R2 = R*R;

    int x = 0;
    int y = R;

    while (x <= y)
	{
        draw8Points(hdc, points[0], x, roundNum(y), color);
		x++;
		y = sqrt((double)R2 - x*x);
	}
}

void circlePolar(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int R = getLineLen(points[0], points[1]);
    double x = R;
	double y = 0;
	double theta = 0;

	while (x >= y)
	{
        draw8Points(hdc, points[0], roundNum(x), roundNum(y), color);
	    theta += (1.0/R);
		x = R*cos(theta);
        y = R*sin(theta);
	}
}

void circleIterativePolar(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int R = getLineLen(points[0], points[1]);
    double x = R;
	double y = 0;
	double dtheta = 1.0/R;
	double sdth = sin(dtheta);
	double cdth = cos(dtheta);

	while (x >= y)
	{
		draw8Points(hdc, points[0], roundNum(x), roundNum(y), color);
		double newX = x*cdth - y*sdth;
        y = y*cdth + x*sdth;
        x = newX;
	}
}

void circleMidpoint(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int R = getLineLen(points[0], points[1]);
    int R2 = R*R;
    int x = 0;
    int y = R;

    while(x <= y){
        draw8Points(hdc, points[0], x, y, color);

        double d = pow(x+1, 2) + pow(y-0.5, 2) - (R2);

        x++;

        if(d > 0){
            y--;
        }
    }
}

void circleModifiedMidpoint(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int R = getLineLen(points[0], points[1]);
    int x = 0;
    int y = R;
    float d = 1.0 - R;
    float d1 = 3;
    float d2 = 5 - 2*R;

    while(x <= y){
        draw8Points(hdc, points[0], x, y, color);

        d1 += 2;
        x++;

        if(d < 0){
            d += d1;
            d2 += 2;
        }else{
            d += d2;
            d2 += 4;
            y--;
        }
    }
}

