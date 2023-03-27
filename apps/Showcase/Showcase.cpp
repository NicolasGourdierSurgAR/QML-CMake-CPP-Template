#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    // create the gui app
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("Showcase");

    QLocale::setDefault(QLocale::English);

    // init the qml engine
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc://.");

    // Init the ressources of the UI lib
    Q_INIT_RESOURCE(Ui);

    // load main qml file
    engine.load(QUrl(QLatin1String("qrc:/Showcase.qml")));

    return app.exec();
}
