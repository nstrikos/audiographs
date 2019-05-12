#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include "AndroidClient.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    AndroidClient *androidClient = new AndroidClient(&engine);
    Parser parser;

    engine.rootContext()->setContextProperty(QLatin1String("androidClient"), androidClient);
    engine.rootContext()->setContextProperty("parser", &parser);

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    QObject::connect(window, SIGNAL(graphSignal()),
    &parser, SLOT(receiveGraphSignal()));

    QObject::connect(&parser, SIGNAL(calculationFinished()),
                     window, SLOT(updatePoints()));

    return app.exec();
}
