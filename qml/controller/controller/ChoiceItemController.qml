import QtQuick 2.6
import Sailfish.Silica 1.0

import "../../base" as Base

Item {
    id: root

    property alias bodyCircle: bodyCircle
    property alias model: repeater.model
    property color bodyBorderColor: "#A8A8A8"
    property color bodyBackgroundColor: "#7FA8A8A8"
    property int bodyCircleHeight: Math.min(bodySize.width, bodySize.height)
    property int borderWidth: 4 * currentScale
    property int circleRadius: (bodyCircle.height / 2 - borderWidth) * currentScale
    property int currentCoefficient: closeCoefficient
    property int closeCoefficient: 30
    property int openCoefficient: 100
    property int itemsScale: 1
    property int itemSize: Theme.buttonWidthTiny * root.currentScale
    property real currentScale: currentCoefficient / 100
    property rect gameScreenRect: scenePainter.activeScreen
    property size bodySize: Qt.size(gameScreenRect.width, gameScreenRect.height)

    signal itemSelect(var index)
    signal animationStopped()

    function toggle()
    {
        if (currentCoefficient === openCoefficient) {
            close()
        } else if (currentCoefficient === closeCoefficient) {
            open()
        }
    }

    function open() {
        currentCoefficient = openCoefficient
    }

    function close() {
        currentCoefficient = closeCoefficient
    }

    visible: !(currentCoefficient === closeCoefficient)

    Rectangle {
        id: bodyCircle

        // NOTE: anchors.centerIn leads to incorrect layouting, because ignore the title height in Portrait orientation
        x: gameScreenRect.x + (gameScreenRect.width - width ) / 2
        y: gameScreenRect.y + (gameScreenRect.height - height) / 2

        width: root.bodyCircleHeight * currentScale
        height: width
        radius: width / 2
        color: bodyBackgroundColor
        border.color: bodyBorderColor
        border.width: 2

        Repeater {
            id: repeater
            anchors.centerIn: parent

            delegate: ChoiceItem {
                id: item

                // NOTE: padding from circle edge to button center
                readonly property int padding: itemRadius * 1.5
                readonly property int itemCenterRadius: circleRadius - padding

                size: root.bodyCircleHeight / root.itemsScale
                x: Math.cos(2 / repeater.count * index * Math.PI) * itemCenterRadius + bodyCircle.width / 2 - itemRadius
                y: Math.sin(2 / repeater.count * index * Math.PI) * itemCenterRadius + bodyCircle.height / 2 - itemRadius
                source: model.image ? model.image : ""
                quantity: model.quantity !== -1 ? model.quantity : "∞"

                onClicked: root.itemSelect(model.code)
                onAnimationComplete: root.close()
            }
        }

        Base.Button {
            anchors.centerIn: parent
            source: "image://theme/icon-m-input-remove"
            size: itemSize

            background: Rectangle {
                anchors.fill: parent
                radius: width / 2
                color: "transparent"
                border.width: 2
                border.color: root.bodyBorderColor
            }

            onClicked: root.close()
        }
    }

    Behavior on currentCoefficient {
        NumberAnimation {
            easing.type: Easing.InExpo
            duration: 200

            onStopped: root.animationStopped()
        }
    }
}
