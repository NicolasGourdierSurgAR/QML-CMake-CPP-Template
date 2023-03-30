import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    color: "red"

    Column {
        anchors.centerIn: parent
        spacing: 10

        Button {
            text: "Button"
        }

        Button {
            text: "Button 2"
        }
    }
}
