import QtQuick 2.6
import Sailfish.Silica 1.0

import "." as Base

MouseArea {
    id: root

    property alias source: image.source
    property color contentColor

    Base.ColoredImage {
        id: image

        source: "qrc:/resource/image/menu-dots-circle.svg"
        width: Theme.buttonWidthTiny
        height: width
        anchors.centerIn: parent
        color: root.contentColor
    }
}


