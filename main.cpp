#include "mainwindow.h"

#include <QApplication>

#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QQmlContext>
//#include "function/functionDisplayView.h"
//#include "function/functionPointView.h"
//#include "function/point.h"

#include "functionController.h"
#include "function/functionModel.h"
#include "function/dragHandler.h"
#include "function/functionZoomer.h"
#include "function/currentPoint.h"
#include "generator/audio.h"
#include "audionotes/audionotes.h"
#include "function/pointsInterest.h"

int main(int argc, char *argv[])
{
//    bool runMobile = false;

//#ifdef Q_OS_ANDROID
//    runMobile = true;
//#endif

//    if ((argc == 2) && (strcmp(argv[1], "--mobile") == 0))
//        runMobile = true;

//    if (!runMobile) {
        QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication a(argc, argv);

        FunctionController *controller = new FunctionController();
        MainWindow *w = new MainWindow(*controller);
        FunctionModel *model = new FunctionModel(*controller);
        DragHandler *dragHandler = new DragHandler(*controller, *model);
        FunctionZoomer *zoomer = new FunctionZoomer(*controller, *model);
        CurrentPoint *currentPoint = new CurrentPoint(*controller, *model);
        Audio *audio = new Audio(*controller);
        AudioNotes *audionotes = new AudioNotes(*controller, *model);
        PointsInterest *pointsInterest = new PointsInterest(*controller, *model, *audionotes, *currentPoint);

        w->showMaximized();

        int ret = a.exec();

        delete w;
        delete model;
        delete dragHandler;
        delete zoomer;
        delete currentPoint;
        delete audio;
        delete pointsInterest;
        delete audionotes;
        delete controller;

        return ret;
//    } else {
//        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//        QGuiApplication app(argc, argv);

//        app.setOrganizationName("Nick Strikos");
//        app.setOrganizationDomain("nstrikos@yahoo.gr");
//        app.setApplicationName("audiographs");

//        qmlRegisterType<FunctionDisplayView>("DisplayView", 1, 0, "DisplayView");
//        qmlRegisterType<FunctionPointView>("PointView", 1, 0, "PointView");
//        //qmlRegisterType<Points>("Points", 1, 0, "Points");

//        Parameters *parameters = &Parameters::getInstance();
//        TextToSpeech *textToSpeech = &TextToSpeech::getInstance();

//        QQmlApplicationEngine engine;
//        engine.rootContext()->setContextProperty("parameters", parameters);
//        engine.rootContext()->setContextProperty("textToSpeech", textToSpeech);
//        //qRegisterMetaType<FunctionController*>("FunctionController*");


//        const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
//        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                         &app, [url](QObject *obj, const QUrl &objUrl) {
//            if (!obj && url == objUrl)
//                QCoreApplication::exit(-1);
//        }, Qt::QueuedConnection);
//        engine.load(url);

//        QObject *rootObject = engine.rootObjects().first();
//        QObject *qmlPointView = rootObject->findChild<QObject*>("pointView");
//        QObject *qmlDisplayView = rootObject->findChild<QObject*>("displayView");
//        QObject *qmlDerivativeView = rootObject->findChild<QObject*>("derivativeView");

//        //            FunctionPointView *pointView = static_cast<FunctionPointView*>(qmlPointView);
//        FunctionDisplayView *displayView = static_cast<FunctionDisplayView*>(qmlDisplayView);

//        FunctionPointView *pointView = static_cast<FunctionPointView*>(qmlPointView);


//        FunctionDisplayView *derivativeView = static_cast<FunctionDisplayView*>(qmlDerivativeView);

//        return app.exec();
//    }
}
