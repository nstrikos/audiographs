#include "dragHandler.h"
#include "../functionModel.h"

#include <QDebug>

DragHandler::DragHandler(FunctionModel &model) : m_model(model)
{
    newInputValuesRequest = nullptr;
    calculateRequest = nullptr;

    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_start_drag);
    requestHandler->add(this, request_drag);
}

DragHandler::~DragHandler()
{
    if (newInputValuesRequest != nullptr)
        delete newInputValuesRequest;
    if (calculateRequest != nullptr)
        delete calculateRequest;
}

void DragHandler::accept(Request *request)
{
    if (m_log)
        qDebug() << "DragHandler used id: " << request->id << " type: " << request->description;
    if (request->type == request_start_drag) {
        int x = static_cast<StartDragRequest*>(request)->x;
        int y = static_cast<StartDragRequest*>(request)->y;
        startDrag(x, y);
    } else if (request->type == request_drag) {
        int diffX = static_cast<DragRequest*>(request)->diffX;
        int diffY = static_cast<DragRequest*>(request)->diffY;
        int width = static_cast<DragRequest*>(request)->width;
        int height = static_cast<DragRequest*>(request)->height;
        drag(diffX, diffY, width, height);
    }
}

void DragHandler::startDrag(int x, int y)
{
    if (!m_model.validExpression())
        return;

    m_dragX = x;
    m_dragY = y;
    m_minX = m_model.minX();
    m_maxX = m_model.maxX();
    m_minY = m_model.minY();
    m_maxY = m_model.maxY();
}

void DragHandler::drag(int diffX, int diffY, int width, int height)
{
    if (!m_model.validExpression())
        return;

    //The level of precision in rounding depends on the distance between the values
    double distanceX = m_maxX - m_minX;

    int powerX = -floor(log10(distanceX)) + 2;

    //variable precisionX holds the level of precision
    double precisionX = pow(10, powerX);

    double distanceY = m_maxY - m_minY;

    int powerY = -floor(log10(distanceY)) + 2;
    double precisionY = pow(10, powerY);

    int newDiffX = diffX - m_dragX;
    int newDiffY = diffY - m_dragY;

    double diffXDouble = (double)((m_maxX - m_minX)) / (double)width * newDiffX;
    double diffYDouble = (double)((m_maxY - m_minY)) / (double)height * newDiffY;

    //newMinX, newMaxX, newMinY, newMaxY are the new values
    double newMinX, newMaxX, newMinY, newMaxY;

    if (powerX > 0) {
        newMinX = round( (m_minX - diffXDouble) * precisionX) / precisionX;
        newMaxX = round( (m_maxX - diffXDouble) * precisionY) / precisionY;
    } else {
        newMinX = round(m_minX - diffXDouble);
        newMaxX = round(m_maxX - diffXDouble);
    }

    if (powerY > 0) {
        newMinY = round( (m_minY + diffYDouble) * precisionY) / precisionY;
        newMaxY = round( (m_maxY + diffYDouble) * precisionY) / precisionY;
    } else {
        newMinY = round(m_minY + diffYDouble);
        newMaxY = round(m_maxY + diffYDouble);
    }


    //we update with the rounded values
    sendCalculateRequest(newMinX, newMaxX, newMinY, newMaxY);
    sendNewInputValuesRequest(newMinX, newMaxX, newMinY, newMaxY);
}

void DragHandler::sendCalculateRequest(double minX, double maxX, double minY, double maxY)
{
    if (calculateRequest == nullptr)
        calculateRequest = new CalculateRequest;
    calculateRequest->sender = "DragHandler";
    calculateRequest->expression = m_model.expression();
    calculateRequest->minX = QString::number(minX);
    calculateRequest->maxX = QString::number(maxX);
    calculateRequest->minY = QString::number(minY);
    calculateRequest->maxY = QString::number(maxY);

    requestHandler->handleRequest(calculateRequest);
}

void DragHandler::sendNewInputValuesRequest(double minX, double maxX, double minY, double maxY)
{
    if (newInputValuesRequest == nullptr)
        newInputValuesRequest = new NewInputValuesRequest();
    newInputValuesRequest->sender = "DragHandler";
    newInputValuesRequest->minX = minX;
    newInputValuesRequest->maxX = maxX;
    newInputValuesRequest->minY = minY;
    newInputValuesRequest->maxY = maxY;

    requestHandler->handleRequest(newInputValuesRequest);
}
