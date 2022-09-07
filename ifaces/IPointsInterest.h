#ifndef IPOINTSINTEREST_H
#define IPOINTSINTEREST_H


class QString;
class PointsInterest;

class IPointsInterest
{
public:
    virtual void addPointsInterest(PointsInterest *pointInterest) = 0;
    virtual void interestingPointsfinished() = 0;
    virtual void updateLabel(QString text) = 0;
};

#endif // IPOINTINTEREST_H
