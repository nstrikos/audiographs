#include "pinchHandler.h"

#include "../functionModel.h"

PinchHandler::PinchHandler(QObject *parent) : QObject(parent)
{
    calculateRequest = nullptr;
    newInputValuesRequest = nullptr;
    requestHandler = &RequestHandler::getInstance();
}

PinchHandler::~PinchHandler()
{
    if (newInputValuesRequest != nullptr)
        delete newInputValuesRequest;
    if (calculateRequest != nullptr)
        delete calculateRequest;
}

void PinchHandler::startPinch(FunctionModel &model)
{
    if (!model.validExpression())
        return;

    m_minX = model.minX();
    m_maxX = model.maxX();
    m_minY = model.minY();
    m_maxY = model.maxY();
}

void PinchHandler::pinch(FunctionModel &model, double scale)
{
    if (!model.validExpression())
        return;

    scale = 1 / scale;

    double distanceX = m_maxX - m_minX;
    double centerX = (m_maxX + m_minX) / 2;

    int power = -floor(log10(distanceX)) + 2;
    double ten = pow(10, power);

    double distanceY = m_maxY - m_minY;
    double centerY = (m_maxY + m_minY) / 2;


    distanceX = distanceX * scale;
    distanceY = distanceY * scale;

    if ( ((abs(distanceX) > 100000) || (abs(distanceY) > 100000)) &&
         (scale > 1))
        return;

    if ( ((abs(distanceX) < 0.0001) || (abs(distanceY) < 0.0001)) &&
         (scale < 1))
        return;

    double minX = centerX - distanceX / 2;
    double maxX = centerX + distanceX / 2;
    double minY = centerY - distanceY / 2;
    double maxY = centerY + distanceY / 2;

    if (calculateRequest == nullptr)
        calculateRequest = new CalculateRequest;
    calculateRequest->expression = model.expression();
    calculateRequest->minX = QString::number(minX);
    calculateRequest->maxX = QString::number(maxX);
    calculateRequest->minY = QString::number(minY);
    calculateRequest->maxY = QString::number(maxY);

    requestHandler->handleRequest(calculateRequest);

    minX = round(minX * ten) / ten;
    maxX = round(maxX * ten) / ten;
    minY = round(minY * ten) / ten;
    maxY = round(maxY * ten) / ten;

    if (newInputValuesRequest == nullptr)
        newInputValuesRequest = new NewInputValuesRequest();
    newInputValuesRequest->minX = minX;
    newInputValuesRequest->maxX = maxX;
    newInputValuesRequest->minY = minY;
    newInputValuesRequest->maxY = maxY;

    requestHandler->handleRequest(newInputValuesRequest);
}
