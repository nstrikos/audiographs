#ifndef DRAGHANDLER_H
#define DRAGHANDLER_H

class FunctionModel;
class IDragZoom;

/*
 * startDrag - Sets the variables when the drag starts
 * drag - Calculates function with new rounded values and updates the new values
 * */

class DragHandler
{
public:
    DragHandler(IDragZoom &iface, FunctionModel &model);
    void startDrag(int x, int y);
    void drag(int diffX, int diffY, int width, int height);

private:
    IDragZoom &iface;
    FunctionModel &model;
    int m_dragX;
    int m_dragY;

    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
};

#endif // DRAGHANDLER_H
