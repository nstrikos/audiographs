#ifndef DRAGHANDLER_H
#define DRAGHANDLER_H

class FunctionModel;
class IDragZoom;

class DragHandler
{
public:
    DragHandler(IDragZoom &iface, FunctionModel &model);
    void startDrag(int x, int y);
    void drag(int diffX, int diffY, int width, int height);

private:
    FunctionModel &model;
    IDragZoom &iface;
    int m_dragX;
    int m_dragY;

    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
};

#endif // DRAGHANDLER_H
