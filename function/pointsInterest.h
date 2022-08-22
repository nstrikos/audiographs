#ifndef POINTSINTEREST_H
#define POINTSINTEREST_H

class IPointsInterest;

#include <QObject>
#include <QVector>
#include <QTimer>
#include "function/functionModel.h"
#include "function/functionDescription.h"
#include "function/currentPoint.h"
#include "audionotes/audionotes.h"
#include "parameters.h"
#include "texttospeech.h"

/*
 * init - initializes pointsInterest
 * nextPoint - goes to the next point of interest, updating currentPoint
 * previousPoint - goes to the previous point of interest, updating currentPoint
 * nextPointFast - goes to the next point of interest immediately
 * previousPointFast - goes to the previous point of interest immediately
 * stop - stops pointsInterest
 * notUpdated - pointsInterest is not updated
 * */

class PointsInterest : public QObject
{
    Q_OBJECT
public:
    explicit PointsInterest(IPointsInterest &iface,
                            FunctionModel &functionModel,
                            AudioNotes &audioNotes,
                            CurrentPoint &currentPoint);
    ~PointsInterest();

    void init();
    void nextPoint();
    void previousPoint();
    void nextPointFast();
    void previousPointFast();
    void stop();
    void notUpdated();

private slots:
    void timerExpired();

private:
    IPointsInterest &iface;
    FunctionModel &m_model;
    AudioNotes &m_audioNotes;
    CurrentPoint &m_currentPoint;
    TextToSpeech *m_textToSpeech;
    Parameters *m_parameters;

    void start();
    int getNextPointInterest();
    QString currentPointLabel();
    void setStep();

    int m_pointInterest;
    QTimer m_timer;
    bool m_forward;    
    FunctionDescription *m_funcDescription;
    QVector<InterestingPoint> m_points;
    bool m_isUpdated;
    int m_step = 1;
    int m_timerInterVal = 40;
};

#endif // POINTSINTEREST_H
