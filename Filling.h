#ifndef FILLING_H_INCLUDED
#define FILLING_H_INCLUDED

#include <iostream>
#include <windows.h>
#include "Common.h"

#define EDGE_TABLE_SIZE 800

using namespace std;

struct Edge {
    int xLeft=INT_MAX;
    int xRight=INT_MIN;

    void print(){
        cout<<"Left = "<<this->xLeft<<" Right = "<<this->xRight<<endl;
    }
};

struct EdgeRecord{
    double x;
    double yMax;
    double mInv;

    EdgeRecord(double x=0, double yMax=0, double mInv=0){
        this->x = x;
        this->yMax = yMax;
        this->mInv = mInv;
    }

    bool operator<( const EdgeRecord& edge) const { 
        return this->x < edge.x;
    }

    void print(){
        cout<<"<"<<x<<", "<<yMax<<", "<<mInv<<">";
    }
};

void recursiveFloodFill(HDC, Point*, int, COLORREF);
void nonRecursiveFloodFill(HDC, Point*, int, COLORREF);

void fillingQuarter1ByLines(HDC, Point*, int, COLORREF);
void fillingQuarter2ByLines(HDC, Point*, int, COLORREF);
void fillingQuarter3ByLines(HDC, Point*, int, COLORREF);
void fillingQuarter4ByLines(HDC, Point*, int, COLORREF);

void fillingQuarter1ByCircles(HDC, Point*, int, COLORREF);
void fillingQuarter2ByCircles(HDC, Point*, int, COLORREF);
void fillingQuarter3ByCircles(HDC, Point*, int, COLORREF);
void fillingQuarter4ByCircles(HDC, Point*, int, COLORREF);

void fillingPolygonConvex(HDC, Point*, int, COLORREF);
void fillingPolygonNonConvex(HDC, Point*, int, COLORREF);

#endif
