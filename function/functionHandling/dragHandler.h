#ifndef DRAGHANDLER_H
#define DRAGHANDLER_H

#include "requests.h"

class FunctionModel;

class DragHandler : public RequestReceiver
{
public:
    DragHandler(FunctionModel &model);
    virtual ~DragHandler();

    void accept(Request *request) override;

private:
    FunctionModel &m_model;
    int m_dragX;
    int m_dragY;

    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;

    RequestHandler *requestHandler;
    NewInputValuesRequest *newInputValuesRequest;
    CalculateRequest *calculateRequest;

    void startDrag(int x, int y);
    void drag(int diffX, int diffY, int width, int height);

    void sendCalculateRequest(double minX, double maxX, double minY, double maxY);
    void sendNewInputValuesRequest(double minX, double maxX, double minY, double maxY);
};

#endif // DRAGHANDLER_H
