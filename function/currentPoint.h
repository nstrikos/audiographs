#ifndef CURRENTPOINT_H
#define CURRENTPOINT_H

class ICurrentPoint;
class FunctionModel;

#include <QObject>
#include <QTimer>

class CurrentPoint : public QObject
{
    Q_OBJECT
public:
    CurrentPoint(ICurrentPoint &iface, FunctionModel &model);
    void startMoving(int duration);
    void stop();
    void reset();
    void endPoint();
    void next();
    void previous();
    int point();
    void decStep();
    void incStep();

    int step() const;
    void setPoint(int point);

    void incPoint(int step);
    void decPoint(int step);

private slots:
    void timerExpired();

private:
    ICurrentPoint &iface;
    FunctionModel &model;

    int m_duration;
    int m_timeElapsed;
    QTimer timer;

    double m_x;
    double m_y;
    int m_point;
    int m_step;
};

#endif // CURRENTPOINT_H
