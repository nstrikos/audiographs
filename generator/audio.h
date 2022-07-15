#ifndef AUDIO_H
#define AUDIO_H

class IAudio;

#include "audioengine.h"

class Audio
{    
public:
    Audio(IAudio &iface);
    ~Audio();
    void start(QString expression,
                           double start,
                           double end,
                           double minY,
                           double maxY,
                           int seconds,
                           double fmin,
                           double fmax,
                           int mode);
    void stop();
    void audioFinished();

private:
    IAudio &iface;
    AudioEngine *m_audioEngine;
    void reset();
};

#endif // AUDIO_H
