#include "Lines.h"
#include <algorithm>
#include <cmath>

void lineDDA(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    Point p1 = points[0], p2 = points[1];
    int dx=p2.x - p1.x;
    int dy=p2.y-p1.y;

    SetPixel(hdc,p1.x,p1.y,color);

    if(abs(dx)>=abs(dy))
    {
        int x=p1.x;
        int xInc= dx>0? 1:-1;
        double y = p1.y;
        double yInc = (double)dy/dx*xInc;

        while(x!=p2.x)
        {
            x += xInc;
            y += yInc;
            SetPixel(hdc,x,roundNum(y),color);
        }
    }
    else
    {
        int y = p1.y;
        int yInc = dy>0? 1: -1;
        double x = p1.x;
        double xInc = (double)dx/dy*yInc;

        while(y!=p2.y)
        {
            x += xInc;
            y += yInc;
            SetPixel(hdc,roundNum(x),y,color);
        }
    }
}

void lineParametric(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    Point p1 = points[0];
    Point p2 = points[1];
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;

    for (double t = 0; t < 1; t += 0.001) {
        int x = p1.x + (dx * t);
        int y = p1.y + (dy * t);
        SetPixel(hdc, x, y, color);
    }
}

void lineMidpoint(HDC hdc, Point* points, int pointsNum, COLORREF color)
{
    Point startPoint = points[0], endPoint = points[1];
    int dx = endPoint.x - startPoint.x;
    int dy = endPoint.y - startPoint.y;

    int x, y, d, d1, d2;

    if(abs(dy) <= abs(dx)){ // if slope is less than or equal 1
        if(dx < 0){ // if x1 > x2
            swapTwoPoints(startPoint, endPoint);
			dy *= -1;
            dx *= -1;
        }

        int ySign = dy > 0 ? 1 : -1;

		d = dx - (2*ySign) *dy;
		d1 = 2 * (dx - (dy * ySign));
		d2 = (-2*ySign) * dy;

        x = startPoint.x;
        y = startPoint.y;

        while(x <= endPoint.x){
            SetPixel(hdc, x, y, color);

            if(d <= 0){
				d += d1;
				y += ySign;
			}else{
				d += d2;
			}

            x++;
        }
    }else{ // if slope is greater than 1
        if(dy < 0){ // if y1 > y2
            swapTwoPoints(startPoint, endPoint);
			dy *= -1;
            dx *= -1;
        }

		int xSign = dx > 0 ? 1 : -1;

		d = dy - (2*xSign) *dx;
		d1 = 2 * (dy - (dx * xSign));
		d2 = (-2*xSign) * dx;

        x = startPoint.x;
        y = startPoint.y;

        while(y <= endPoint.y){
            SetPixel(hdc, x, y, color);

            if(d <= 0){
				d += d1;
				x += xSign;
			}else{
				d += d2;
			}

            y++;
        }
    }
}
