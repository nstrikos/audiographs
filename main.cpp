#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include "function.h"
#include "parameters.h"
#include "test.h"
#include "audiopoints.h"
#include "texttospeech.h"

#include "AndroidClient.h"

#include "curve.h"
#include "QSurfaceFormat"
#include <QQuickView>

#ifndef Q_OS_ANDROID
#include <QApplication>
#include "appwindow.h"
#else
#include <QGuiApplication>
#endif


int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setSamples(256);
//    QSurfaceFormat::setDefaultFormat(format);
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

    qmlRegisterType<Curve>("CustomGeometry", 1, 0, "Curve");
    qmlRegisterType<BezierCurve>("CustomGeometry2", 1, 0, "BezierCurve");


//    QQuickView view;
//    QSurfaceFormat format = view.format();
//    format.setSamples(256);
//    view.setFormat(format);
//    view.setSource(QUrl("qrc:///mainmain.qml"));
//    view.rootContext()->setContextProperty("myfunction", &function);
//    view.rootContext()->setContextProperty("myparameters", &parameters);
//    view.rootContext()->setContextProperty("test", &test);
//    view.rootContext()->setContextProperty("audioPoints", &audioPoints);
//    view.rootContext()->setContextProperty("texttospeech", &textToSpeech);
//    view.show();



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myfunction", &function);
    engine.rootContext()->setContextProperty("myparameters", &parameters);
    engine.rootContext()->setContextProperty("test", &test);
    engine.rootContext()->setContextProperty("audioPoints", &audioPoints);
    engine.rootContext()->setContextProperty("texttospeech", &textToSpeech);

//    qmlRegisterType<Curve>("CustomGeometry", 1, 0, "Curve");

    AndroidClient androidClient(&engine);
    engine.rootContext()->setContextProperty("androidClient", &androidClient);


    engine.load(QUrl(QStringLiteral("qrc:/mainmain.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return application.exec();
}
