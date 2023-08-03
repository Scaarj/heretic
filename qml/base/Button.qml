import QtQuick 2.6
import Sailfish.Silica 1.0

import "." as Base

MouseArea {
    id: root

    property alias source: image.source
    property alias clickAnimation: clickAnimation
    property color contentColor: "white"
    property color contentColorPressed: "coral"
    property color currentColor: clickAnimation.running ? contentColorPressed : contentColor
    property int size: Theme.buttonWidthTiny

    onClicked: clickAnimation.restart()

    width: size
    height: width

    Base.ColoredImage {
        id: image
        width: clickAnimation.running ? size * 0.9 : size
        height: width
        anchors.centerIn: parent
        color: root.currentColor
    }

    Timer {
        id: clickAnimation
        interval: 100
    }
}


