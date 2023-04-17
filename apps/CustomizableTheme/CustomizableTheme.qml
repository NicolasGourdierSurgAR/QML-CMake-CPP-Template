import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

import ModernStyle 1.0
import Modern 1.0

ApplicationWindow {
    id: root

    title: "Showcase"
    visible: true

    width: 500
    height: 500

    Component.onCompleted: {
        ModernStyleSingleton.screenWidth = Qt.binding(function() {
            return Screen.width && Screen.height ?
                        Screen.primaryOrientation === Qt.LandscapeOrientation ? Screen.width : Screen.height
                      : ModernStyleSingleton.defaultScreenWidth
        });
        ModernStyleSingleton.screenHeight = Qt.binding(function() {
            return Screen.width && Screen.height ?
                        Screen.primaryOrientation === Qt.LandscapeOrientation ? Screen.height : Screen.width
                      : ModernStyleSingleton.defaultScreenHeight
        });
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Button {
            text: "Unlocked"
            ModernStyle.elevation: 10
        }

        SpinBox {

        }

    }
}
