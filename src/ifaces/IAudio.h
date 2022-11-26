#ifndef IAUDIO_H
#define IAUDIO_H

class Audio;

class IAudio
{
public:
    virtual void addAudio(Audio *audio) = 0;
    virtual void audioFinished() = 0;
};

#endif // IAUDIO_H