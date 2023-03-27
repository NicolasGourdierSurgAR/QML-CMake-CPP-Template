#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    // create the gui app
    QGuiApplication app(argc, argv);

    // init the qml engine
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc://.");

    // load main qml file
    engine.load(QUrl(QLatin1String("qrc:/Showcase.qml")));

    return app.exec();
}
