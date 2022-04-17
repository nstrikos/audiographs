#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include "audioengine.h"
#include "requests.h"

class Audio : public QObject, public RequestReceiver
{
    Q_OBJECT
public:
    Audio();
    ~Audio();

    void accept(Request* request);

private slots:
    void audioFinished();

private:
    AudioEngine *m_audioEngine;
    RequestHandler *requestHandler;

    AudioFinishedRequest *audioFinishedRequest;

    void startAudio(QString expression,
                    double start,
                    double end,
                    double minY,
                    double maxY,
                    int seconds,
                    double fmin,
                    double fmax,
                    int mode);

    void stop();

    void reset();
};

#endif // AUDIO_H
