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
        for (var i = 0; i < touchPoints.length; ++i) {
            var touchPoint = touchPoints[i]
            if (touchPoint.pressed) {
                handleTouchPressed(touchPoint)
            }
        }

        if (!existMoveControllerTouch(touchPoints)) {
            moveController.stopHandling()
        }
    }

    function existMoveControllerTouch(touchPoints)
    {
        for (var i = 0; i < touchPoints.length; ++i) {
            if (touchPoints[i].pointId === moveController.movingTouchId) {
                return true
            }
        }

        return false
    }

    function handleTouchPressed(point) {
        if (screenController.gameStateActive) {
            if (!moveController.active && inLeftBottomSide(point)) {
                moveController.setBasePosition(point)
            }

            if(moveController.visible && moveController.movingTouchId === point.pointId) {
                moveController.handleTouch(Qt.point(point.x, point.y))
            } else {
                screenController.mousePositionChanged(point.x, point.y)
            }
        } else {
            screenController.mousePositionChanged(point.x, point.y)
        }
    }

    function inLeftBottomSide(point)
    {
        return point.x < root.width / 2
    }

    MoveController {
        id: moveController
        anchors.fill: parent
        active: screenController.gameStateActive && movingTouchId !== -1
    }

    Keys.MenuButton {
        anchors { left: parent.left; top: parent.top; leftMargin: Theme.paddingMedium; topMargin: anchors.leftMargin }
        visible: screenController.gameStateActive

        onClicked: screenController.menuPressed()
    }

    Timer {
        id: doubleClickingTimer
        interval: 200
    }
}
