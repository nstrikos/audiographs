#ifndef AUDIOPOINTS_H
#define AUDIOPOINTS_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <qmath.h>
#include <QTimer>
#include <qendian.h>

const int DataFrequencyHz = 48000;
const int BufferSize   = 6000;
const int ChannelCount = 1;
const int SampleSize = 16;
const int TimerMSeconds = 5;

class AudioPoints : public QObject
{
    Q_OBJECT
public:
    AudioPoints();
    ~AudioPoints();

public:
    void startAudio();
    Q_INVOKABLE void stopAudio();
    Q_INVOKABLE void setFreq(double freq);

private slots:
    void writeMoreData();
private:
    void initializeAudio();

    QAudioDeviceInfo deviceinfo;
    QAudioOutput* audioOutput;
    QAudioFormat format;
    QIODevice* auIObuffer;
    bool audioPlaying = false;
    signed short aubuffer[BufferSize];
    double xx;
    double m_sum;
    double m_phi;
    QTimer *timer;
    int k = 0;
};

#endif // AUDIOPOINTS_H
