#ifndef ICURRENTPOINT_H
#define ICURRENTPOINT_H

class CurrentPoint;


class ICurrentPoint
{
public:
    virtual void addCurrentPoint(CurrentPoint *currentPoint) = 0;
    virtual void newCurrentPoint(double x, double y) = 0;
};

#endif // ICURRENTPOINT_H
