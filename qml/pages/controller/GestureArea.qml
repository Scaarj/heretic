import QtQuick 2.6
import Sailfish.Silica 1.0

import "keys" as Keys

MultiPointTouchArea {
    id: root

    minimumTouchPoints: 1
    maximumTouchPoints: 2

    onPressed: {
        var xCoord = touchPoints[0].x
        var yCoord = touchPoints[0].y
        if (doubleClickingTimer.running) {
            screenController.doubleClick(xCoord, yCoord)
        } else {
            screenController.mousePressed(xCoord, yCoord)
        }
    }

    onReleased: {
        if (!doubleClickingTimer.running) {
            doubleClickingTimer.start()
        }
    }

    onTouchUpdated: {
        if (!touchPoints.length) {
            moveController.stopHandling()
            return
        }

        var moveControllerPressed = moveController.handling
        var movingTouchFound = false
        var movingTouchId = moveController.movingTouchId

        for (var i = 0; i < touchPoints.length; ++i) {
            var touchPoint = touchPoints[i]
            if (touchPoint.pressed) {
                handleTouchPressed(touchPoint)
                if (touchPoint.pointId === moveController.movingTouchId) {
                    movingTouchFound = true
                }
            }
        }

        if (!movingTouchFound) {
            moveController.stopHandling()
        }
    }

    function handleTouchPressed(point) {
        var xOffset = moveController.x + moveController.width / 2 + moveController.anchors.leftMargin
        var yOffset = moveController.y + moveController.height / 2 + moveController.anchors.bottomMargin
        var normalizedPoint = Qt.point(point.x - xOffset, -(point.y - yOffset))

        if (moveController.exist(normalizedPoint)) {
            moveController.handleTouch(normalizedPoint, point.pointId)
        } else {
            var xCoord = point.x
            var yCoord = point.y
            screenController.mousePositionChanged(xCoord, yCoord)
        }
    }

    MoveController {
        id: moveController
        anchors { left: parent.left; bottom: parent.bottom; leftMargin: Theme.paddingMedium; bottomMargin: anchors.leftMargin }
        visible: screenController.isGameState
    }

    Keys.MenuButton {
        anchors { left: parent.left; top: parent.top; leftMargin: Theme.paddingMedium; topMargin: anchors.leftMargin }
        visible: screenController.isGameState

        onClicked: screenController.menuPressed()
    }

    Timer {
        id: doubleClickingTimer
        interval: 100
    }
}
