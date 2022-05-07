#ifndef FUNCTIONZOOMER_H
#define FUNCTIONZOOMER_H

#include "requestHandler.h"

class FunctionModel;

class FunctionZoomer : public RequestReceiver
{
public:
    FunctionZoomer(FunctionModel &model);
    virtual ~FunctionZoomer();
    void accept(Request *request);

private:
    RequestHandler *requestHandler;
    CalculateRequest *calculateRequest;
    NewInputValuesRequest *newInputValuesRequest;
    FunctionModel &m_model;
    void zoom(double delta);
    void performZoom(double factor);
    void newInputValues(double minX, double maxX, double minY, double maxY);
};

#endif // FUNCTIONZOOMER_H
