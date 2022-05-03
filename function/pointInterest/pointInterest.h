#ifndef POINTINTEREST_H
#define POINTINTEREST_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "function/functionModel.h"
#include "functionDescription.h"
#include "parameters.h"
#include "requests.h"

class PointsInterest : public QObject , public RequestReceiver
{
    Q_OBJECT
public:
    explicit PointsInterest(FunctionModel &functionModel);
    ~PointsInterest();

    void accept(Request *request);

private slots:
    void timerExpired();

private:
    //Requests
    RequestHandler *requestHandler;
    SetPointRequest *setPointRequest;
    IncPointRequest *incPointRequest;
    DecPointRequest *decPointRequest;
    InterestingPointFinishedRequest *interestingPointFinishedRequest;
    UpdateTextRequest *updateTextRequest;
    SetNoteRequest *setNoteRequest;
    StopNotesRequest *stopNotesRequest;
    SayTextRequest *sayTextRequest;    

    void sendNewPoint(int point);

    int m_pointInterest;
    QTimer m_timer;
    bool m_forward;
    FunctionModel &m_model;
    FunctionDescription *m_funcDescription;
    QVector<InterestingPoint> m_points;
    bool m_isUpdated;
    int m_step = 1;
    int m_timerInterVal = 40;
    int m_curPoint = 0;
    int m_derivativeMode = 0;

    int getStep();
    void setUpdated(int mode);
    int getNextPointInterest();
    void start();

    void finished();
    void updateLabel(QString text);
    void sendNoteRequest(int fmin, int fmax, bool useNotes, bool useNegativeNotes);
    void sayText(QString text);
    void nextPoint();
    void previousPoint();
    void nextPointFast();
    void previousPointFast();
    void stop();
    QString currentPointLabel();

    Parameters *m_parameters;
};

#endif // POINTSINTEREST_H
