#ifndef AUDIONOTES_H
#define AUDIONOTES_H

class IAudio;

#include <QObject>
#include <QTimer>
#include "function/functionModel.h"
#include "audiopoints.h"

/*
 * startNotes - Starts playing notes
 *
 * setNoteFromMouse - Plays note depending on the position of mouse
 *
 * setNote - Plays notes depending on the position of currentPoint
 *
 * stopNotes - Stops playing notes
 * */

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

    void setNoteFromMouse(int mouseX,
                          int width,
                          int fmin,
                          int fmax,
                          bool useNotes);

    void setNote(int currentPoint,
                 int fmin,
                 int fmax,
                 bool useNegativeNotes);

    void stopNotes();

private slots:
    void timerExpired();

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
