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
#include "utils/parameters.h"
#include "utils/texttospeech.h"

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
    void update();
    int util(int i, int size, int n, int timerInterval);

    int m_pointInterest; //current point of interest
    bool m_forward;    //true means going to right of x axis, false going to the left
    FunctionDescription *m_funcDescription; //returns the points of interest
    QVector<InterestingPoint> m_interestingPoints; //store the points of interest
    bool m_isUpdated; //points are updated only when necessary
    int m_step; //how fast current point will move
    int m_timerInterVal;  //how fast current point will be updated
    QTimer m_timer;
    QVector<int> stepCandidates;
};

#endif // POINTSINTEREST_H
