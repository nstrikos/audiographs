#ifndef QMLCONNECTOR_H
#define QMLCONNECTOR_H

#include <QObject>
#include "requestHandler.h"

class QmlConnector : public QObject,  public RequestReceiver
{
    Q_OBJECT
public:
    QmlConnector();
    ~QmlConnector();
    void accept(Request *request);
    
    Q_INVOKABLE void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY);
    Q_INVOKABLE void startDrag(int x, int y);
    Q_INVOKABLE void drag(int diffX, int diffY, int width, int height);
    Q_INVOKABLE void startPinch();
    Q_INVOKABLE void pinch(double scale);
    Q_INVOKABLE void zoom(double delta);
    
signals:
    void newGraph(double minX, double maxX, double minY, double maxY);
    void error(QString errorString);
    void newInputValues(double minX, double maxX, double minY, double maxY);
private:
    RequestHandler *requestHandler;
    CalculateRequest *calculateRequest;
    StartDragRequest *startDragRequest;
    DragRequest *dragRequest;
    StartPinchRequest *startPinchRequest;
    PinchRequest *pinchRequest;
    ZoomRequest *zoomRequest;
};

#endif // QMLCONNECTOR_H
