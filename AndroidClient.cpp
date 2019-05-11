#include <QDebug>

#include "AndroidClient.h"



AndroidClient::AndroidClient(QObject *parent)
    : QObject(parent)
{

}

void AndroidClient::speak(QString msg)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(msg);
    QAndroidJniObject::callStaticMethod<void>("org/nstrikos/access/audiographs/AndroidClient",
                                              "speak",
                                              "(Ljava/lang/String;)V",
                                              javaMessage.object<jstring>());
#else
    qDebug() << "Speak: " + msg;
#endif
}

void AndroidClient::vibrate(QString msg)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(msg);
    QAndroidJniObject::callStaticMethod<void>("org/nstrikos/access/audiographs/AndroidClient",
                                              "vibrate",
                                              "(Ljava/lang/String;)V",
                                              javaMessage.object<jstring>());
#else
    qDebug() << "Vibrate: " + msg;
#endif
}
