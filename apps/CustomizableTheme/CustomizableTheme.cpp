#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <Modern/ModernStyle.hpp>

int main(int argc, char* argv[])
{
    // create the gui app
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("Showcase");

    QLocale::setDefault(QLocale::English);

    qmlRegisterUncreatableType<ModernStyle>("ModernStyle", 1, 0, "ModernStyle", "ModernStyle is an attached property");

    // init the qml engine
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    // Init the ressources of the UI lib
    Q_INIT_RESOURCE(ModernStyle);

    // Set default style
    QQuickStyle::setStyle("Modern");
    QQuickStyle::setFallbackStyle("Material");

    // load main qml file
    engine.load(QUrl(QLatin1String("qrc:/CustomizableTheme.qml")));

    return app.exec();
}
