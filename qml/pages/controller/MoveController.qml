import QtQuick 2.6
import Sailfish.Silica 1.0

Item {
    id: root

    property bool active: false
    property bool handling: direction !== -1
    property int movingTouchId: -1
    property int direction: -1
    property point baseCursorPosition: Qt.point(0, 0)
    property point cursorPosition: baseCursorPosition

    function setBasePosition(point)
    {
        movingTouchId = point.pointId
        baseCursorPosition = Qt.point(point.x, point.y)
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

    function handleTouch(point) {
        var angle = convertToAngle(point)
        var newDirection = handleAngle(angle)
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
        var atanAngle = Math.atan((baseCursorPosition.y - point.y) / (point.x - baseCursorPosition.x)) * 180 / Math.PI

        if (point.x >= baseCursorPosition.x) {
            if (point.y <= baseCursorPosition.y) {
                return atanAngle
            } else {
                return atanAngle + 360
            }
        } else {
            return atanAngle + 180
        }
    }

    function stopHandling()
    {
        movingTouchId = -1
        pressDirectionKey(direction, false)
        setDirection(-1)
        setСursorPosition(baseCursorPosition)
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
        cursorPosition = point
    }

    onCursorPositionChanged: cursor.updateRender()

    Canvas {
        id: cursor
        anchors.fill: parent

        function updateRender()
        {
            var ctx = getContext("2d");
            ctx.reset();
            requestPaint();
        }

        onPaint: {
            const r1 = 30
            const r2 = 45
            const x1 = baseCursorPosition.x
            const y1 = baseCursorPosition.y
            const x2 = cursorPosition.x
            const y2 = cursorPosition.y

            const atan2 = Math.atan2(y2 - y1, x2 - x1)
            const arcos = Math.acos((r1 - r2) / Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2)))
            const phy1 = atan2 + arcos
            const phy2 = atan2 - arcos
            const t12 = Qt.point(r1 * Math.cos(phy1), r1 * Math.sin(phy1))
            const t2 = Qt.point(x1 + t12.x, y1 + t12.y)
            var ctx = getContext("2d")

            ctx.reset()
            ctx.beginPath()
            ctx.arc(x1, y1, r1, phy1, phy2)
            ctx.arc(x2, y2, r2, phy2, phy1)
            ctx.lineTo(t2.x, t2.y)

            ctx.lineWidth = 2
            ctx.fillStyle = "grey"
            ctx.strokeStyle = "red"

            ctx.fill()
            ctx.stroke()
        }
        visible: active
    }
}
