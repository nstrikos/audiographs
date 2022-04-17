#ifndef FUNCTIONZOOMER_H
#define FUNCTIONZOOMER_H

#include <QObject>
#include "requests.h"

class FunctionModel;

class FunctionZoomer : public QObject
{
    Q_OBJECT
public:
    explicit FunctionZoomer(QObject *parent = nullptr);
    ~FunctionZoomer();
    void zoom(FunctionModel &model, double delta, int derivMode);

signals:
    void newInputValues(double minX, double maxX, double minY, double maxY);

private:
    void performZoom(FunctionModel &model, double factor, int derivMode);
    RequestHandler *requestHandler;
    CalculateRequest *calculateRequest;
    NewInputValuesRequest *newInputValuesRequest;
};

#endif // FUNCTIONZOOMER_H
