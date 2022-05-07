#include "pinchHandler.h"

#include "../functionModel.h"

#include <QDebug>

PinchHandler::PinchHandler(FunctionModel &model) : m_model(model)
{
    calculateRequest = nullptr;
    newInputValuesRequest = nullptr;
    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_start_pinch);
    requestHandler->add(this, request_pinch);
}

PinchHandler::~PinchHandler()
{
    if (newInputValuesRequest != nullptr)
        delete newInputValuesRequest;
    if (calculateRequest != nullptr)
        delete calculateRequest;
}

void PinchHandler::accept(Request *request)
{
    if (m_log)
        qDebug() << "PinchHandler used id: " << request->id << " type: " << request->description;
    switch(request->type) {
    case request_start_pinch : startPinch();
        break;
    case request_pinch : pinch(static_cast<PinchRequest*>(request)->scale);
        break;
    default:
        break;
    }
}

void PinchHandler::startPinch()
{
    if (!m_model.validExpression())
        return;

    m_minX = m_model.minX();
    m_maxX = m_model.maxX();
    m_minY = m_model.minY();
    m_maxY = m_model.maxY();
}

void PinchHandler::pinch(double scale)
{
    if (!m_model.validExpression())
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
    calculateRequest->expression = m_model.expression();
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
