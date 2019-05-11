#include "audiopoints.h"
#include <QDebug>
#include <qmath.h>

AudioPoints::AudioPoints()
{
    timer = nullptr;
    audioOutput = nullptr;
}

AudioPoints::~AudioPoints()
{
    if (timer != nullptr)
        delete timer;
    if (audioOutput != nullptr)
        delete audioOutput;
}

void AudioPoints::startAudio()
{
    audioPlaying = true;
    initializeAudio();
    writeMoreData();
}

void AudioPoints::stopAudio()
{
    if (audioOutput != nullptr) {
        audioOutput->stop();
        delete audioOutput;
        audioOutput = nullptr;
    }
    audioPlaying = false;
//    setFreq(0);
}

void AudioPoints::setFreq(double freq)
{
    xx = freq;
//    if ( xx >= 220.0 && xx <  246.94)
//        xx = 220.0;
//    else if ( xx >= 246.94 && xx < 261.63)
//        xx = 246.94;
//    else if ( xx >= 261.63 && xx < 293.66)
//        xx = 261.63;
//    else if ( xx >= 293.66 && xx < 329.63)
//        xx = 293.66;
//    else if ( xx >= 329.63 && xx < 349.23)
//        xx = 329.63;
//    else if ( xx >= 349.23 && xx < 392.00)
//        xx = 349.23;
//    else if ( xx >= 392.00 && xx < 440.00)
//        xx = 392.00;
//    else if ( xx >= 440.00 && xx < 493.88)
//        xx = 440.0;
//    else if ( xx >= 493.88 && xx < 523.25)
//        xx = 493.88;
//    else if ( xx >= 523.25 && xx < 587.33)
//        xx = 523.25;
//    else if ( xx >= 587.33 && xx < 659.25)
//        xx = 587.33;
//    else if ( xx >= 659.25 && xx < 698.46)
//        xx = 659.25;
//    else if ( xx >= 698.46 && xx < 783.99)
//        xx = 698.46;
//    else if ( xx >= 783.99 && xx < 880.00)
//        xx = 783.99;
//    else if ( xx >= 880.00 && xx < 987.77)
//        xx = 880.00;
//    else if ( xx >= 987.77 && xx < 1046.50)
//        xx = 987.77;
//    else if ( xx >= 1046.50 && xx < 1174.66)
//        xx = 1046.50;
//    else if ( xx >= 1174.66 && xx < 1318.51)
//        xx = 1174.66;
//    else if ( xx >= 1318.51 && xx < 1567.98)
//        xx = 1318.51;
//    else if ( xx >= 1567.98 && xx < 1760.00)
//        xx = 1567.98;
//    else if ( xx >= 1760.00 && xx < 1975.53)
//        xx = 1760.00;
//    else if ( xx >= 1975.53 && xx < 2093.00)
//        xx = 1975.53;
//    else if ( xx >= 2093.00 && xx < 2349.32)
//        xx = 2093.00;
//    else if ( xx >= 2349.32 && xx < 2637.02)
//        xx = 2349.32;
//    else if ( xx >= 2637.02 && xx < 2793.83)
//        xx = 2637.02;
//    else if ( xx >= 2793.83 && xx < 3135.96)
//        xx = 2793.83;
//    else if ( xx >= 3135.96)
//        xx = 3135.96;

    if (audioPlaying == false)
        startAudio();
}

void AudioPoints::initializeAudio()
{
    deviceinfo = QAudioDeviceInfo::defaultOutputDevice();
    audioOutput = nullptr;

    format.setSampleRate(DataFrequencyHz);
    format.setChannelCount(ChannelCount);
    format.setSampleSize(SampleSize);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = info.nearestFormat(format);
    }
    audioOutput = new QAudioOutput(deviceinfo, format, this);
    audioOutput->setBufferSize(BufferSize);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(writeMoreData()));
    timer->start(TimerMSeconds);
    m_sum = 0;
    m_phi = 0;
    auIObuffer = audioOutput->start();
#ifdef Q_OS_WIN
    auIObuffer = audioOutput->start(); //In windows calling audioOutput->start
    //for second time gives better results
#endif
}

void AudioPoints::writeMoreData()
{
    int emptyBytes = audioOutput->bytesFree();
    //if (emptyBytes > BufferSize) emptyBytes = BufferSize;// Check how many empty bytes are in the device buffer
    int periodSize = audioOutput->periodSize(); // Check the ideal chunk size, in bytes

    int chunks = emptyBytes/periodSize;
    while (chunks){

        for (int sample=0; sample<periodSize/2; sample++) {
            m_sum += xx/DataFrequencyHz;
            m_phi = m_sum * 2 * M_PI;
            double x = qSin(m_phi);
            signed short value = static_cast<signed short>(x * 32767);
            aubuffer[sample] = value;
        }

        auIObuffer->write((const char*) &aubuffer[0], periodSize);
        --chunks;
    }
}
