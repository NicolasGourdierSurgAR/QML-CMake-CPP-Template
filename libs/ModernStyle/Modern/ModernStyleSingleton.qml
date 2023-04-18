pragma Singleton

import QtQuick 2.15

QtObject {
    id: root

    readonly property int defaultScreenWidth: 1920
    readonly property int defaultScreenHeight: 1080

    property int screenWidth: defaultScreenWidth
    property int screenHeight: defaultScreenHeight
    property bool scaleToScreenSize: true
    property real sizeScale: 1.0

    // Scale regarding width
    function wScale(size) {
        if(!scaleToScreenSize) {
            return size * sizeScale;
        }

        return (size/1920) * screenWidth;
    }

    // Scale regarding height
    function hScale(size) {
        if(!scaleToScreenSize) {
            return size * sizeScale;
        }

        return (size/1080) * screenHeight;
    }

    // Scale regarding mean between wscale and hscale
    function mScale(size) {
        if(!scaleToScreenSize) {
            return size * sizeScale;
        }

        return (wScale(size) + hScale(size)) / 2;
    }
}
