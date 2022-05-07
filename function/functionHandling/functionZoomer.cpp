#include "functionZoomer.h"
#include "../functionModel.h"

#include <QDebug>

FunctionZoomer::FunctionZoomer(FunctionModel &model) : m_model(model)
{
    calculateRequest = nullptr;
    newInputValuesRequest = nullptr;
    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_zoom);
}

FunctionZoomer::~FunctionZoomer()
{
    if (newInputValuesRequest != nullptr)
        delete newInputValuesRequest;
    if (calculateRequest != nullptr)
        delete calculateRequest;
}

void FunctionZoomer::accept(Request *request)
{
    if (m_log)
        qDebug() << "FunctionZoomer used id: " << request->id << " type: " << request->description;
    if (request->type == request_zoom)
        zoom(static_cast<ZoomRequest*>(request)->delta);
}

void FunctionZoomer::zoom(double delta)
{
    //    if (!model.validExpression())
    //        return;

    double factor;
    if (delta < 0)
        factor = 1.1;
    else
        factor = 0.9;

    performZoom(factor);
}

void FunctionZoomer::performZoom(double factor)
{
    double minX = m_model.minX();
    double maxX = m_model.maxX();
    double minY = m_model.minY();
    double maxY = m_model.maxY();

    double newMinX, newMaxX, newMinY, newMaxY;

    double distanceX = maxX - minX;
    double centerX = (maxX + minX) / 2;

    double distanceY = maxY - minY;
    double centerY = (maxY + minY) / 2;

    distanceX = distanceX * factor;
    distanceY = distanceY * factor;

    if ( ((abs(distanceX) > 100000) || (abs(distanceY) > 100000)) &&
         (factor > 1))
        return;

    if ( ((abs(distanceX) < 0.0001) || (abs(distanceY) < 0.0001)) &&
         (factor < 1))
        return;


    //newMinX, newMaxX, newMinY, newMaxY are the new values

    newMinX = centerX - distanceX / 2;
    newMaxX = centerX + distanceX / 2;
    newMinY = centerY - distanceY / 2;
    newMaxY = centerY + distanceY / 2;


    //    //The level of precision in rounding depends on the distance between the values
    double distance = newMaxX - newMinX;
    double power = -floor(log10(distance)) + 2;

    //    //variable precision holds the level of precision
    double precision = pow(10, power);

    if (power > 0) {
        minX = round(newMinX * precision) / precision;
        maxX = round(newMaxX * precision) / precision;
    }
    else {
        minX = round(newMinX);
        maxX = round(newMaxX);
    }

    distance = newMaxY - newMinY;
    power = -floor(log10(distance)) + 2;
    precision = pow(10, power);
    if (power > 0) {
        minY = round(newMinY * precision) / precision;
        maxY = round(newMaxY * precision) / precision;
    }
    else {
        minY = round(newMinY);
        maxY = round(newMaxY);
    }

    //    //We calculate with the new values, but we need to round them before displaying them
    //    //if we round the values before zooming, zoom will not be smooth
    if (calculateRequest == nullptr)
        calculateRequest = new CalculateRequest;
    calculateRequest->sender = "FunctionZoomer";
    calculateRequest->expression = m_model.expression();
    calculateRequest->minX = QString::number(newMinX);
    calculateRequest->maxX = QString::number(newMaxX);
    calculateRequest->minY = QString::number(newMinY);
    calculateRequest->maxY = QString::number(newMaxY);

    requestHandler->handleRequest(calculateRequest);

    if (newInputValuesRequest == nullptr)
        newInputValuesRequest = new NewInputValuesRequest();
    newInputValuesRequest->sender = "FunctionZoomer";
    newInputValuesRequest->minX = minX;
    newInputValuesRequest->maxX = maxX;
    newInputValuesRequest->minY = minY;
    newInputValuesRequest->maxY = maxY;

    requestHandler->handleRequest(newInputValuesRequest);
}
