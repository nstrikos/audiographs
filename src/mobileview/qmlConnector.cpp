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

void QmlConnector::setDerivativeMode(int mode)
{
    iface.setDerivativeMode(mode);
}

void QmlConnector::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    iface.calculate(expression, minX, maxX, minY, maxY);
}

void QmlConnector::playSound()
{
    iface.playSound();
}

void QmlConnector::stopSound()
{
    iface.stopSound();
}

void QmlConnector::updateGraph(Points *points, double minX, double maxX, double minY, double maxY)
{
    emit qmlGraph(points, minX, maxX, minY, maxY);
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

}

void QmlConnector::updateLabelText(QString text)
{

}

void QmlConnector::initialStateActivated()
{

}

void QmlConnector::evaluateStateActivated()
{

}

void QmlConnector::graphReadyStateActivated()
{

}

void QmlConnector::errorDisplayStateActivated()
{

}

void QmlConnector::playSoundStateActivated()
{

}

void QmlConnector::playSoundStateDeactivated()
{

}

void QmlConnector::exploreStateActivated()
{

}

void QmlConnector::exploreStateDeactivated()
{

}

void QmlConnector::interestingPointStateActivated()
{

}

void QmlConnector::interestingPointStateDeactivated()
{

}

void QmlConnector::interestingPointStoppedStateActivated()
{

}

void QmlConnector::interestingPointStoppedStateDeactivated()
{

}

void QmlConnector::newInputValues(double minX, double maxX, double minY, double maxY)
{

}
