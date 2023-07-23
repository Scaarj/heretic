import QtQuick 2.6

Rectangle {
    id: root

    property bool handling: direction !== -1
    property int movingTouchId: -1
    property int direction: -1

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

    function exist(point) {
        return Math.abs(point.x) <= radius && Math.abs(point.y) <= radius
    }

    function handleTouch(point, id) {
        var angle = convertToAngle(point)
        movingTouchId = id
        var newDirection = handleAngle(angle)
        setDirection(newDirection)
        pressDirectionKey(direction, true)
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
    }

    function setDirection(newDirection)
    {
        if (newDirection !== direction) {
            pressDirectionKey(direction, false)
        }

        direction = newDirection
    }

    width: 300
    height: width
    radius: width / 2
    color: "white"
    opacity: 0.3

    Rectangle {
        anchors.centerIn: parent
        width: 30
        height: width
        radius: width / 2
        color: "red"
    }
}
