#ifndef PINCHHANDLER_H
#define PINCHHANDLER_H

#include "requestHandler.h"

class FunctionModel;

class PinchHandler : public RequestReceiver
{
public:
    explicit PinchHandler(FunctionModel &model);
    virtual ~PinchHandler();
    void accept(Request *request);


private:
    RequestHandler *requestHandler;
    CalculateRequest *calculateRequest;
    NewInputValuesRequest *newInputValuesRequest;
    FunctionModel &m_model;
    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
    void startPinch();
    void pinch(double scale);
    void newInputValues(double minX, double maxX, double minY, double maxY);
};

#endif // PINCHHANDLER_H
