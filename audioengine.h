#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QAudioOutput>
#include "generator.h"

const int channelCount = 1;
const int sampleSize = 16;
const QString codec = "audio/pcm";

const int minDuration = 10;
const int maxDuration = 120;
const int minimumAllowedFmin = 50;
const int maximumAllowedFmin = 8000;
const int minimumAllowedFmax = 00;
const int maximumAllowedFmax = 12000;

class AudioEngine
{
public:
    AudioEngine(QString expression, double m_start, double m_end, int seconds, int fmin, int fmax);
    ~AudioEngine();
    Q_INVOKABLE void createAudioOutput();
    Q_INVOKABLE void stop();

    int getFmin() const;
    int getFmax() const;

private:
    void resetAudioOutput();
    void resetGenerator();
    void setDevice();
    void setFormat();
    void checkParameters();
    QAudioOutput *audioOutput;
    QAudioDeviceInfo device;
    QAudioFormat format;
    Generator *generator;
    int seconds;
    int fmax;
    int fmin;
    QString m_expression;
    double m_start;
    double m_end;
};

#endif // AUDIOENGINE_H
