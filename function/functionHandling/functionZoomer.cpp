#include "functionZoomer.h"
#include "../functionModel.h"

FunctionZoomer::FunctionZoomer(QObject *parent) : QObject(parent)
{
    calculateRequest = nullptr;
    newInputValuesRequest = nullptr;
    requestHandler = &RequestHandler::getInstance();
}

FunctionZoomer::~FunctionZoomer()
{
    if (newInputValuesRequest != nullptr)
        delete newInputValuesRequest;
    if (calculateRequest != nullptr)
        delete calculateRequest;
}

void FunctionZoomer::zoom(FunctionModel &model, double delta)
{
    //    if (!model.validExpression())
    //        return;

    double factor;
    if (delta < 0)
        factor = 1.1;
    else
        factor = 0.9;

    performZoom(model, factor);
}

void FunctionZoomer::performZoom(FunctionModel &model, double factor)
{
    double minX = model.minX();
    double maxX = model.maxX();
    double minY = model.minY();
    double maxY = model.maxY();

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
    calculateRequest->expression = model.expression();
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
