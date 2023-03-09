#ifndef PINCHHANDLER_H
#define PINCHHANDLER_H

class FunctionModel;
class IDragZoom;

class PinchHandler
{
public:
    PinchHandler(IDragZoom &iface, FunctionModel &model);
    void startPinch();
    void pinch(double scale);

private:
    IDragZoom &iface;
    FunctionModel &model;
    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
};

#endif // PINCHHANDLER_H
