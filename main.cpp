#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "function.h"
#include "parameters.h"
#include "test.h"
#include "audiopoints.h"
#include "texttospeech.h"

#include "AndroidClient.h"

#ifndef Q_OS_ANDROID
#include <QApplication>
#include "appwindow.h"
#else
#include <QGuiApplication>
#endif


int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Function function;
    Parameters parameters;
    Test test;
    AudioPoints audioPoints;
    TextToSpeech textToSpeech(parameters);

//#ifndef Q_OS_ANDROID
//    QApplication application(argc, argv);
//    AppWindow appWindow;
//    appWindow.setFunction(&function);
//    appWindow.show();
//#else
    QGuiApplication application(argc, argv);
//#endif

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myfunction", &function);
    engine.rootContext()->setContextProperty("myparameters", &parameters);
    engine.rootContext()->setContextProperty("test", &test);
    engine.rootContext()->setContextProperty("audioPoints", &audioPoints);
    engine.rootContext()->setContextProperty("texttospeech", &textToSpeech);

    AndroidClient androidClient(&engine);
    engine.rootContext()->setContextProperty("androidClient", &androidClient);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return application.exec();
}
