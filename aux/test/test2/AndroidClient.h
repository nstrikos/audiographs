#ifndef ANDROIDCLIENT_H
#define ANDROIDCLIENT_H

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

#include <QObject>

class AndroidClient: public QObject
{
    Q_OBJECT
public:
    explicit AndroidClient(QObject *parent = 0);
    Q_INVOKABLE void speak(QString msg );
    Q_INVOKABLE void vibrate(QString msg );
};


#endif // ANDROIDCLIENT_H
