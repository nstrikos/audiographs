#ifndef IAUDIONOTES_H
#define IAUDIONOTES_H

class AudioNotes;

class IAudioNotes
{
public:
    virtual void addAudionotes(AudioNotes *audionotes) = 0;
    virtual void audioNotesFinished() = 0;
};

#endif // IAUDIONOTES_H
