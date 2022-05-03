#ifndef FUNCTIONDESCRIPTION_H
#define FUNCTIONDESCRIPTION_H

#include <QString>
#include <QVector>
#include "../functionModel.h"

class InterestingPoint
{
public:
    double x;
    double y;
    QString label;
};

class FunctionDescription
{
public:
    FunctionDescription(FunctionModel &model);
    QVector<InterestingPoint> points(int derivativeMode);

private:
    QVector<InterestingPoint> m_points;
    FunctionModel &m_model;
};

#endif // FUNCTIONDESCRIPTION_H
