#ifndef AUDIONOTES_H
#define AUDIONOTES_H

#include <QObject>
#include <QTimer>
#include "function/functionModel.h"
#include "audiopoints.h"
#include "requests.h"

class AudioNotes : public QObject, public RequestReceiver
{
    Q_OBJECT

public:
    AudioNotes(FunctionModel &model);
    ~AudioNotes();
    void accept(Request *request);

private slots:
    void timerExpired();

private:
    FunctionModel &m_model;
    RequestHandler *requestHandler;
    AudioFinishedRequest *audioFinishedRequest;    
    int m_fmin;
    int m_fmax;
    int m_duration;
    QTimer m_timer;
    int m_timeElapsed;
    AudioPoints *m_audioPoints;
    int m_currentPoint = 0;

    bool m_useNegativeNotes = false;

    void startNotes(int fmin,
                    int fmax,
                    int duration,
                    bool useNegativeNotes);

    void setNote(int fmin,
                 int fmax,
                 bool useNotes,
                 bool useNegativeNotes);
    void stopNotes();

    void setPoint(int point);
};

#endif // AUDIONOTES_H
