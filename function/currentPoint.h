#ifndef CURRENTPOINT_H
#define CURRENTPOINT_H

#include "requests.h"
#include "parameters.h"
#include <QObject>
#include <QTimer>

class FunctionModel;

class CurrentPoint : public QObject, public RequestReceiver
{
    Q_OBJECT
public:
    CurrentPoint(FunctionModel &model);
    ~CurrentPoint();

    void accept(Request *request);

private slots:
    void timerExpired();

private:
    FunctionModel &m_model;
    RequestHandler *requestHandler;
    NewPointRequest *newPointRequest;
    DrawPointRequest *drawPointRequest;
    Parameters *parameters;

    SayTextRequest *sayTextRequest;
    UpdateTextRequest *updateTextRequest;

    int m_duration;
    int m_timeElapsed;
    QTimer timer;

    double m_X;
    double m_Y;
    int m_point;
    int m_step;

    void startMoving();
    void stop();
    void reset();
    void next();
    void previous();
    void decStep();
    void incStep();

    void sayText(QString text);
    void updateText(QString text);

    void setPoint(int point);
    void incPoint(int step);
    void decPoint(int step);
    void endPoint();
    void drawPoint();

    void sayX();
    void sayY();
    void getX();
    void getY();
};

#endif // CURRENTPOINT_H
