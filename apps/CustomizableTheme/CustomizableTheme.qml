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

    menuBar: RowLayout {
    layoutDirection: Qt.RightToLeft

        Button {
            Layout.margins: 5
            text: "Settings"

            onClicked: {
                settings.show();
            }
        }
    }

    Rectangle {
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 1
        color: "black"
    }

    Window {
        id: settings

        objectName: "settings"
        width: 800
        height: 500

        SettingsPage {
            id: settingsPage

            anchors.fill: parent

            onThemeChanged: root.ModernStyle.theme = theme;
        }
    }

    Column {
        id: column

        ModernStyle.accentColor: "orange"

        anchors {
            margins: 5
            centerIn: parent
        }
        spacing: 10

        Button {
            text: "Some Button"
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
        }

        Button {
            enabled: false
            text: "Some Disabled Button"
        }

        Button {
            highlighted: true
            text: "Some Highlighted Button"
        }

        Label {
            id: label
            text: "Some label"
        }

        SpinBox {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
        }

        Slider {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
