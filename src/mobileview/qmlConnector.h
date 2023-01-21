#ifndef QMLCONNECTOR_H
#define QMLCONNECTOR_H

#include "ifaces/IGui.h"
#include <ifaces/IMainWindow.h>

class QmlConnector : public QObject, public IMainWindow
{
    Q_OBJECT
public:
    QmlConnector(IGui &face, QObject *parent);
    virtual ~QmlConnector();

    Q_INVOKABLE void evaluate();
    Q_INVOKABLE void setDerivativeMode(int mode);
    Q_INVOKABLE void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY);
    Q_INVOKABLE void playSound();
    Q_INVOKABLE void stopSound();


    void updateGraph(Points *points, double minX, double maxX, double minY, double maxY) override;
    void error(QString errorString) override;
    void updateDerivative(Points *points, double minX, double maxX, double minY, double maxY) override;
    void newCurrentPoint(double x, double y) override;
    void updateLabelText(QString text) override;
    void initialStateActivated() override;
    void evaluateStateActivated() override;
    void graphReadyStateActivated() override;
    void errorDisplayStateActivated() override;
    void playSoundStateActivated() override;
    void playSoundStateDeactivated() override;
    void exploreStateActivated() override;
    void exploreStateDeactivated() override;
    void interestingPointStateActivated() override;
    void interestingPointStateDeactivated() override;
    void interestingPointStoppedStateActivated() override;
    void interestingPointStoppedStateDeactivated() override;
    void newInputValues(double minX, double maxX, double minY, double maxY) override;

signals:
    void qmlGraph(Points *points, double minX, double maxX, double minY, double maxY);
    void qmlError(QString errorString);
    void qmlInterestingPointFinished();
    void qmlAudioFinished();
    void qmlNewInputValues(double minX, double maxX, double minY, double maxY);

private:
    IGui &iface;
};

#endif // QMLCONNECTOR_H
