#include "test.h"

Test::Test(QObject *parent) : QObject(parent)
{
    m_audioEngine = nullptr;
}

Test::~Test()
{
    if (m_audioEngine != nullptr)
        delete m_audioEngine;
}

void Test::start(QString expression, double start, double end, int seconds, int fmin, int fmax)
{
    reset();

    m_audioEngine = new AudioEngine(expression, start, end, seconds, fmin, fmax);
    m_audioEngine->createAudioOutput();
}

void Test::stop()
{
    if (m_audioEngine != nullptr)
        m_audioEngine->stop();
}

void Test::reset()
{
    if (m_audioEngine != nullptr)
    {
        m_audioEngine->stop();
        delete m_audioEngine;
        m_audioEngine = nullptr;
    }
}
