#include "Ellipses.h"
#include "Common.h"
#include <math.h>
#include <algorithm>

void ellipseDirect(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int A = getLineLen(points[0], points[1]);
    int B = getLineLen(points[0], points[2]);

    int x = 0;
	double y = B;
	while (x*B*B <= y*A*A)
	{
		draw4Points(hdc, points[0], x, roundNum(y), color);
		x++;
		y = B * sqrt(1.0 - (double)(x*x)/(A*A));
	}

	double x1 = A;
	int y1 = 0;
	while (x1*B*B >= y1*A*A)
	{
		draw4Points(hdc, points[0], roundNum(x1), y1, color);
		y1++;
		x1 = A * sqrt(1.0 - (double)(y1*y1)/(B*B));
	}
}

void ellipsePolar(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int A = getLineLen(points[0], points[1]);
    int B = getLineLen(points[0], points[2]);

    double x = A;
	double y = 0;
	double theta = 0;


	while (x >= y)
	{
	    draw4Points(hdc, points[0], roundNum(x), roundNum(y), color);
 	    theta += (1.0/std::max(A,B));
		x = A*cos(theta);
        y = B*sin(theta);
	}

	x=0;
	y=B;
	theta=90;

	while (x <= y)
	{
	    draw4Points(hdc, points[0], roundNum(x), roundNum(y), color);
	    theta -= (1.0/std::max(A,B));
		x = A*cos(theta);
        y = B*sin(theta);
	}
}

void ellipseMidpoint(HDC hdc, Point* points, int pointsNum, COLORREF color){
    int A = getLineLen(points[0], points[1]);
    int B = getLineLen(points[0], points[2]);

    int x = 0;
    int y = B;
    while(x*B*B <= y*A*A){
        draw4Points(hdc, points[0], x, y, color);

        double d = ((x+1)*(x+1))/(double)(A*A) + ((y-0.5)*(y-0.5))/(double)(B*B) -1;

        x++;
        if(d >= 0){
            y--;
        }
    }

    x = A;
    y = 0;
    while(x*B*B >= y*A*A){
        draw4Points(hdc, points[0], x, y, color);
        
        double d = ((x-0.5)*(x-0.5))/(double)(A*A) + ((y-1)*(y-1))/(double)(B*B) -1;

        y++;
        if(d >= 0){
            x--;
        }
    }
}

