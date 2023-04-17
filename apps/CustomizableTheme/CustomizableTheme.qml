import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import ModernStyle 1.0

ApplicationWindow {
    id: root

    title: "Showcase"
    visible: true

    width: 500
    height: 500

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
