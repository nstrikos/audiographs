#ifndef IDRAGZOOM_H
#define IDRAGZOOM_H

class DragHandler;
class FunctionZoomer;

class IDragZoom
{
public:
    virtual void addDragHandler(DragHandler *dragHandler) = 0;
    virtual void addZoomer(FunctionZoomer *zoomer) = 0;
    virtual void newInputValues(double minX, double maxX, double minY, double maxY) = 0;
};

#endif // IDRAGZOOM_H
