#ifndef POINT_H
#define POINT_H

#include<array>
using namespace std;

#include <QObject>
#include "utils/constants.h"

class Point
{
public:
    Point();
    double x;
    double y;
    bool isValid;
};

class Points : public QObject
{        
    Q_OBJECT
public:
    Points();

    void setPoint(int i, Point point);
    double xAt(int i) const;
    double yAt(int i) const;
    bool validAt(int i) const;

private:
    array<Point, LINE_POINTS> m_points;
};

#endif // POINT_H
