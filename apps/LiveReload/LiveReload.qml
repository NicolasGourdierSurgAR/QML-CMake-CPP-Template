import QtQuick 2.15
import QtQuick.Controls 2.15

import QtQuick.Window 2.15


ApplicationWindow {
    id: root

    title: "LiveReload"
    visible: true

    width: 500
    height: 500

    Loader {
        id: loader

        property string sourceWindow : "./ReloadingWindow.qml";

        anchors.fill: parent

        source: sourceWindow

        function reload() {
            loader.source = "";
            QmlEngine.clearCache();
            loader.source = sourceWindow;
        }
    }

    Connections {
        target: QmlEngine

        function onReloadUI() {
            console.log("Reloading UI");
            loader.reload();
        }
    }
}
