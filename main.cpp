#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "function.h"
#include "parameters.h"
#include "test.h"
//#include "audiopoints.h"
#include "audionotes.h"
//#include "texttospeech.h"

//#include "AndroidClient.h"

#include "curve.h"
#include "curvemovingpoint.h"

#ifndef Q_OS_ANDROID
#include <QApplication>
//#include "appwindow.h"
#else
#include <QGuiApplication>
#endif


int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Function function;
    Parameters parameters;
    Test test;
//    AudioPoints audioPoints;
    AudioNotes audioNotes;
//    TextToSpeech textToSpeech(parameters);

    //#ifndef Q_OS_ANDROID
    //    QApplication application(argc, argv);
    //    AppWindow appWindow;
    //    appWindow.setFunction(&function);
    //    appWindow.show();
    //#else
    QGuiApplication application(argc, argv);
    //#endif

    qmlRegisterType<Curve>("CustomGeometry", 1, 0, "Curve");
    qmlRegisterType<CurveMovingPoint>("CurveMovingPoint", 1, 0, "CurveMovingPoint");


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myfunction", &function);
    engine.rootContext()->setContextProperty("myparameters", &parameters);
    engine.rootContext()->setContextProperty("test", &test);
    engine.rootContext()->setContextProperty("audioNotes", &audioNotes);
//    engine.rootContext()->setContextProperty("texttospeech", &textToSpeech);

//    AndroidClient androidClient(&engine);
//    engine.rootContext()->setContextProperty("androidClient", &androidClient);


    engine.load(QUrl(QStringLiteral("qrc:/mainmain.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return application.exec();
}
