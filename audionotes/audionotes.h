#ifndef AUDIONOTES_H
#define AUDIONOTES_H

class IAudio;

#include <QObject>
#include <QTimer>
#include "function/functionModel.h"
#include "audiopoints.h"

class AudioNotes : public QObject
{
    Q_OBJECT

public:
    AudioNotes(IAudio &iface, FunctionModel &model);
    ~AudioNotes();
    void startNotes(int fmin,
                    int fmax,
                    int duration,
                    bool useNegativeNotes);

    Q_INVOKABLE void setNoteFromMouse(int mouseX,
                                      int width,
                                      int fmin,
                                      int fmax,
                                      bool useNotes);

    Q_INVOKABLE void setNote(int currentPoint,
                             int fmin,
                             int fmax,
                             bool useNotes,
                             bool useNegativeNotes);
    Q_INVOKABLE void stopNotes();


private slots:
    void timerExpired();
    void audionotesFinished();

private:
    IAudio &iface;
    FunctionModel &m_model;
    int m_fmin;
    int m_fmax;
    int m_duration;
    QTimer m_timer;
    int m_timeElapsed;
    AudioPoints *m_audioPoints;
    int m_mouseX;
    int m_currentPoint;
    bool m_useNegativeNotes = false;
};

#endif // AUDIONOTES_H
