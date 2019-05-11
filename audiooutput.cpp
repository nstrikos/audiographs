#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>

#include "audiooutput.h"

AudioTest::AudioTest()
{
    initializeVariables();
    initializeAudio();
    //connect(generator, SIGNAL(readComplete()), this, SLOT(readDataComplete()));
}

void AudioTest::initializeVariables()
{
    m_pushTimer = new QTimer(this);
    audioEngine = NULL;
    m_pullMode = true;
    eTimer = new QElapsedTimer();
}

void AudioTest::initializeAudio()
{
    connect(m_pushTimer, SIGNAL(timeout()), SLOT(pushTimerExpired()));

    //What to do with this?
    //QAudioDeviceInfo info(m_device);
    //if (!info.isFormatSupported(m_format)) {
    //    qWarning() << "Default format not supported - trying to use nearest";
    //    m_format = info.nearestFormat(m_format);
    //}

    //if (generator != NULL)
    //    delete generator;
    //generator = new Generator();

    createAudioOutput();
}

void AudioTest::createAudioOutput()
{
    if (audioEngine != NULL)
        delete audioEngine;
    audioEngine = new AudioEngine("5/(x*x+1)", -3.0, 3.0, 10, 200, 2000);
    audioEngine->createAudioOutput();

/*    qreal initialVolume = QAudio::convertVolume(m_audioOutput->volume(),
                                                QAudio::LinearVolumeScale,
                                                QAudio::LogarithmicVolumeScale);
    m_volumeSlider->setValue(qRound(initialVolume * 100));
*/
    eTimer->start();
}

AudioTest::~AudioTest()
{
    if (audioEngine != NULL)
        delete audioEngine;
    delete m_pushTimer;
    delete eTimer;
}

void AudioTest::readDataComplete()
{
    qDebug() << eTimer->elapsed();
    //disconnect(generator, SIGNAL(readComplete()), 0, 0);
}



//The rest of the code is not used for now

void AudioTest::deviceChanged(int index)
{
    Q_UNUSED(index);

    m_pushTimer->stop();
    //generator->stop();
    //m_audioOutput->stop();
    //m_audioOutput->disconnect(this);
    initializeAudio();
}

void AudioTest::volumeChanged(int value)
{
    /*if (m_audioOutput) {
        qreal linearVolume =  QAudio::convertVolume(value / qreal(100),
                                                    QAudio::LogarithmicVolumeScale,
                                                    QAudio::LinearVolumeScale);

        m_audioOutput->setVolume(linearVolume);
    } */
    //if (m_audioOutput)
    //    m_audioOutput->setVolume(qreal(value/100.0f));
}

void AudioTest::pushTimerExpired()
{
//    if (m_audioOutput && m_audioOutput->state() != QAudio::StoppedState)
//    {
//        int chunks = m_audioOutput->bytesFree()/m_audioOutput->periodSize();
//        while (chunks)
//        {
//            const qint64 len = generator->read(m_buffer.data(), m_audioOutput->periodSize());
//            if (len)
//                m_output->write(m_buffer.data(), len);
//            if (len != m_audioOutput->periodSize())
//                break;
//            --chunks;
//        }
//    }
}

void AudioTest::toggleMode()
{
//    m_pushTimer->stop();
//    m_audioOutput->stop();

//    if (m_pullMode)
//    {
//        //switch to push mode (periodically push to QAudioOutput using a timer)
//        m_output = m_audioOutput->start();
//        m_pullMode = false;
//        m_pushTimer->start(20);
//    }
//    else
//    {
//        //switch to pull mode (QAudioOutput pulls from Generator as needed)
//        m_pullMode = true;
//        m_audioOutput->start(generator);
//    }
}

void AudioTest::toggleSuspendResume()
{
//    if (m_audioOutput->state() == QAudio::SuspendedState)
//        m_audioOutput->resume();
//    else if (m_audioOutput->state() == QAudio::ActiveState)
//        m_audioOutput->suspend();
//    else if (m_audioOutput->state() == QAudio::StoppedState)
//        m_audioOutput->resume();
//    else if (m_audioOutput->state() == QAudio::IdleState)
//    {
//        // no-op
//    }
}
