#ifndef AUDIOPOINTS_H
#define AUDIOPOINTS_H

#include <QObject>
#include <QAudioOutput>
#include <QTimer>
#include <random>

const int DataFrequencyHz = 48000;
const int BufferSize = 32000;
const int ChannelCount = 2;
const int SampleSize = 16;
const int TimerMSeconds = 5;
const int duration = 1000;

class AudioPoints : public QObject
{
    Q_OBJECT
public:
    AudioPoints();
    ~AudioPoints();

public:
    void start();
    void stop();
    void playFreq(double freq, bool useNegative, double ratio);

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
    double xx2;
    double m_sum;
    double m_sum2;
    double m_phi;
    double m_phi2;
    int instrument = 0;
    QTimer timer;
    int k = 0;
    int m = 0;
    int m_2 = 0;

    double m_f0 = 1.0;
    double m_f1 = 0.0;
    double m_f2 = 0.0;
    double m_f3 = 0.0;
    double m_f4 = 0.0;
    double m_f5 = 0.0;
    double m_f6 = 0.0;
    double m_f7 = 0.0;
    double m_f8 = 0.0;
    double m_f9 = 0.0;
    double m_f10 = 0.0;

    bool m_n;
    int m_time;
    double m_ratio;
    bool m_isPlaying;

    const double m_mean = 0.0;
    const double m_stddev = 100;
    std::default_random_engine m_generator;
};

#endif // AUDIOPOINTS_H
