#include "qmlconnector.h"

QmlConnector::QmlConnector()
{
    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_update);
    requestHandler->add(this, request_error);
    requestHandler->add(this, request_new_values);

    calculateRequest = new CalculateRequest();
    startDragRequest = nullptr;
    dragRequest = nullptr;
    startPinchRequest = nullptr;
    pinchRequest = nullptr;
    zoomRequest = nullptr;
}

QmlConnector::~QmlConnector()
{
    delete calculateRequest;
    if (startDragRequest != nullptr)
        delete startDragRequest;
    if (dragRequest != nullptr)
        delete dragRequest;
    if (startPinchRequest != nullptr)
        delete startPinchRequest;
    if (pinchRequest != nullptr)
        delete pinchRequest;
    if (zoomRequest != nullptr)
        delete zoomRequest;
}

void QmlConnector::accept(Request *request)
{
    if (request->type == request_update) {
        UpdateRequest *tmp_request = static_cast<UpdateRequest*>(request);
        emit newGraph(tmp_request->minX,
                      tmp_request->maxX,
                      tmp_request->minY,
                      tmp_request->maxY);
    } else if (request->type == request_error) {
        ErrorRequest *tmp_request = static_cast<ErrorRequest*>(request);
        emit error(tmp_request->error);
    } else if (request->type == request_new_values) {
        NewInputValuesRequest *tmp_request = static_cast<NewInputValuesRequest*>(request);
        emit newInputValues(tmp_request->minX,
                            tmp_request->maxX,
                            tmp_request->minY,
                            tmp_request->maxY);
    }
}

void QmlConnector::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    calculateRequest->expression = expression;
    calculateRequest->minX = minX;
    calculateRequest->maxX = maxX;
    calculateRequest->minY = minY;
    calculateRequest->maxY = maxY;
    requestHandler->handleRequest(calculateRequest);
}

void QmlConnector::startDrag(int x, int y)
{
    if (startDragRequest == nullptr)
        startDragRequest = new StartDragRequest();
    startDragRequest->x = x;
    startDragRequest->y = y;
    requestHandler->handleRequest(startDragRequest);
}

void QmlConnector::drag(int diffX, int diffY, int width, int height)
{
    if (dragRequest == nullptr)
        dragRequest = new DragRequest();
    dragRequest->diffX = diffX;
    dragRequest->diffY = diffY;
    dragRequest->width = width;
    dragRequest->height = height;
    requestHandler->handleRequest(dragRequest);
}

void QmlConnector::startPinch()
{
    if (startPinchRequest == nullptr)
        startPinchRequest = new StartPinchRequest();
    requestHandler->handleRequest(startPinchRequest);
}

void QmlConnector::pinch(double scale)
{
    if (pinchRequest == nullptr)
        pinchRequest = new PinchRequest();
    pinchRequest->scale = scale;
    requestHandler->handleRequest(pinchRequest);
}

void QmlConnector::zoom(double delta)
{
    if (zoomRequest == nullptr)
        zoomRequest = new ZoomRequest();
    zoomRequest->delta = delta;
    requestHandler->handleRequest(zoomRequest);
}
