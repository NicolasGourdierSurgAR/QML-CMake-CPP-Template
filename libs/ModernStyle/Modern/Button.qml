import QtQuick 2.15
import QtQuick.Templates 2.15 as T

import ModernStyle 1.0

T.Button {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding);
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                                 implicitContentHeight + topPadding + bottomPadding)


    horizontalPadding: ModernStyleSingleton.wScale(40)
    verticalPadding: ModernStyleSingleton.hScale(15)

    text: "Custom Button"

    background: Rectangle {
        implicitWidth: ModernStyleSingleton.wScale(100)
        implicitHeight: ModernStyleSingleton.hScale(40)
        color: control.hovered ? Qt.darker("#4287f5",1.5) : "#4287f5"
        radius: ModernStyleSingleton.mScale(8)
    }

    contentItem: Text {
        font {
            family: "Inter"
            styleName: "SemiBold"
            pixelSize: ModernStyleSingleton.hScale(16)
            capitalization: Font.Capitalize
        }
        color: "white"
        text: control.text + " " + control.ModernStyle.elevation
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
