#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "AndroidClient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    AndroidClient *androidClient = new AndroidClient(&engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty(QLatin1String("androidClient"), androidClient);

    return app.exec();
}
