#ifndef AUDIONOTES_H
#define AUDIONOTES_H

#include <QObject>
#include <QTimer>
#include "function.h"
#include "audiopoints.h"

class AudioNotes : public QObject
{
    Q_OBJECT

public:
    AudioNotes();
    ~AudioNotes();
    Q_INVOKABLE void startNotes(Function *function,
                                int fmin,
                                int fmax,
                                int duration);
    Q_INVOKABLE void setNote(Function *function,
                             int mouseX,
                             int width,
                             int fmin,
                             int fmax,
                             bool useNotes);
    Q_INVOKABLE void stopNotes();

private slots:
    void timerExpired();

private:
    Function *m_function;
    int m_fmin;
    int m_fmax;
    int m_duration;
    QTimer m_timer;
    int m_timeElapsed;
    AudioPoints *m_audioPoints;
    int m_mouseX;
};

#endif // AUDIONOTES_H
