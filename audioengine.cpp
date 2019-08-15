#include "audioengine.h"
#include <QDebug>

AudioEngine::AudioEngine(QString expression, double start, double end, int seconds, int fmin, int fmax)
{
    generator = NULL;
    audioOutput = nullptr;

    this->seconds = seconds;
    this->fmin = fmin;
    this->fmax = fmax;
    m_expression = expression;
    m_start = start;
    m_end = end;
    checkParameters();
    qDebug() << "Audio engine created with parameters: seconds " << seconds
             << " fmin:" << fmin
             << " fmax:" << fmax;
}

AudioEngine::~AudioEngine()
{
    if (generator != NULL)
        delete generator;
    if (audioOutput != nullptr)
        delete audioOutput;
    qDebug() << "Audio engine deleted";
}

void AudioEngine::createAudioOutput()
{
    setDevice();
    setFormat();
    resetAudioOutput();
    resetGenerator();
    audioOutput = new QAudioOutput(device, format);
    audioOutput->start(generator);
    qDebug() << "Audio output created";
}

void AudioEngine::stop()
{
    if (audioOutput != nullptr)
        audioOutput->stop();
    qDebug() << "Audio engine stopped";
}

void AudioEngine::resetAudioOutput()
{
    if (audioOutput != NULL)
    {
        audioOutput->stop();
        delete audioOutput;
        audioOutput = NULL;
    }
    qDebug() << "Audio output reset";
}

void AudioEngine::resetGenerator()
{
    if (generator != NULL)
        delete generator;
    generator = new Generator(format, m_expression, m_start, m_end, seconds, fmin, fmax);
    generator->start();
    qDebug() << "Generator reset";
}

void AudioEngine::setDevice()
{
    qDebug() << "Trying to set audio device to default device";
    device = QAudioDeviceInfo::defaultOutputDevice();
    qDebug() << "Device set to: " << device.deviceName();
}

void AudioEngine::setFormat()
{
    qDebug() << "Trying to set audio format";
    format.setSampleRate(DataSampleRateHz);
    format.setChannelCount(channelCount);
    format.setSampleSize(sampleSize);
    format.setCodec(codec);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    qDebug() << "Audio format set to: " << format;
}

void AudioEngine::checkParameters()
{
    qDebug() << "Checking engines parameters";

    if (seconds < minDuration)
    {
        seconds = minDuration;
        qDebug() << "Duration smaller than " << minDuration;
    }
    else if (seconds > maxDuration)
    {
        seconds = maxDuration;
        qDebug() << "Duration greater than " << maxDuration;
    }

    if (fmin < minimumAllowedFmin)
    {
        fmin = minimumAllowedFmin;
        qDebug() << "Minimum frequency smaller than " << minimumAllowedFmin;
    }
    else if (fmin > maximumAllowedFmin)
    {
        fmin = maximumAllowedFmin;
        qDebug() << "Minimum frequency greater than " << maximumAllowedFmin;
    }

    if (fmax < minimumAllowedFmax)
    {
        fmax = minimumAllowedFmax;
        qDebug() << "Maximum frequency smaller than " << minimumAllowedFmax;
    }
    else if (fmax > maximumAllowedFmax)
    {
        fmax = maximumAllowedFmax;
        qDebug() << "Maximum frequency greater than " << maximumAllowedFmax;
    }

    qDebug() << "Audio engines parameters checked";
}

int AudioEngine::getFmax() const
{
    return fmax;
}

int AudioEngine::getFmin() const
{
    return fmin;
}
