import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Qt.labs.settings 1.1

import ModernStyle 1.0
import Modern 1.0

Page {
    id: root

    signal themeChanged(var theme);

    Settings {
        category: "UiSettings"

        property alias scaleToScreenSize: checkBoxSTSZ.checkState
        property alias sizeScale: spinBoxSizeScale.value
    }

    TabBar {
        id: tabBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        TabButton {
            text: "Sizing"
        }
        TabButton {
            text: "Themes"
        }
    }

    StackLayout {
        anchors {
            top: tabBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        currentIndex: tabBar.currentIndex

        Item {
            id: sizeSettings

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
                                return realValue;
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
            }
        }

        Item {
            ColumnLayout {
                anchors {
                    margins: 5
                    fill: parent
                }

                Row {
                    spacing: 5
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Theme"
                    }

                    ComboBox {
                        id: comboBox

                        anchors.verticalCenter: parent.verticalCenter
                        model: ["Light","Dark"]
                        onCurrentTextChanged: {
                            switch(currentText) {
                            case "Light":
                                root.themeChanged(ModernStyle.Light);
                                break;
                            case "Dark":
                                root.themeChanged(ModernStyle.Dark);
                                break;
                            default:
                                break;
                            };
                        }
                    }
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }
}
