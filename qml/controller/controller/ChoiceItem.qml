import QtQuick 2.6
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0

import "../../base" as Base

MouseArea {
    id: root

    property alias fillMode: image.fillMode
    property alias source: image.source
    property alias quantity: quantity.text
    property bool animated: true
    property color borderColor: "#646464"
    property color backgroundColor: "#AFA8A8A8"
    property int animationDuration: 100
    property int size: ratio * Theme.buttonWidthTiny
    property int itemRadius: width / 2

    signal animationComplete()

    width: size
    height: width

    onClicked: {
        backgroundAnimation1.start()
        imageAnimation1.start()
    }

    Rectangle {
        id: background
        width: root.width
        height: width
        radius: root.itemRadius
        color: backgroundColor
        border.width: 2
        border.color: borderColor
    }

    Glow {
        anchors.fill: background
        radius: 8
        samples: 17
        color: "lightblue"
        source: background
        opacity: 0.0

        NumberAnimation on opacity {
            id: backgroundAnimation1
            to: 0.6
            running: false
            duration: animationDuration
            onStopped: backgroundAnimation2.start()

        }
        NumberAnimation on opacity {
            id: backgroundAnimation2
            to: 0.0
            running: false
            duration: animationDuration
            onStopped: root.animationComplete()
        }
    }

    Glow {
        anchors.fill: image
        radius: 8
        samples: 17
        color: "coral"
        source: image
        opacity: 0.0

        NumberAnimation on opacity {
            id: imageAnimation1
            to: 1.0
            running: backgroundAnimation1.running
        }

        NumberAnimation on opacity {
            id: imageAnimation2
            to: 0.0
            running: backgroundAnimation2.running
        }
    }

    Image {
        id: image
        anchors.centerIn: parent
        asynchronous: false
        width: root.size * 0.8
        height: width
        smooth: true
        fillMode: Image.PreserveAspectFit
        sourceSize: Qt.size(width, width)
    }

    Text {
        id: quantity
        anchors { top: image.bottom; horizontalCenter: image.horizontalCenter }
        color: "white"
    }
}
