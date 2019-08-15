#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "audioengine.h"

class Test : public QObject
{
    Q_OBJECT
public:
    Test();
    ~Test();
    Q_INVOKABLE void start(QString expression, double start, double end, int seconds, int fmin, int fmax);
    Q_INVOKABLE void stop();

private:
    AudioEngine *m_audioEngine;

    void reset();
};

#endif // TEST_H
