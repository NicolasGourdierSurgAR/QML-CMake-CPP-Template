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

    Window {
        id: settings

        height: 400
        width: 550

        ColumnLayout {
            anchors {
                margins: 5
                fill: parent
            }

            Row {
                spacing: 5
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Scale to screen size:"
                }

                CheckBox {
                    id: checkBoxSTSZ
                    anchors.verticalCenter: parent.verticalCenter
                    checkState: Qt.Checked
                    Component.onCompleted: {
                        ModernStyleSingleton.scaleToScreenSize = Qt.binding(function() {
                            return checkBoxSTSZ.checkState === Qt.Checked;
                        });
                    }
                }
            }

            Row {
                spacing: 5
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Size scale:"
                }

                SpinBox {
                    id: spinBoxSizeScale

                    from: 50
                    to: 400
                    value: 100
                    property int decimals: 2
                    property real realValue: value / 100

                    Component.onCompleted: {
                        ModernStyleSingleton.sizeScale = Qt.binding(function() {
                            return spinBoxSizeScale.value / 100;
                        });
                    }

                    validator: DoubleValidator {
                        bottom: Math.min(spinBoxSizeScale.from, spinBoxSizeScale.to)
                        top: Math.max(spinBoxSizeScale.from, spinBoxSizeScale.to)
                    }

                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', spinBoxSizeScale.decimals);
                    }

                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }

            Button {
                text: "Close"
                Layout.alignment: Qt.AlignRight
                onClicked: settings.close();
            }
        }
    }

    Column {
        anchors {
            margins: 5
            centerIn: parent
        }
        spacing: 10

        Button {
            text: "Button"
        }

        SpinBox {

        }
    }
}
