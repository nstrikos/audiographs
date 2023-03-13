#ifndef CURRENTPOINT_H
#define CURRENTPOINT_H

class ICurrentPoint;
class FunctionModel;

#include <QObject>
#include <QTimer>

/*
 * startMoving - Starts the timer, when timer expires it updates the position *
 * stop - Stops the timer
 * reset - Stops the timer, sets the position at zero point
 * endPoint - Stops the timers,  sets the position to the last point
 * next - Increases the position of point by step points
 * previous - Decreases the position of point by step points
 * incStep - Increases step
 * decStep - Decreases step
 * step - Returns step
 *
 * pointsInterest:
 * point - Returns current point
 * incPoint - Increases the position of point by i points
 * decPoint - Decreases the position of point by i points
 * setPoint - Sets the position of point *
 * */

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
    void decStep();
    void incStep();
    int step() const;

    //PointsInterest
    int point();
    void incPoint(int i);
    void decPoint(int i);
    void setPoint(int point);
    void update();

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
