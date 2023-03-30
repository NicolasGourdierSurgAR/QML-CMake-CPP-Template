#include "LiveReloadEngine.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

int main(int argc, char* argv[])
{
    // create the gui app
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("LiveReload");

    QLocale::setDefault(QLocale::English);

    // init the Live Reload Engine
    LiveReloadEngine engine;
    engine.rootContext()->setContextProperty("QmlEngine", &engine);

    // Init the ressources of the UI lib
    Q_INIT_RESOURCE(Ui);

    // load main qml file
    // run the app with the env var MAIN_QML set to the main qml file in the sources of the project
    engine.load(QUrl(qgetenv("MAIN_QML")));
    if(engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
