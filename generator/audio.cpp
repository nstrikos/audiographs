#include "audio.h"

#include <QtMath>

Audio::Audio()
{
    m_audioEngine = nullptr;
    audioFinishedRequest = nullptr;
    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_audio_start);
    requestHandler->add(this, request_stop_sound);
    requestHandler->add(this, request_first_point);
    requestHandler->add(this, request_last_point);
}

Audio::~Audio()
{
    if (m_audioEngine != nullptr)
        delete m_audioEngine;
    if (audioFinishedRequest != nullptr)
        delete audioFinishedRequest;
}

void Audio::accept(Request *request)
{
    if (m_log)
        qDebug() << "Audio accepted id: " << request->id << " type: " << request->type;
    if (request->type == request_audio_start) {
        QString expression = static_cast<AudioStartRequest*>(request)->expression;
        double start = static_cast<AudioStartRequest*>(request)->start;
        double end = static_cast<AudioStartRequest*>(request)->end;
        double minY = static_cast<AudioStartRequest*>(request)->minY;
        double maxY = static_cast<AudioStartRequest*>(request)->maxY;
        int seconds = static_cast<AudioStartRequest*>(request)->seconds;
        double fmin = static_cast<AudioStartRequest*>(request)->fmin;
        double fmax = static_cast<AudioStartRequest*>(request)->fmax;
        int mode = static_cast<AudioStartRequest*>(request)->mode;
        startAudio(expression, start, end, minY, maxY, seconds, fmin, fmax, mode);
    } else if (request->type == request_stop_sound) {
        stop();
    } else if (request->type == request_first_point) {
        stop();
    } else if (request->type == request_last_point) {
        stop();
    }

}

void Audio::startAudio(QString expression,
                       double start,
                       double end,
                       double minY,
                       double maxY,
                       int seconds,
                       double fmin,
                       double fmax,
                       int mode)
{
    reset();

    std::string exp = expression.toStdString();

    m_audioEngine = new AudioEngine(expression,
                                    start,
                                    end,
                                    minY,
                                    maxY,
                                    seconds,
                                    fmin,
                                    fmax,
                                    mode);

    connect(m_audioEngine, &AudioEngine::finished, this, &Audio::audioFinished);

    m_audioEngine->createAudioOutput();
}

void Audio::audioFinished()
{
    if (audioFinishedRequest == nullptr)
        audioFinishedRequest = new AudioFinishedRequest();
    audioFinishedRequest->sender = "Audio";
    requestHandler->handleRequest(audioFinishedRequest);
}

void Audio::stop()
{
    if (m_audioEngine != nullptr)
        m_audioEngine->stop();
}

void Audio::reset()
{
    if (m_audioEngine != nullptr)
    {
        m_audioEngine->stop();
        delete m_audioEngine;
        m_audioEngine = nullptr;
    }
}
