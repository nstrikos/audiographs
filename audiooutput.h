#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H

#include <math.h>
#include "audioengine.h"

#include <QAudioOutput>
#include <QTimer>
#include <QElapsedTimer>

class AudioTest : public QObject
{
    Q_OBJECT

public:
    AudioTest();
    ~AudioTest();

private:
    void initializeVariables();
    void initializeAudio();
    void createAudioOutput();

private:
    QTimer *m_pushTimer;
    QElapsedTimer *eTimer;

    AudioEngine *audioEngine;
    bool m_pullMode;

private slots:
    void pushTimerExpired();
    void toggleMode();
    void toggleSuspendResume();
    void deviceChanged(int index);
    void volumeChanged(int);
    void readDataComplete();
};

#endif // AUDIOOUTPUT_H
