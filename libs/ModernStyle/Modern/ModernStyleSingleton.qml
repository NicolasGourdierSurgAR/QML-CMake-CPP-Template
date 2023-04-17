pragma Singleton

import QtQuick 2.15

QtObject {
    id: root

    readonly property int defaultScreenWidth: 1920
    readonly property int defaultScreenHeight: 1080

    property int screenWidth: defaultScreenWidth
    property int screenHeight: defaultScreenHeight

    // Scale regarding width
    function wScale(size) {
        return (size/1920) * screenWidth;
    }

    // Scale regarding height
    function hScale(size) {
        return (size/1080) * screenHeight;
    }

    // Scale regarding mean between wscale and hscale
    function mScale(size) {
        return (wScale(size) + hScale(size)) / 2;
    }
}
