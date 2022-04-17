#ifndef POINT_H
#define POINT_H

#include<array>
using namespace std;

#include "constants.h"

class Point
{
public:
    Point();
    double x;
    double y;
    bool isValid;
};

class Points
{
public:
    Points();

    void setPoint(int i, Point point);
    double xAt(int i);
    double yAt(int i);
    bool validAt(int i);

private:
    array<Point, LINE_POINTS> m_points;
};

#endif // POINT_H
