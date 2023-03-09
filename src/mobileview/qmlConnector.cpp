#include "qmlConnector.h"
#include <QDebug>

QmlConnector::QmlConnector(IGui &iface, QObject *parent) : iface(iface)
{
    Q_UNUSED(parent)
    iface.addGui(this);
}

QmlConnector::~QmlConnector()
{

}

void QmlConnector::evaluate()
{
    iface.evaluate();
}

void QmlConnector::newGraph()
{
    iface.newGraph();
}

void QmlConnector::functionError()
{
    iface.functionError();
}

void QmlConnector::setDerivativeMode(int mode)
{
    iface.setDerivativeMode(mode);
}

void QmlConnector::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    iface.calculate(expression, minX, maxX, minY, maxY);
}

void QmlConnector::playPressed()
{
    iface.playPressed();
}

void QmlConnector::playSound()
{
    iface.playSound();
}

void QmlConnector::stopSound()
{
    iface.stopSound();
}

void QmlConnector::previousPointInterest()
{
    iface.previousPointInterest();
}

void QmlConnector::nextPointInterest()
{
    iface.nextPointInterest();
}

void QmlConnector::firstPoint()
{
    iface.firstPoint();
}

void QmlConnector::lastPoint()
{
    iface.lastPoint();
}

void QmlConnector::previousPoint()
{
    iface.previousPoint();
}

void QmlConnector::nextPoint()
{
    iface.nextPoint();
}

void QmlConnector::previousFast()
{
    iface.previousFast();
}

void QmlConnector::nextFast()
{
    iface.nextFast();
}

void QmlConnector::zoom(double delta)
{
    iface.zoom(delta);
}

void QmlConnector::startDrag(int x, int y)
{
    iface.startDrag(x, y);
}

void QmlConnector::drag(int diffX, int diffY, int width, int height)
{
    iface.drag(diffX, diffY, width, height);
}

void QmlConnector::startPinch()
{
    iface.startPinch();
}

void QmlConnector::pinch(double scale)
{
    iface.pinch(scale);
}

void QmlConnector::updateGraph(Points *points, double minX, double maxX, double minY, double maxY)
{
    emit qmlUpdateGraph(points, minX, maxX, minY, maxY);
}

void QmlConnector::error(QString errorString)
{
    emit qmlError(errorString);
}

void QmlConnector::updateDerivative(Points *points, double minX, double maxX, double minY, double maxY)
{

}

void QmlConnector::newCurrentPoint(double x, double y)
{
    emit qmlNewCurrentPoint(x, y);
}

void QmlConnector::updateLabelText(QString text)
{

}

void QmlConnector::initialStateActivated()
{
    emit qmlInitialStateActivated();
}

void QmlConnector::evaluateStateActivated()
{
    emit qmlEvaluateStateActivated();
}

void QmlConnector::graphReadyStateActivated()
{
    emit qmlGraphReadyStateActivated();
}

void QmlConnector::errorDisplayStateActivated()
{

}

void QmlConnector::playSoundStateActivated()
{
    emit qmlPlaySoundStateActivated();
}

void QmlConnector::playSoundStateDeactivated()
{
    emit qmlPlaySoundStateDeactivated();
}

void QmlConnector::exploreStateActivated()
{
    emit qmlExploreStateActivated();
}

void QmlConnector::exploreStateDeactivated()
{
    emit qmlExploreStateDeactivated();
}

void QmlConnector::interestingPointStateActivated()
{
    emit qmlInterestingPointStateActivated();
}

void QmlConnector::interestingPointStateDeactivated()
{
    emit qmlInterestingPointStateDeactivated();
}

void QmlConnector::interestingPointStoppedStateActivated()
{
    emit qmlInterestingPointStoppedStateActivated();
}

void QmlConnector::interestingPointStoppedStateDeactivated()
{
    emit qmlInterestingPointStoppedStateDeactivated();
}

void QmlConnector::newInputValues(double minX, double maxX, double minY, double maxY)
{
    emit qmlNewInputValues(minX, maxX, minY, maxY);
}
