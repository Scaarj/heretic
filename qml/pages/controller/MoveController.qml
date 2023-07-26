import QtQuick 2.6
import Sailfish.Silica 1.0

Rectangle {
    id: root

    readonly property point baseCursourPosition: Qt.point(0, 0)

    property bool active: movingTouchId !== -1
    property bool handling: direction !== -1
    property int movingTouchId: -1
    property int direction: -1
    property point cursorPosition: baseCursourPosition
    property real currentAngle: 0
    property int size: Theme.buttonWidthSmall

    function setBasePosition(point)
    {
        movingTouchId = point.pointId
        x = point.x - width / 2
        y = point.y - height / 2
    }

    function pressDirectionKey(command, pressed)
    {
        switch(command) {
        case 0:
            screenController.forwardPressed(pressed)
            screenController.rightStrafePressed(pressed)
            break;
        case 1:
            screenController.forwardPressed(pressed)
            break;
        case 2:
            screenController.forwardPressed(pressed)
            screenController.leftStrafePressed(pressed)
            break;
        case 3:
            screenController.leftStrafePressed(pressed)
            break;
        case 4:
            screenController.backPressed(pressed)
            screenController.leftStrafePressed(pressed)
            break;
        case 5:
            screenController.backPressed(pressed)
            break;
        case 6:
            screenController.backPressed(pressed)
            screenController.rightStrafePressed(pressed)
            break;
        case 7:
            screenController.rightStrafePressed(pressed)
            break;
        default:
            break;
        }
    }

    function handleTouch(point, id) {
        currentAngle = convertToAngle(point)
        movingTouchId = id
        var newDirection = handleAngle(currentAngle)
        setDirection(newDirection)
        pressDirectionKey(direction, true)
        setСursorPosition(point)
    }

    function handleAngle(angle) {
        if (angle > 22.5 && angle <= 67.5) {
            return 0
        } else if (angle > 67.5 && angle <= 112.5) {
            return 1
        } else if (angle > 112.5 && angle <= 157.5) {
            return 2
        } else if (angle > 157.5 && angle <= 202.5) {
            return 3
        } else if (angle > 202.5 && angle <= 247.5) {
            return 4
        } else if (angle > 247.5 && angle <= 292.5) {
            return 5
        } else if (angle > 292.5 && angle <= 337.5) {
            return 6
        } else {
            return 7
        }
    }

    function convertToAngle(point) {
        var atanAngle = Math.atan(point.y / point.x) * 180 / Math.PI

        if (point.x >= 0) {
            if (point.y >= 0) {
                return atanAngle
            } else {
                return 360 + atanAngle
            }
        } else {
            return 180 + atanAngle
        }
    }

    function stopHandling()
    {
        movingTouchId = -1
        pressDirectionKey(direction, false)
        setDirection(-1)
        setСursorPosition(baseCursourPosition)
    }

    function setDirection(newDirection)
    {
        if (newDirection !== direction) {
            pressDirectionKey(direction, false)
        }

        direction = newDirection
    }

    function setСursorPosition(point)
    {
        var distance = Math.sqrt(Math.pow(point.x, 2) + Math.pow(point.y, 2))

        if (distance <= radius) {
            cursorPosition = point
        } else {
            var tempX = radius * Math.cos(currentAngle * Math.PI / 180)
            var tempY = radius * Math.sin(currentAngle * Math.PI / 180)
            cursorPosition = Qt.point(tempX, tempY)
        }
    }

    width: size
    height: width
    radius: width / 2
    color: "#3FFFFFFF"
    border.width: 2
    border.color: "#7fFFFFFF"

    Rectangle {
        anchors.centerIn: parent
        width: 10
        height: width
        radius: width / 2
        color: "red"
    }

    Canvas {
        anchors.fill: parent
        onPaint: {
          var ctx = getContext("2d");
          ctx.fillStyle = Qt.rgba(1, 0, 0, 1);
          ctx.arc(0, 0, 50, Math.PI * 2, false);
        }
    }

    Rectangle {
        id: cursor
        x: cursorPosition.x + root.width / 2 - cursor.width / 2
        y: -cursorPosition.y + root.height / 2 - cursor.height / 2
        width: 30
        height: width
        radius: width / 2
        color: "grey"

        Behavior on x { NumberAnimation { duration: 100 } }
        Behavior on y { NumberAnimation { duration: 100 } }
    }
}
