#include "dialogs/mainwindow.h"

#include <QApplication>
#include "controller/functionController.h"
#include "function/functionModel.h"
#include "function/dragHandler.h"
#include "function/functionZoomer.h"
#include "function/currentPoint.h"
#include "generator/audio.h"
#include "audionotes/audionotes.h"
#include "function/pointsInterest.h"
#include "controller/stateMachine.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <mobileview/functionDisplayView.h>
#include <mobileview/functionPointView.h>
#include <mobileview/qmlConnector.h>
#include <utils/texttospeech.h>

int main(int argc, char *argv[])
{
    bool runMobile = false;
    int ret;

#ifdef Q_OS_ANDROID
    runMobile = true;
#endif

    if ((argc == 2) && (strcmp(argv[1], "--mobile") == 0))
        runMobile = true;

    FunctionController *controller = new FunctionController();
    FunctionModel *model = new FunctionModel(*controller);
    DragHandler *dragHandler = new DragHandler(*controller, *model);
    FunctionZoomer *zoomer = new FunctionZoomer(*controller, *model);
    CurrentPoint *currentPoint = new CurrentPoint(*controller, *model);
    Audio *audio = new Audio(*controller);
    AudioNotes *audionotes = new AudioNotes(*controller, *model);
    PointsInterest *pointsInterest = new PointsInterest(*controller, *model, *audionotes, *currentPoint);
    StateMachine *stateMachine = new StateMachine(*controller);

    if (!runMobile) {
        QApplication a(argc, argv);

        MainWindow *w = new MainWindow(*controller);
        w->showMaximized();

        ret = a.exec();
        delete w;

    } else {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv);

        app.setOrganizationName("Nick Strikos");
        app.setOrganizationDomain("nstrikos@yahoo.gr");
        app.setApplicationName("audiographs");

        QmlConnector *w = new QmlConnector(*controller, nullptr);

        qmlRegisterType<FunctionDisplayView>("DisplayView", 1, 0, "DisplayView");
        qmlRegisterType<FunctionPointView>("PointView", 1, 0, "PointView");
        qmlRegisterType<Points>("Points", 1, 0, "Points");

        Parameters *parameters = &Parameters::getInstance();
        //FunctionExpression functionExpression;
        TextToSpeech *textToSpeech = &TextToSpeech::getInstance();

        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("parameters", parameters);
        engine.rootContext()->setContextProperty("qmlConnector", w);
        engine.rootContext()->setContextProperty("textToSpeech", textToSpeech);

        const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);

        QObject *rootObject = engine.rootObjects().first();
        QObject *qmlPointView = rootObject->findChild<QObject*>("pointView");
        QObject *qmlDisplayView = rootObject->findChild<QObject*>("displayView");
        QObject *qmlDerivativeView = rootObject->findChild<QObject*>("derivativeView");

        FunctionDisplayView *displayView = static_cast<FunctionDisplayView*>(qmlDisplayView);
        QObject::connect(w, &QmlConnector::qmlGraph, displayView, &FunctionDisplayView::draw);
        QObject::connect(w, &QmlConnector::qmlError, displayView, &FunctionDisplayView::clear);

        FunctionPointView *pointView = static_cast<FunctionPointView*>(qmlPointView);
        QObject::connect(w, &QmlConnector::qmlGraph, pointView, &FunctionPointView::draw);
        QObject::connect(w, &QmlConnector::newCurrentPoint, pointView, &FunctionPointView::setCurrentPoint);

        FunctionDisplayView *derivativeView = static_cast<FunctionDisplayView*>(qmlDerivativeView);
        QObject::connect(w, &QmlConnector::updateDerivative, derivativeView, &FunctionDisplayView::draw);
        QObject::connect(w, &QmlConnector::qmlError, derivativeView, &FunctionDisplayView::clear);

        ret = app.exec();
        delete w;
    }

    delete model;
    delete dragHandler;
    delete zoomer;
    delete currentPoint;
    delete audio;
    delete pointsInterest;
    delete audionotes;
    delete stateMachine;
    delete controller;

    return ret;
}
