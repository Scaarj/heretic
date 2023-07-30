import QtQuick 2.6
import Sailfish.Silica 1.0

import "keys" as Keys

import "controller" as Controller

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
            if (touchPoints[i].pointId === moveController.touchId) {
                return true
            }
        }

        return false
    }

    function handleTouchPressed(point) {
        var id = point.pointId
        var position = Qt.point(point.x, point.y)

        if (screenController.gameStateActive) {
            if (!moveController.active && inLeftBottomSide(point)) {
                moveController.setBaseTouchPoint(id, position)
            } else if(moveController.active && moveController.touchId === id) {
                moveController.handleTouch(position)
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

    Controller.MoveController {
        id: moveController
        anchors.fill: parent
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
