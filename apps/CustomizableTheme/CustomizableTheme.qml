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

        anchors {
            margins: 5
            centerIn: parent
        }
        spacing: 10
        ModernStyle.elevation: 5

        Button {
            text: "Button" + (ModernStyle.theme === ModernStyle.Dark ? "Dark" : "Light")
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

//            onClicked: popupTest.open()
            onClicked: repeater.model++
        }

        Label {
            text: ModernStyle.elevation
        }

        Repeater {
            id: repeater
            model: 2

            Label {
                id: label
                text: ModernStyle.elevation
            }
        }

//        Popup {
//            id: popupTest

////            ModernStyle.elevation: 8
//            objectName: "BellePopup"
//            height: 100
//            width: 100
//            Rectangle {
//                objectName: "popupRectangle"
//                anchors.fill: parent
//                color: "red"
//                Button {
//                    objectName: "label"
//                    anchors.centerIn: parent
//                    text: ModernStyle.elevation
//                    onClicked: test.show()
//                }
//            }
//            Window {
//                id: test
//                objectName: "popup 3"
////                ModernStyle.elevation: 111
//                Label {
//                    objectName: "labelPopup3"
//                    text: ModernStyle.elevation
//                }
//            }
//        }

        Label {
            text: "Elevation: " + ModernStyle.elevation
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
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
