#ifndef IFUNCTIONMODEL_H
#define IFUNCTIONMODEL_H

#include "function/point.h"

class FunctionModel;

class IFunctionModel
{
public:
    virtual void addModel(FunctionModel *model) = 0;
    virtual void newGraph(Points *points, double minX, double maxX, double minY, double maxY) = 0;
    virtual void error(QString) = 0;
    virtual void updateDerivative(Points *points, double minX, double maxX, double minY, double maxY) = 0;
};

#endif // IFUNCTIONMODEL_H
