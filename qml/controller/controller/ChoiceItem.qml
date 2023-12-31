import QtQuick 2.6
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0

import "../../base" as Base

MouseArea {
    id: root

    property alias backgroundGlow: backgroundGlow
    property alias imageGlow: imageGlow
    property alias fillMode: image.fillMode
    property alias source: image.source
    property alias quantity: quantity.text
    property bool animated: true
    property color borderColor: "#646464"
    property color backgroundColor: "#AFA8A8A8"
    property int animationDuration: 100
    property int size: Theme.buttonWidthTiny
    property int itemRadius: width / 2
    property real angle: 0

    signal animationComplete()

    function startAnimation() {
        if (backgroundAnimation1.running || imageAnimation1.running) { return }

        backgroundAnimation1.start()
        imageAnimation1.start()
    }

    onClicked: startAnimation()

    width: size
    height: width

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
        id: backgroundGlow
        anchors.fill: background
        radius: 8
        samples: 17
        color: "lightblue"
        source: background
        opacity: 0.0

        NumberAnimation on opacity {
            id: backgroundAnimation1
            to: 1.0
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
        id: imageGlow
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
        asynchronous: true
        width: root.size * 0.8
        height: width
        smooth: true
        fillMode: Image.PreserveAspectFit
        sourceSize: Qt.size(width, width)
    }

    Text {
        id: quantity
        property int halfWidth: root.width / 2
        property int halfHeight: root.height / 2

        x: Math.cos(angle - Math.PI) * (root.width + width) / 2 + (halfWidth - width / 2)
        y: Math.sin(angle - Math.PI) * (root.height + height) / 2 + (halfHeight - height / 2)
        color: "white"
        font.pixelSize: Theme.fontSizeTiny
    }
}
