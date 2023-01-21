#ifndef IMAINWINDOW_H
#define IMAINWINDOW_H

#include "function/point.h"

class IMainWindow
{
public:
    IMainWindow();
    virtual void updateGraph(Points *points, double minX, double maxX, double minY, double maxY) = 0;
    virtual void error(QString errorString) = 0;
    virtual void updateDerivative(Points *points, double minX, double maxX, double minY, double maxY) = 0;
    virtual void newInputValues(double minX, double maxX, double minY, double maxY) = 0;
    virtual void newCurrentPoint(double x, double y) = 0;
    virtual void updateLabelText(QString text) = 0;
    virtual void initialStateActivated() = 0;
    virtual void evaluateStateActivated() = 0;
    virtual void graphReadyStateActivated() = 0;
    virtual void errorDisplayStateActivated() = 0;
    virtual void playSoundStateActivated() = 0;
    virtual void playSoundStateDeactivated() = 0;
    virtual void exploreStateActivated() = 0;
    virtual void exploreStateDeactivated() = 0;
    virtual void interestingPointStateActivated() = 0;
    virtual void interestingPointStateDeactivated() = 0;
    virtual void interestingPointStoppedStateActivated() = 0;
    virtual void interestingPointStoppedStateDeactivated() = 0;
};

#endif // IMAINWINDOW_H
